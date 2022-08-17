/// @copyright 2021 ECCI, Universidad de Costa Rica. All rights reserved
/// This code is released under the GNU Public License version 3
/// @author Esteban Castañeda Blanco <esteban.castaneda@ucr.ac.cr>
/// @author Daniel Lizano Morales <daniel.lizanomorales@ucr.ac.cr>
/// @author Andrea Ramírez Rojas <andrea.ramirezrojas@ucr.ac.cr>
/// @author Carlos Ramírez Masís <carlos.ramirezmasis@ucr.ac.cr>

#include "Goldbach.hpp"

Goldbach :: Goldbach(std::vector<int64_t> numbers) {
  this -> position = 0;
  this -> threadNumber = 4;
  this -> numbers = numbers;
  this -> solvers.reserve(this -> numbers.size());
}

Goldbach :: ~Goldbach() {
  this -> numbers.clear();
  for (size_t index = 0; index < this -> solvers.size(); ++index)
    delete this -> solvers[index];
}

void Goldbach :: read() {
  for (size_t index = 0; index < numbers.size(); ++index)
    this -> solvers.push_back(new Solver(this -> numbers[index]));
}

void Goldbach :: run() {
  this -> read();
  std::vector<std::thread> threads;
  for (int64_t index = 0; index < this -> threadNumber; ++index)
    threads.push_back(std::thread(calculate, this));
  for (int64_t index = 0; index < this -> threadNumber; ++index)
    threads[index].join();

  for (size_t index = 0; index < this -> solvers.size(); ++index) {
    std::vector<std::string> currentSolution;
    currentSolution = this -> solvers[index] -> getSolutions();
    this -> solutions.push_back(currentSolution);
  }
}

int64_t& Goldbach :: getPosition() {
  return this -> position;
}

std::vector<Solver*>& Goldbach :: getSolvers() {
  return this -> solvers;
}

std::mutex& Goldbach :: getCanAccessPosition() {
  return this -> canAccessPosition;
}

std::vector<std::vector<std::string>> Goldbach :: getSolutions() {
  return this -> solutions;
}

void calculate(Goldbach* goldbach) {
  std::vector<Solver*>& solvers = goldbach -> getSolvers();
  std::mutex& canAccessPosition = goldbach -> getCanAccessPosition();
  int64_t& position = goldbach -> getPosition();
  size_t myPosition = 0;
  while (true) {
    canAccessPosition.lock();
    myPosition = position;
    ++position;
    canAccessPosition.unlock();
    if (myPosition < solvers.size())
      solvers[myPosition] -> calculate();
    else
      break;
  }
}
