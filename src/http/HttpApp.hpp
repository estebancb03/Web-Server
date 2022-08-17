// Copyright 2021 Jeisson Hidalgo-Cespedes. Universidad de Costa Rica. CC BY 4.0

#ifndef HTTPAPP_H
#define HTTPAPP_H

#include "Queue.hpp"
#include "common.hpp"
#include "Consumer.hpp"
#include "OrderPackage.hpp"

/**
@brief Base class for all web applications that can be registered with the
web server.
**/
class HttpApp {
  /// Web application objects are usually complex. This base class does not
  /// require child classes to allow copying
  DISABLE_COPY(HttpApp);

 public:
  /// Constructor
  HttpApp() = default;
  /// Destructor
  ~HttpApp() = default;
  /// Called by the web server when the web server is started
  virtual void start();
  /// Handle OrderPackagesQueues.
  /// @param OrderPackagesQueue A pointer to queues of OrderPackages
  /// @return A queue of HttpResponse.
  virtual Queue<HttpResponse>*
    handleHttpRequest(Queue<OrderPackage>* OrderPackagesQueue) = 0;

  /// Called when the web server stops, in order to allow the web application
  /// clean up and finish as well
  virtual void stop();
};

#endif  // HTTPAPP_H
