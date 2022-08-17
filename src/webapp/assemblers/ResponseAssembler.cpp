/// @copyright 2021 ECCI, Universidad de Costa Rica. All rights reserved
/// This code is released under the GNU Public License version 3
/// @author Esteban Castañeda Blanco <esteban.castaneda@ucr.ac.cr>
/// @author Daniel Lizano Morales <daniel.lizanomorales@ucr.ac.cr>
/// @author Andrea Ramírez Rojas <andrea.ramirezrojas@ucr.ac.cr>
/// @author Carlos Ramírez Masís <carlos.ramirezmasis@ucr.ac.cr>

#include "ResponseAssembler.hpp"

ResponseAssembler::ResponseAssembler(Queue<ResultsPackage>*
  resultsPackageQueue,
  Queue<ResponsePackage>* responsePackageQueue) {
  // Consumming and producing queue are set
  this->setConsumingQueue(resultsPackageQueue);
  this->setProducingQueue(responsePackageQueue);
}

ResponseAssembler::~ResponseAssembler() {
}

int ResponseAssembler::run() {
  this->consumeForever();
  return EXIT_SUCCESS;
}

void ResponseAssembler::consume(ResultsPackage resultsPackage) {
  ResponsePackage responsesPackage =
    ResponsePackage(resultsPackage.httpResponse,
    resultsPackage.results, resultsPackage.valid, resultsPackage.url);
  // A ResponsesPackage is produced
  this->produce(responsesPackage);
}
