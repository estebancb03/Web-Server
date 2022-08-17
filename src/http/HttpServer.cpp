// Copyright 2021 Jeisson Hidalgo-Cespedes. Universidad de Costa Rica. CC BY 4.0

#include <unistd.h>
#include <cassert>
#include <stdexcept>
#include <string>
#include <csignal>

#include "HttpApp.hpp"
#include "HttpServer.hpp"
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"
#include "Log.hpp"
#include "NetworkAddress.hpp"
#include "Socket.hpp"
#include "Producer.hpp"
#include "Queue.hpp"
#include "Consumer.hpp"

// TODO(you): Implement connection handlers argument
const char* const usage =
  "Usage: webserv [port] [handlers]\n"
  "\n"
  "  port        Network port to listen incoming HTTP requests, default "
    DEFAULT_PORT "\n"
  "  handlers     Number of connection handler theads\n";

HttpServer::HttpServer() {
}

HttpServer::~HttpServer() {
}

void HttpServer::listenForever(const char* port) {
  return TcpServer::listenForever(port);
}

void HttpServer::handleClientConnection(Socket& client) {
  // Se agrega un socket a la cola
  this->socketsQueue->push(client);
}

void HttpServer::chainWebApp(HttpApp* application) {
  assert(application);
  this->applications.push_back(application);
}

int HttpServer::start(int argc, char* argv[]) {
  // Se crea la cola de sockets
  this->socketsQueue = new Queue<Socket>;

  bool stopApps = false;
  try {
    if (this->analyzeArguments(argc, argv)) {
      if (signal(SIGINT, HttpServer::sigHandler) == SIG_ERR) {
        // Recibido SIGINT
        // Termina
      } else {
        // Start the log service
        Log::getInstance().start();

        // Start all web applications
        for (size_t index = 0; index < this->applications.size(); ++index) {
          this->applications[index]->start();
          // this->applications[index]->startThread();
        }
        stopApps = true;

        // Se redefine el tam del vector a la cantidad maxima de conexiones
        this->connections.resize(maxConnections);
        // Para cada conexion, cree un HttpConnectionHandler
        // Para cada HttpConnectionHandler, cree un hilo
        for (int64_t index = 0; index < maxConnections; index++) {
          this->connections[index] = new HttpConnectionHandler(this,
            applications);
          assert(this->connections[index]);
          this->connections[index]->startThread();
        }

        // Start waiting for connections
        this->listenForConnections(this->port);
        const NetworkAddress& address = this->getNetworkAddress();
        Log::append(Log::INFO, "webserver", "Listening on " + address.getIP()
          + " port " + std::to_string(address.getPort()) + " using " +
            std::to_string(this->maxConnections) + " threads");

        // Accept all client connections
        this->acceptAllConnections();
      }
    }
  } catch (const std::runtime_error& error) {
     // Creamos sockets vacios
    Socket empty = Socket();
    // Para cada connections ...
    for (int64_t index = 0; index < (int64_t) this->connections.size();
     index++) {
      // Pone un socket vacio en la cola
      this->socketsQueue->push(empty);
    }

    // Para cada connections ...
    for (int64_t index = 0; index < (int64_t) this->connections.size();
     index++) {
      // Hace join al hilo
      this->connections[index]->waitToFinish();
    }

    // Elimina la cola
    delete this->socketsQueue;

    for (HttpConnectionHandler* consumer : this->connections) {
      delete consumer;
    }
    std::cerr << "\nerror: " << error.what() << std::endl;
  }

  // If applications were started
  if (stopApps) {
    // Stop web applications. Give them an opportunity to clean up
    for (size_t index = 0; index < this->applications.size(); ++index) {
      this->applications[index]->stop();
    }
  }

  // Stop the log service
  Log::getInstance().stop();

  return EXIT_SUCCESS;
}

bool HttpServer::analyzeArguments(int argc, char* argv[]) {
  // Traverse all arguments
  for (int index = 1; index < argc; ++index) {
    const std::string argument = argv[index];
    if (argument.find("help") != std::string::npos) {
      std::cout << usage;
      return false;
    }
  }

  if (argc >= 2) {
    this->port = argv[1];
  }
  if (argc >= 3) {
    this->maxConnections = std::atoi(argv[2]);
  }

  return true;
}

void HttpServer::stop() {
  // Stop listening for incoming client connection requests
  this->stopListening();
}

HttpServer& HttpServer::getInstance() {
  static HttpServer server;
  return server;
}

void HttpServer::sigHandler(int signal) {
  if (signal == SIGINT) {
    HttpServer::getInstance().stop();
  }
}

Queue<Socket>* HttpServer::getSocketsQueue() {
  return this->socketsQueue;
}


