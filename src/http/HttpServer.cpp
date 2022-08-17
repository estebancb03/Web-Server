/// @copyright 2021 ECCI, Universidad de Costa Rica. All rights reserved
/// This code is released under the GNU Public License version 3
/// @author Esteban Castañeda Blanco <esteban.castaneda@ucr.ac.cr>
/// @author Daniel Lizano Morales <daniel.lizanomorales@ucr.ac.cr>
/// @author Andrea Ramírez Rojas <andrea.ramirezrojas@ucr.ac.cr>
/// @author Carlos Ramírez Masís <carlos.ramirezmasis@ucr.ac.cr>

#include "HttpServer.hpp"

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
  // Socket is added to the queue
  this->socketsQueue->push(client);
}

void HttpServer::chainWebApp(HttpApp* application) {
  assert(application);
  this->applications.push_back(application);
}

int HttpServer::start(int argc, char* argv[]) {
  // Sockets queue is created
  this->socketsQueue = new Queue<Socket>;
  // HttpOrders queue is created
  this->orderPackagesQueue = new Queue<OrderPackage>;
  // HttpRoutedOrdersQueue queue is created
  this->routedOrderPackagesQueue = new Queue<OrderPackage>;
  // httpResponseQueue queue is created
  this->httpResponseQueue = new Queue<HttpResponse>;

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
        stopApps = true;
        }

        // Se inicializa hilo del dispatcher
        this->httpDispatcher = new HttpDispatcher(this->orderPackagesQueue,
         this->routedOrderPackagesQueue);
        this->httpDispatcher->startThread();

        this->httpResponseConsumer =
         new HttpResponseConsumer(this->httpResponseQueue);
        // HttpResponseConsumer thread is created
        this->httpResponseConsumer->startThread();
        // Start the server
        // Connections array size is redefined
        this->connections.resize(maxConnections);

        for (int64_t index = 0; index < maxConnections; index++) {
          // For each connection a HttpConnectionHandler is created
          this->connections[index] = new HttpConnectionHandler(this,
            applications);
          assert(this->connections[index]);
          // For each HttpConnectionHandler a thread is created
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
    Socket empty = Socket();
    for (int64_t index = 0; index < (int64_t) this->connections.size();
     index++) {
      // For each connection an empty socket is added to the queue
      this->socketsQueue->push(empty);
    }

    for (int64_t index = 0; index < (int64_t) this->connections.size();
     index++) {
      // For each connection its thread is joinned
      this->connections[index]->waitToFinish();
    }

    // Sockets queue is deleted
    delete this->socketsQueue;
    // orderPackagesQueue queue is deleted
    delete this->orderPackagesQueue;
    // routedOrderPackagesQueue queue is deleted
    delete this->routedOrderPackagesQueue;
    // httpResponseQueue queue is deleted
    delete this->httpResponseQueue;

    // Stop all web applications

    for (HttpConnectionHandler* consumer : this->connections) {
      delete consumer;
    }
    std::cerr << "\nerror: " << error.what() << std::endl;
    // httpDispatcher its thread is joinned
    this->httpDispatcher->waitToFinish();
    // httpResponseConsumer its thread is joinned
    this->httpResponseConsumer->waitToFinish();
    // httpDispatcher is deleted
    delete this->httpDispatcher;
    // httpResponseConsumer is deleted
    delete this->httpResponseConsumer;
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


Queue<OrderPackage>* HttpServer::getOrderPackagesQueue() {
  return this->orderPackagesQueue;
}

Queue<OrderPackage>* HttpServer::getRoutedOrderPackagesQueue() {
  return this->routedOrderPackagesQueue;
}


