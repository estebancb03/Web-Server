/// @copyright 2021 ECCI, Universidad de Costa Rica. All rights reserved
/// This code is released under the GNU Public License version 3
/// @author Esteban Castañeda Blanco <esteban.castaneda@ucr.ac.cr>
/// @author Daniel Lizano Morales <daniel.lizanomorales@ucr.ac.cr>
/// @author Andrea Ramírez Rojas <andrea.ramirezrojas@ucr.ac.cr>
/// @author Carlos Ramírez Masís <carlos.ramirezmasis@ucr.ac.cr>

#ifndef HTTPCONNECTIONHANDLER_H
#define HTTPCONNECTIONHANDLER_H

#include <vector>

#include "HttpServer.hpp"
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"
#include "Queue.hpp"
#include "Socket.hpp"
#include "Consumer.hpp"

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
class HttpConnectionHandler : public Consumer <Socket> {
 protected:
  /// A pointer to the server
  HttpServer *server;
  /// A pointer of a vector of web applications
  std::vector<HttpApp*> httpApps;
  /**
   * @brief Each thread handles one client request at the time
   * @param httpRequest The request of the client which needs to be worked
   * @param httpResponse The response the client will get at the end
   * @return boolean result of route()
   */
  bool handleHttpRequest(HttpRequest& httpRequest,
    HttpResponse& httpResponse);
  /**
   * @brief Checks which web application has to process the request recieved
   * @param httpRequest The request of the client which needs to be worked
   * @param httpResponse The response the client will get at the end
   * @return 
   *   true: If this application handles the request
   *   false: Unrecognized request
   */
  bool route(HttpRequest& httpRequest, HttpResponse& httpResponse);
  /**
   * @brief Tells the client that no web application can process their request
   * @param httpRequest The request of the client which needs to be worked
   * @param httpResponse The response the client will get at the end
   * @return boolean result
   */
  bool serveNotFound(HttpRequest& httpRequest, HttpResponse& httpResponse);

 public:
  /**
   * @brief HttpConnectionHandler's constructor
   * @param httpserver A pointer to the server
   * @param applications A pointer of a vector of web applications
   * @return object (thread) of type HttpConnectionHandler
   */
  explicit HttpConnectionHandler(HttpServer *httpserver,
   std::vector<HttpApp*>& applications);

  /**
   * @brief HttpConnectionHandler's destructor
   */
  virtual ~HttpConnectionHandler();

  /**
   * @brief Sets httpServer to be used by HttpConnectionHandler threads
   * @param httpserver A pointer to the server
   */
  void setHttpServer(HttpServer *httpserver);

    // sobrescribe la funcion de Thread
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
};


#endif  // HTTPCONNECTIONHANDLER_H
