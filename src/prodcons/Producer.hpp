/// @copyright 2020 ECCI, Universidad de Costa Rica. All rights reserved
/// This code is released under the GNU Public License version 3
/// @author Jeisson Hidalgo-Céspedes <jeisson.hidalgo@ucr.ac.cr>

#ifndef PRODUCER_HPP
#define PRODUCER_HPP

#include <cassert>

#include "Queue.hpp"
#include "Thread.hpp"

/**
 * @brief A template that generates abstract base classes for Producers
 * Producers are execution threads. They create elements that are pushed
 * to a queue. These elements will be popped by a consumer thread.
 */
template <typename DataType>
class Producer : public virtual Thread {
  DISABLE_COPY(Producer);

 protected:
  Queue<DataType>* producingQueue;

 public:
  /**
   * @brief Constructor
   * @param queue
   */
  explicit Producer(Queue<DataType>* producingQueue = nullptr)
    : producingQueue(producingQueue) {
  }

  /// Destructor
  virtual ~Producer() {
  }

  /**
   * @brief da acceso a la cola donde esta hilo produce
   * @return la cola donde esta hilo produce
   */
  inline Queue<DataType>* getProducingQueue() {
    return this->producingQueue;
  }

  /**
   * @brief setea la cola donde los hilos producen los elementos
   * @param producingQueue 
   */
  inline void setProducingQueue(Queue<DataType>* producingQueue) {
    this->producingQueue = producingQueue;
  }

  /**
   * @brief añade a la lista la data que se encuentra 
   * en la fila de produccion.
   * @param data 
   */
  virtual void produce(const DataType& data) {
    assert(this->producingQueue);
    this->producingQueue->push(data);
  }
};

#endif  // PRODUCER_HPP
