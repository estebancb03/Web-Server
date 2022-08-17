/// @copyright 2020 ECCI, Universidad de Costa Rica. All rights reserved
/// This code is released under the GNU Public License version 3
/// @author Jeisson Hidalgo-Céspedes <jeisson.hidalgo@ucr.ac.cr>

#include <cassert>
#include <iostream>
#include "Thread.hpp"
/**
 * @brief Constructor de la clase Thread.
 */
Thread::Thread() {
}
/**
 * @brief Destructor de la clase Thread.
 */
Thread::~Thread() {
  delete this->thread;
}
/**
 * @brief Método que inicia el hilo.
 * @return EXIT_SUCCESS.
 */
int Thread::startThread() {
  assert(this->thread == nullptr);
  this->thread = new std::thread( &Thread::run, this );
  return EXIT_SUCCESS;
}
/**
 * @brief Método que detiene el hilo.
 * @return EXIT_SUCCESS.
 */
int Thread::waitToFinish() {
  assert(this->thread);
  this->thread->join();

  delete this->thread;
  this->thread = nullptr;

  return EXIT_SUCCESS;
}
