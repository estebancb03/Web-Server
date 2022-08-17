/// @copyright 2021 ECCI, Universidad de Costa Rica. All rights reserved
/// This code is released under the GNU Public License version 3
/// @author Esteban Castañeda Blanco <esteban.castaneda@ucr.ac.cr>
/// @author Daniel Lizano Morales <daniel.lizanomorales@ucr.ac.cr>
/// @author Andrea Ramírez Rojas <andrea.ramirezrojas@ucr.ac.cr>
/// @author Carlos Ramírez Masís <carlos.ramirezmasis@ucr.ac.cr>


#ifndef ORDERPACKAGE_HPP
#define ORDERPACKAGE_HPP

#include "Queue.hpp"
#include "Socket.hpp"
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"

class OrderPackage {
 public:
  //  HttpRequest object
  HttpRequest httpRequest;
  //  HttpResponse object
  HttpResponse httpResponse;
  //  Value to do the comparations
  int64_t testValue;

 public:
  /**
   * @brief Stop condition OrderPackage's constructor
   */
  OrderPackage() : httpRequest(HttpRequest(Socket())),
    httpResponse(HttpResponse(Socket())), testValue(-1) {
  }

  /**
   * @brief OrderPackage's constructor
   * @param httpRequest 
   * @param httpResponse 
   */
  explicit OrderPackage(HttpRequest& httpRequest, HttpResponse& httpResponse) :
      httpRequest(httpRequest), httpResponse(httpResponse), testValue(0) {
  }

  /**
   * @brief OrderPackage's destoyer
   */
  virtual ~OrderPackage() {
  }

  /**
   * @brief Operator == overloading
   * @param other 
   * @return int 
   */
  int operator==(const OrderPackage & other) const {
    return this->testValue == other.testValue;
  }
};

#endif  // ORDERPACKAGE_HPP
