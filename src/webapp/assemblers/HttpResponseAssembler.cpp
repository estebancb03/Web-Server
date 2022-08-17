/// @copyright 2021 ECCI, Universidad de Costa Rica. All rights reserved
/// This code is released under the GNU Public License version 3
/// @author Esteban Castañeda Blanco <esteban.castaneda@ucr.ac.cr>
/// @author Daniel Lizano Morales <daniel.lizanomorales@ucr.ac.cr>
/// @author Andrea Ramírez Rojas <andrea.ramirezrojas@ucr.ac.cr>
/// @author Carlos Ramírez Masís <carlos.ramirezmasis@ucr.ac.cr>

#include "HttpResponseAssembler.hpp"

HttpResponseAssembler::HttpResponseAssembler(Queue<ResponsePackage>*
  responsesPackageQueue,
  Queue<HttpResponse>* httpResponseQueue) {
  // Consumming and producing queues are set
  this->setConsumingQueue(responsesPackageQueue);
  this->setProducingQueue(httpResponseQueue);
}

HttpResponseAssembler::~HttpResponseAssembler() {
}

int HttpResponseAssembler::run() {
  this->consumeForever();
  return EXIT_SUCCESS;
}

void HttpResponseAssembler::consume(ResponsePackage responsesPackage) {
  // A HttpResponse is produced
  this->produce(responsesPackage.httpResponse);
}
