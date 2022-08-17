/// @copyright 2021 ECCI, Universidad de Costa Rica. All rights reserved
/// This code is released under the GNU Public License version 3
/// @author Esteban Castañeda Blanco <esteban.castaneda@ucr.ac.cr>
/// @author Daniel Lizano Morales <daniel.lizanomorales@ucr.ac.cr>
/// @author Andrea Ramírez Rojas <andrea.ramirezrojas@ucr.ac.cr>
/// @author Carlos Ramírez Masís <carlos.ramirezmasis@ucr.ac.cr>

#ifndef RESPONSEPACKAGE_HPP
#define RESPONSEPACKAGE_HPP

#include <vector>
#include <string>

#include "Queue.hpp"
#include "Socket.hpp"
#include "Consumer.hpp"
#include "HttpServer.hpp"
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"

class ResponsePackage {
 public:
  // HttpResponse object
  HttpResponse httpResponse;
  // Goldbach sums
  std::vector<std::vector<std::string>> results;
  // Value to validate the request
  bool valid;
  // Request url
  std::string url;
  // Value to do the comparations
  int64_t testValue;

  /**
   * @brief Stop condition ResponsePackage's constructor
   */
  ResponsePackage() : httpResponse(HttpResponse(Socket())), testValue(-1) {
  }

  /**
   * @brief ResponsePackage's constructor
   * @param httpResponse 
   * @param results 
   * @param valid 
   * @param url 
   */
  explicit ResponsePackage(HttpResponse& httpResponse,
   std::vector<std::vector<std::string>> results, bool valid,
    std::string url) :
    httpResponse(httpResponse), results(results),
      valid(valid), url(url), testValue(0) {
  }

  /**
   * @brief ResponsePackage's destroyer
   */
  virtual ~ResponsePackage() {
  }

  /**
   * @brief Operator == overloading
   * @param other 
   * @return int 
   */
  int operator==(const ResponsePackage & other) const {
    return this->testValue == other.testValue;
  }
};

#endif  // !RESPONSEPACKAGE_HPP
