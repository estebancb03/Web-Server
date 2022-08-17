// Copyright 2021 Jeisson Hidalgo-Cespedes. Universidad de Costa Rica. CC BY 4.0
// Serial web server's initial code for parallelization

#ifdef WEBSERVER

#include "HttpServer.hpp"
#include "GoldbachWebApp.hpp"

/// Start the web server
int main(int argc, char* argv[]) {
  // Create the web server
  // HttpServer httpServer;
  // Create a Goldbach web application, and other apps if you want
  GoldbachWebApp goldbachWebApp;
  // Register the web application(s) with the web server
  HttpServer::getInstance().chainWebApp(&goldbachWebApp);
  // Start the web server
  return HttpServer::getInstance().start(argc, argv);
}

#endif  // WEBSERVER
