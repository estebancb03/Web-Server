/// @copyright 2021 ECCI, Universidad de Costa Rica. All rights reserved
/// This code is released under the GNU Public License version 3
/// @author Esteban Castañeda Blanco <esteban.castaneda@ucr.ac.cr>
/// @author Daniel Lizano Morales <daniel.lizanomorales@ucr.ac.cr>
/// @author Andrea Ramírez Rojas <andrea.ramirezrojas@ucr.ac.cr>
/// @author Carlos Ramírez Masís <carlos.ramirezmasis@ucr.ac.cr>

#ifndef HTTPSERVER_H
#define HTTPSERVER_H

#include <unistd.h>
#include <string>
#include <vector>
#include <cassert>
#include <csignal>
#include <stdexcept>

#include "Log.hpp"
#include "Queue.hpp"
#include "Socket.hpp"
#include "HttpApp.hpp"
#include "Producer.hpp"
#include "Consumer.hpp"
#include "TcpServer.hpp"
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"
#include "OrderPackage.hpp"
#include "NetworkAddress.hpp"
#include "HttpDispatcher.hpp"
#include "HttpResponseConsumer.hpp"
#include "HttpConnectionHandler.hpp"

#define DEFAULT_PORT "8080"
#define DEFAULT_MAX_CONNECTIONS sysconf(_SC_NPROCESSORS_ONLN);

class HttpApp;
class HttpDispatcher;
class HttpConnectionHandler;
class HttpResponseConsumer;

class HttpServer : public TcpServer {
  DISABLE_COPY(HttpServer);

 protected:
  /// Lookup criteria for searching network information about this host
  struct addrinfo hints;
  /// TCP port where this web server will listen for connections
  const char* port = DEFAULT_PORT;

  // Save the maximum number of connections
  int64_t maxConnections = DEFAULT_MAX_CONNECTIONS;

  /// Chain of registered web applications. Each time an incoming HTTP request
  /// is received, the request is provided to each application of this chain.
  /// If an application detects the request is for it, the application will
  /// call the httpResponse.send() and the chain stops. If no web app serves
  /// the request, the not found page will be served.
  std::vector<HttpApp*> applications;
  // Save the created sockets
  Queue<Socket>* socketsQueue;
  // Save pointers to HttpConnectionHandler to handle sockets
  std::vector<HttpConnectionHandler*> connections;
  // A queue of OrderPackages
  Queue<OrderPackage>* orderPackagesQueue;
  // A queue of OrderPackages
  Queue<OrderPackage>* routedOrderPackagesQueue;
  // A queue of HttpResponses
  Queue<HttpResponse>* httpResponseQueue;
  // A pointer of HttpDispatcher object
  HttpDispatcher* httpDispatcher;

 public:
  // A pointer of HttpResponseConsumer object
  HttpResponseConsumer* httpResponseConsumer;

 public:
  /**
   * @brief Construct a new Http Server object
   */
  HttpServer();

  /**
   * @brief Destroy the Http Server object
   */
  ~HttpServer();

  /**
   * @brief Registers a web application to the chain
   * @param application A pointer to HttpApp
   */
  void chainWebApp(HttpApp* application);

  /**
   * @brief Start the web server for listening client connections and HTTP requests
   * @param argc Number of arguments received by the program
   * @param argv Argument vector received by the program
   * @return EXIT_SUCCESS
   */
  int start(int argc, char* argv[]);

  /**
   * @brief Stop the web server.
   * @details The server may stop not immediately. It will stop
   * for listening further connection requests at once, but pending HTTP
   * requests that are enqueued will be allowed to finish
   */
  void stop();

  /**
   * @brief  Infinetelly listen for client connection requests and accept all of them.
   * @details For each accepted connection request, the virtual onConnectionAccepted()
   * will be called. Inherited classes must override that method
   * @param port Port that connects to the server
   */
  void listenForever(const char* port);

  /**
   * @brief Get the Instance object
   * @details Singleton object
   * @return HttpServer& A reference to the server
   */
  static HttpServer& getInstance();

  /**
   * @brief Handles the terminal signal 
   * @details Adapted from: 
   * https://www.thegeekstuff.com/2012/03/catch-signals-sample-c-code/
   * @param signal Number of the signal
   */
  static void sigHandler(int signal);

  /**
   * @brief Get the Sockets Queue object
   * @return Queue<Socket>* A pointer to the start of the vector
   */
  Queue<Socket>* getSocketsQueue();

  /**
   * @brief Get the OrderPackage Queue object
   * @return Queue<OrderPackage>* A OrderPackage queue pointer
   */
  Queue<OrderPackage>* getOrderPackagesQueue();

  /**
   * @brief Get the routed OrderPackage Queue object
   * @return Queue<OrderPackage>* A ordered OrderPackage queue pointer
   */
  Queue<OrderPackage>* getRoutedOrderPackagesQueue();

 protected:
  /**
   * @brief Analyze the command line arguments
   * @param argc Number of arguments received by the program
   * @param argv Argument vector received by the program
   *  @return true if program can continue execution, false otherwise
   */
  bool analyzeArguments(int argc, char* argv[]);

  /**
   * @brief Add the socket to the socket queue
   * @param client A reference to Sockect
   */
  void handleClientConnection(Socket& client) override;
};

#endif  // HTTPSERVER_H
