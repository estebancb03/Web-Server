/// @copyright 2021 ECCI, Universidad de Costa Rica. All rights reserved
/// This code is released under the GNU Public License version 3
/// @author Esteban Castañeda Blanco <esteban.castaneda@ucr.ac.cr>
/// @author Daniel Lizano Morales <daniel.lizanomorales@ucr.ac.cr>
/// @author Andrea Ramírez Rojas <andrea.ramirezrojas@ucr.ac.cr>
/// @author Carlos Ramírez Masís <carlos.ramirezmasis@ucr.ac.cr>

#include "GoldbachWebApp.hpp"

GoldbachWebApp::GoldbachWebApp() {
  // GoldbachAAssemblers vector size is set
  this->maxGoldbachThreads = DEFAULT_MAX_THREADS;
  this->goldbachAssemblers.resize(maxGoldbachThreads);

  // All queues are initialized
  this->orderPackageQueue = new Queue<OrderPackage>;
  this->resultsPackageQueue1 = new Queue<ResultsPackage>;
  this->resultsPackageQueue2 = new Queue<ResultsPackage>;
  this->responsePackageQueue = new Queue<ResponsePackage>;
  this->formattedResponsePackageQueue = new Queue<ResponsePackage>;
  this->httpResponseQueue = new Queue<HttpResponse>;

  // All assemblers are initialized
  this->urlAssembler = new UrlAssembler(this->orderPackageQueue,
    this->resultsPackageQueue1);
  for (size_t index = 0; index < this->goldbachAssemblers.size(); ++index) {
    goldbachAssemblers[index] = new GoldbachAssembler(
     this->resultsPackageQueue1, this->resultsPackageQueue2);
  }
  this->responseAssembler = new ResponseAssembler(this->resultsPackageQueue2,
    this->responsePackageQueue);
  this->formattedResponseAssembler = new FormattedResponseAssembler(
    this->responsePackageQueue, this->formattedResponsePackageQueue);
  this->httpResponseAssembler = new HttpResponseAssembler(
    this->formattedResponsePackageQueue, this->httpResponseQueue);
}

GoldbachWebApp::~GoldbachWebApp() {
}

void GoldbachWebApp::start() {
  // Start producers, consumers, assemblers...
  this->urlAssembler->startThread();
  for (size_t index = 0; index < this->goldbachAssemblers.size(); ++index)
    goldbachAssemblers[index]->startThread();
  this->responseAssembler->startThread();
  this->formattedResponseAssembler->startThread();
  this->httpResponseAssembler->startThread();
}

void GoldbachWebApp::stop() {
  // Stop producers, consumers, assemblers...
  this->urlAssembler->waitToFinish();
  for (size_t index = 0; index < this->goldbachAssemblers.size(); ++index)
    goldbachAssemblers[index]->waitToFinish();
  this->responseAssembler->waitToFinish();
  this->formattedResponseAssembler->waitToFinish();
  this->httpResponseAssembler->waitToFinish();
}

Queue<HttpResponse>* GoldbachWebApp::handleHttpRequest(
  Queue<OrderPackage>* orderPackagesQueue) {
  //  The OrderPackage is pushed into the queue
  this->orderPackageQueue->push(orderPackagesQueue->pop());
  return this->httpResponseQueue;
}
