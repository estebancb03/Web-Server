/// @copyright 2021 ECCI, Universidad de Costa Rica. All rights reserved
/// This code is released under the GNU Public License version 3
/// @author Esteban Castañeda Blanco <esteban.castaneda@ucr.ac.cr>
/// @author Daniel Lizano Morales <daniel.lizanomorales@ucr.ac.cr>
/// @author Andrea Ramírez Rojas <andrea.ramirezrojas@ucr.ac.cr>
/// @author Carlos Ramírez Masís <carlos.ramirezmasis@ucr.ac.cr>

#include "GoldbachAssembler.hpp"

GoldbachAssembler::GoldbachAssembler(Queue<ResultsPackage>* preResultsQueue,
  Queue<ResultsPackage>* postResultsQueue) {
  // Consumming and producing are set
  this->setConsumingQueue(preResultsQueue);
  this->setProducingQueue(postResultsQueue);
}

GoldbachAssembler::~GoldbachAssembler() {
}

int GoldbachAssembler::run() {
  this->consumeForever();
  return EXIT_SUCCESS;
}

void GoldbachAssembler::consume(ResultsPackage resultsPackage) {
  ResultsPackage newResultsPackage = ResultsPackage(resultsPackage.httpResponse,
    resultsPackage.numbers, resultsPackage.valid, resultsPackage.url);
  // Goldbach sums are calculated
  Goldbach* goldbach = new Goldbach(newResultsPackage.numbers);
  goldbach->run();
  newResultsPackage.results = goldbach->getSolutions();
  // A ResultPackage with the Goldbach sums is produced
  this->produce(newResultsPackage);
}
