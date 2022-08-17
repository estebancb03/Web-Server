/// @copyright 2021 ECCI, Universidad de Costa Rica. All rights reserved
/// This code is released under the GNU Public License version 3
/// @author Esteban Castañeda Blanco <esteban.castaneda@ucr.ac.cr>
/// @author Daniel Lizano Morales <daniel.lizanomorales@ucr.ac.cr>
/// @author Andrea Ramírez Rojas <andrea.ramirezrojas@ucr.ac.cr>
/// @author Carlos Ramírez Masís <carlos.ramirezmasis@ucr.ac.cr>

#ifndef RESULTSPACKAGE_HPP
#define RESULTSPACKAGE_HPP

#include <vector>
#include <string>

#include "Queue.hpp"
#include "Socket.hpp"
#include "HttpResponse.hpp"

class ResultsPackage {
 public:
  // HttpResponse object
  HttpResponse httpResponse;
  // Request numbers
  std::vector<int64_t> numbers;
  // Value to validate the request
  bool valid;
  // Request url
  std::string url;
  // Value to do the comparations
  int64_t testValue;

  // Goldbach sums
  std::vector<std::vector<std::string>> results;

 public:
  /**
   * @brief Stop condition ResultsPackage's constructor
   */
  ResultsPackage() : httpResponse(HttpResponse(Socket())), testValue(-1) {
  }

  /**
   * @brief ResultPackage's constructor
   * @param httpResponse 
   * @param numbers 
   * @param valid 
   * @param url 
   */
  explicit ResultsPackage(HttpResponse& httpResponse,
    std::vector<int64_t> numbers, bool valid, std::string url) :
      httpResponse(httpResponse),
    numbers(numbers), valid(valid), url(url), testValue(0) {
  }

  /**
   * @brief ResultPackage's destroyer
   */
  virtual ~ResultsPackage() {
  }

  /**
   * @brief Operator == overloading
   * @param other 
   * @return int 
   */
  int operator==(const ResultsPackage & other) const {
    return this->testValue == other.testValue;
  }
};

#endif  // RESULTSPACKAGE_HPP
