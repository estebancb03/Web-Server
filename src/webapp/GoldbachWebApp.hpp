// Copyright 2021 Jeisson Hidalgo-Cespedes. Universidad de Costa Rica. CC BY 4.0

#ifndef GOLDBACHWEBAPP_HPP
#define GOLDBACHWEBAPP_HPP

#include <mutex>
#include <vector>
#include <string>

#include "HttpApp.hpp"
#include "Goldbach.hpp"
/**
 @brief A web application that calculates Goldbach sums
*/
class GoldbachWebApp : public HttpApp {
  /// Objects of this class cannot be copied
  DISABLE_COPY(GoldbachWebApp);

 public:
  // Mutex for the regex
  std::mutex regex_mutex;

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
   * @brief Handle HTTP requests.
   * @param httpRequest A reference to HttpRequest.
   * @param httpResponse A reference to HttpResponse.
   * @return true If this application handled the request, false otherwise
   */
  bool handleHttpRequest(HttpRequest& httpRequest,
    HttpResponse& httpResponse) override;

  /**
   * @brief Called when the web server stops, in order to allow the web application
   * clean up and finish as well.
   */
  void stop() override;

 protected:
  /**
   * @brief Sends the homepage as Http Response.
   * @param httpRequest A reference to HttpRequest.
   * @param httpResponse A reference to HttpResponse.
   * @return true If this application handled the request, false otherwise.
   */
  bool serveHomepage(HttpRequest& httpRequest, HttpResponse& httpResponse);

  /**
   * @brief Handle a HTTP request that starts with "/goldbach".
   * @param httpRequest A reference to HttpRequest.
   * @param httpResponse A reference to HttpResponse.
   * @return true if the goldbach sum was handled, false if it must be.
   */
  bool serveGoldbach(HttpRequest& httpRequest, HttpResponse& httpResponse);

  /**
   * @brief Puts all the goldbach sums of a number in the body of the page
   * @param httpResponse A reference to HttpResponse.
   * @param number 
   */
  void serveGoldbachResult(HttpResponse& httpResponse,
    int64_t number);

  /**
   * @brief Calculates the goldbach sums for a number and returns an array 
   *        with the sums formatted
   * @param number 
   * @return string vector with the sums formatted
   */
  std::vector<std::string> solveGoldbach(int64_t number);

  /**
   * @brief Convert a given string to an array of inputs.
   * @param numbers String to parse and convert to an int64_t.
   * @return numberArray Vector with the numbers extracted from the string.
   */
  std::vector<int64_t> analyzeString(std::string numbers);

  /**
   * @brief Set the response headers.
   * @param httpResponse A reference to HttpResponse.
   */
  void setResponseHeaders(HttpResponse& httpResponse);

  /**
   * @brief Sends the valid request as Http Response.
   * @param httpResponse A reference to HttpResponse.
   * @param inputArray 
   */
  void validRequest(HttpResponse& httpResponse,
    std::vector<int64_t> inputArray);

  /**
   * @brief Sends the invalid request as Http Response.
   * @param httpResponse A reference to HttpResponse.
   */
  void invalidRequest(HttpResponse& httpResponse);
};

#endif  // GOLDBACHWEBAPP_HPP
