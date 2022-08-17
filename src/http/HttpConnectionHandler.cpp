/// @copyright 2021 ECCI, Universidad de Costa Rica. All rights reserved
/// This code is released under the GNU Public License version 3
/// @author Esteban Castañeda Blanco <esteban.castaneda@ucr.ac.cr>
/// @author Daniel Lizano Morales <daniel.lizanomorales@ucr.ac.cr>
/// @author Andrea Ramírez Rojas <andrea.ramirezrojas@ucr.ac.cr>
/// @author Carlos Ramírez Masís <carlos.ramirezmasis@ucr.ac.cr>

#include "HttpConnectionHandler.hpp"

HttpConnectionHandler::HttpConnectionHandler(HttpServer* httpServer,
 std::vector<HttpApp*>& httpApps) {
  setHttpServer(httpServer);
  this->httpApps = httpApps;
}

HttpConnectionHandler::~HttpConnectionHandler() {
}

void HttpConnectionHandler::setHttpServer(HttpServer* httpServer) {
  this->httpServer = httpServer;
  setConsumingQueue(httpServer->getSocketsQueue());
  setProducingQueue(httpServer->getOrderPackagesQueue());
}

int HttpConnectionHandler::run() {
  // Starts the loop that consumes all the messages that arrive
  this->consumeForever();
  return EXIT_SUCCESS;
}

void HttpConnectionHandler::consume(Socket client) {
  // While the same client asks for HTTP requests in the same connection
  while (true) {
    // Create an object that parses the HTTP request from the socket
    HttpRequest httpRequest(client);

    // If the request is not valid or an error happened
    if (!httpRequest.parse()) {
      // Non-valid requests are normal after a previous valid request. Do not
      // close the connection yet, because the valid request may take time to
      // be processed. Just stop waiting for more requests
      break;
    }

    // A complete HTTP client request was received. Create an object for the
    // server responds to that client's request
    HttpResponse httpResponse(client);
    OrderPackage orderPackage(httpRequest, httpResponse);

    // Give subclass a chance to respond the HTTP request
    const bool handled = this->handleHttpRequest(orderPackage);

    // If subclass did not handle the request or the client used HTTP/1.0
    if (!handled || httpRequest.getHttpVersion() == "HTTP/1.0") {
      // The socket will not be more used, close the connection
      client.close();
      break;
    }
  }
}

bool HttpConnectionHandler::handleHttpRequest(OrderPackage& orderPackage) {
  // Print IP and port from client
  const NetworkAddress& address = orderPackage.httpRequest.getNetworkAddress();
  Log::append(Log::INFO, "connection",
    std::string("connection established with client ") + address.getIP()
    + " port " + std::to_string(address.getPort()));

  // Print HTTP request
  Log::append(Log::INFO, "request", orderPackage.httpRequest.getMethod()
    + ' ' + orderPackage.httpRequest.getURI()
    + ' ' + orderPackage.httpRequest.getHttpVersion());

  this->produce(orderPackage);
  return this->route();
}

bool HttpConnectionHandler::route() {
  // Traverse the chain of applications
  for (size_t index = 0; index < this->httpApps.size(); ++index) {
    // If this application handles the request
    HttpApp* app = this->httpApps[index];
    Queue<HttpResponse>* queue =
     app->handleHttpRequest(this->httpServer->getRoutedOrderPackagesQueue());
    if (queue) {
      Queue<HttpResponse>* queue2 =
       this->httpServer->httpResponseConsumer->getConsumingQueue();
      queue2->push(queue->pop());
      return true;
    }
  }
  return false;
}
