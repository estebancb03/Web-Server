/// @copyright 2021 ECCI, Universidad de Costa Rica. All rights reserved
/// This code is released under the GNU Public License version 3
/// @author Esteban Castañeda Blanco <esteban.castaneda@ucr.ac.cr>
/// @author Daniel Lizano Morales <daniel.lizanomorales@ucr.ac.cr>
/// @author Andrea Ramírez Rojas <andrea.ramirezrojas@ucr.ac.cr>
/// @author Carlos Ramírez Masís <carlos.ramirezmasis@ucr.ac.cr>

#ifndef GOLDBACHWEBAPP_HPP
#define GOLDBACHWEBAPP_HPP

#include <vector>

#include "Queue.hpp"
#include "HttpApp.hpp"
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"
#include "OrderPackage.hpp"
#include "UrlAssembler.hpp"
#include "ResultsPackage.hpp"
#include "ResponsePackage.hpp"
#include "ResponseAssembler.hpp"
#include "GoldbachAssembler.hpp"
#include "HttpResponseAssembler.hpp"
#include "FormattedResponseAssembler.hpp"

#define DEFAULT_MAX_THREADS sysconf(_SC_NPROCESSORS_ONLN);

class HttpServer;
class UrlAssembler;
class GoldbachAssembler;
class ResponseAssembler;
class HttpResponseAssembler;
class FormattedResponseAssembler;

/**
 @brief A web application that calculates Goldbach sums
*/
class GoldbachWebApp : public HttpApp {
  /// Objects of this class cannot be copied
  DISABLE_COPY(GoldbachWebApp);

 private:
  /// Indicates max amount of GoldbachAssembler threads
  int64_t maxGoldbachThreads;
  /// Queue of OrderPackages
  Queue<OrderPackage>* orderPackageQueue;
  /// Queue of ResultsPackages
  Queue<ResultsPackage>* resultsPackageQueue1;
  /// Queue of ResultsPackages
  Queue<ResultsPackage>* resultsPackageQueue2;
  /// Queue of ResponsesPackages
  Queue<ResponsePackage>* responsePackageQueue;
  /// Queue of ResponsesPackages
  Queue<ResponsePackage>* formattedResponsePackageQueue;
  /// Queue of HttpResponses
  Queue<HttpResponse>* httpResponseQueue;

  // Assemblers down below:

  /// A pointer to an UrlAssembler object
  UrlAssembler* urlAssembler;
  /// A pointer to a vector of UrlAssembler objects
  std::vector<GoldbachAssembler*> goldbachAssemblers;
  /// A pointer to a ResponseAssembler object
  ResponseAssembler* responseAssembler;
  /// A pointer to a FormattedResponseAssembler object
  FormattedResponseAssembler* formattedResponseAssembler;
  /// A pointer to an HttpResponseAssembler object
  HttpResponseAssembler* httpResponseAssembler;

 public:
  /**
   * @brief Construct a new Goldbach Web App object.
   */
  GoldbachWebApp();

  /**
   * @brief Destroy the Goldbach Web App object.
   */
  ~GoldbachWebApp();

  /**
   * @brief Called by the web server when the web server is started.
   */
  void start() override;

  /**
   * @brief Consumes OrderPackages from a queue
   * @param orderPackageQueue A consuming queue pointer
   * @return A queue of HttpResponse
   */
  Queue<HttpResponse>* handleHttpRequest(
    Queue<OrderPackage>* orderPackageQueue) override;

  /**
   * @brief Called when the web server stops, in order to allow the web application
   * Clean up and finish as well.
   */
  void stop() override;
};

#endif  // GOLDBACHWEBAPP_HPP
