/// @copyright 2021 ECCI, Universidad de Costa Rica. All rights reserved
/// This code is released under the GNU Public License version 3
/// @author Esteban Castañeda Blanco <esteban.castaneda@ucr.ac.cr>
/// @author Daniel Lizano Morales <daniel.lizanomorales@ucr.ac.cr>
/// @author Andrea Ramírez Rojas <andrea.ramirezrojas@ucr.ac.cr>
/// @author Carlos Ramírez Masís <carlos.ramirezmasis@ucr.ac.cr>

#ifndef HTTPCONNECTIONHANDLER_H
#define HTTPCONNECTIONHANDLER_H

#include <string>
#include <vector>

#include "Log.hpp"
#include "Queue.hpp"
#include "Socket.hpp"
#include "HttpApp.hpp"
#include "Consumer.hpp"
#include "Assembler.hpp"
#include "HttpServer.hpp"
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"
#include "OrderPackage.hpp"
#include "NetworkAddress.hpp"
#include "HttpDispatcher.hpp"

class HttpApp;
class HttpServer;

/**
 * @brief They represent threads which process client requests (sockets)
 * and send them to their respective web application to be worked.
 * @param number Number
 * @return 
 *   true: if the number is prime
 *   false: if the number is not prime 
 */
class HttpConnectionHandler : public Assembler <Socket, OrderPackage> {
 private:
  // A pointer to the server
  HttpServer* httpServer;
  // A pointer of a vector of web applications
  std::vector<HttpApp*> httpApps;

 public:
  /**
   * @brief HttpConnectionHandler's constructor
   * @param httpserver A pointer to the server
   * @param httpApps A pointer of a vector of web applications
   * @return object (thread) of type HttpConnectionHandler
   */
  explicit HttpConnectionHandler(HttpServer *httpserver,
    std::vector<HttpApp*>& httpApps);

  /**
   * @brief HttpConnectionHandler's destructor
   */
  virtual ~HttpConnectionHandler();

  /**
   * @brief Sets httpServer to be used by HttpConnectionHandler threads
   * @param httpServer A pointer to the server
   */
  void setHttpServer(HttpServer *httpServer);

  /**
   * @brief Overwrites Thread run() function, which creates threads
   * @return Error code, 0 for success
   */
  int run() override;

  /**
   * @brief Each thread validates one client request at the time.
   * In case it is a valid request, it is sent to handleHttpRequest()
   * @param client A socket (request) from the client
   */
  void consume(Socket client) override;

  /**
   * @brief Each thread handles one orderPackage at the time,
   * then produces a new orderPackage and calls route() subroutine
   * @param orderPackage The request of the client which needs to be worked
   * @return boolean result of route()
   */
  bool handleHttpRequest(OrderPackage& orderPackage);

  /**
   * @brief Checks which web application has to process the orderPackage recieved
   * and sets consumingQueue of HttpResponseConsumer
   * @return 
   *   true: If this application handles the orderPackage
   *   false: Unrecognized orderPackage
   */
  bool route();
};

#endif  // HTTPCONNECTIONHANDLER_H
