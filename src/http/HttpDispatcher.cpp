/// @copyright 2021 ECCI, Universidad de Costa Rica. All rights reserved
/// This code is released under the GNU Public License version 3
/// @author Esteban Castañeda Blanco <esteban.castaneda@ucr.ac.cr>
/// @author Daniel Lizano Morales <daniel.lizanomorales@ucr.ac.cr>
/// @author Andrea Ramírez Rojas <andrea.ramirezrojas@ucr.ac.cr>
/// @author Carlos Ramírez Masís <carlos.ramirezmasis@ucr.ac.cr>

#include "HttpDispatcher.hpp"

HttpDispatcher::HttpDispatcher(Queue<OrderPackage>* consumingQueue,
  Queue<OrderPackage>* producingQueue) {
  setConsumingQueue(consumingQueue);
  setProducingQueue(producingQueue);
}


HttpDispatcher::~HttpDispatcher() {
}

int HttpDispatcher::run() {
  this->consumeForever();
  return EXIT_SUCCESS;
}

void HttpDispatcher::consume(OrderPackage orderPackage) {
  this -> produce(orderPackage);
}
