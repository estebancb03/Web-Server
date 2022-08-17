/// @copyright 2021 ECCI, Universidad de Costa Rica. All rights reserved
/// This code is released under the GNU Public License version 3
/// @author Esteban Castañeda Blanco <esteban.castaneda@ucr.ac.cr>
/// @author Daniel Lizano Morales <daniel.lizanomorales@ucr.ac.cr>
/// @author Andrea Ramírez Rojas <andrea.ramirezrojas@ucr.ac.cr>
/// @author Carlos Ramírez Masís <carlos.ramirezmasis@ucr.ac.cr>

#include "UrlAssembler.hpp"

UrlAssembler::UrlAssembler(Queue<OrderPackage>* orderPackageQueue,
  Queue<ResultsPackage>* resultsPackageQueue) {
  // Consumming and producing queues are set
  this->setConsumingQueue(orderPackageQueue);
  this->setProducingQueue(resultsPackageQueue);
}

UrlAssembler::~UrlAssembler() {
}

int UrlAssembler::run() {
  this->consumeForever();
  return EXIT_SUCCESS;
}

void UrlAssembler::consume(OrderPackage orderPackage) {
  bool valid = false;
  std::string url = "";
  std::vector<int64_t> empty;
  ResultsPackage resultsPackage = ResultsPackage(orderPackage.httpResponse,
    empty, valid, url);
  // HTML is formatted
  this->redirectResultPackage(orderPackage.httpRequest, resultsPackage);
  // A ResultPackage is produced
  this->produce(resultsPackage);
}

void UrlAssembler::redirectResultPackage(HttpRequest& httpRequest,
  ResultsPackage& resultPackage) {
  // If the home page was asked
  if (httpRequest.getMethod() == "GET" && httpRequest.getURI() == "/") {
    resultPackage.url = httpRequest.getURI();
  }
  // If the results page was asked
  if (httpRequest.getURI().rfind("/goldbach", 0) == 0) {
    this->validateResultPackage(httpRequest, resultPackage);
  }
}

void UrlAssembler::validateResultPackage(HttpRequest& httpRequest,
  ResultsPackage& resultPackage) {
  std::smatch matches;
  this -> regexMutex.lock();
  std::regex inQuery("^/goldbach(/|\\?number=)([+-]?\\d+(%2C[+-]?\\d+)*)$");
  this -> regexMutex.unlock();

  if (std::regex_search(httpRequest.getURI(), matches, inQuery)) {
    assert(matches.length() >= 3);
    std::string num = matches[2];
    // resultPackage properties are updated
    resultPackage.valid = true;
    resultPackage.url = httpRequest.getURI();
    resultPackage.numbers = this->analyzeString(num);
  } else {
    // resultPackage properties are updated
    resultPackage.valid = false;
    resultPackage.url = httpRequest.getURI();
  }
}

std::vector<int64_t> UrlAssembler::analyzeString(std::string numbers) {
  const std::string delimiter = "%2C";  //  porque es una coma
  std::string token;
  int64_t number;
  size_t index = 0;
  std::vector<int64_t> numberArray;
  bool condition = true;
  numbers += delimiter;
  index = numbers.find(delimiter);
  while (index != std::string::npos) {
    number = 0;
    token = numbers.substr(0, index);
    try {
      number = std::stoll(token);
    } catch(...) {
      condition = false;
    }
    if (condition != false) {
      numberArray.push_back(number);
    }
    numbers.erase(0, index + delimiter.length());
    index = numbers.find(delimiter);
    condition = true;
  }
  return numberArray;
}
