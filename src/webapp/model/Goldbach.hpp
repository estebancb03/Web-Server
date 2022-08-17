/// @copyright 2021 ECCI, Universidad de Costa Rica. All rights reserved
/// This code is released under the GNU Public License version 3
/// @author Esteban Castañeda Blanco <esteban.castaneda@ucr.ac.cr>
/// @author Daniel Lizano Morales <daniel.lizanomorales@ucr.ac.cr>
/// @author Andrea Ramírez Rojas <andrea.ramirezrojas@ucr.ac.cr>
/// @author Carlos Ramírez Masís <carlos.ramirezmasis@ucr.ac.cr>

#ifndef GOLDBACH_HPP
#define GOLDBACH_HPP

#include <mutex>
#include <string>
#include <vector>
#include <thread>
#include <iostream>
#include <algorithm>

#include "Solver.hpp"

class Goldbach {
 private:
  // Position in the solvers array
  int64_t position;
  // Number of threads to create
  int64_t threadNumber;
  // Mutex that controls position modification
  std::mutex canAccessPosition;
  // Array with the numbers to calculate their Goldbach sums
  std::vector<int64_t> numbers;
  // Array of Solver objects
  std::vector<Solver*> solvers;
  // Solutions array
  std::vector<std::vector<std::string>> solutions;
  /**
   * @brief Creates a Solver object from each element of the 
   *        numbers array and stores it in the solvers array 
   */
  void read();

 public:
  explicit Goldbach(std::vector<int64_t> numbers);  //  Constructor
  ~Goldbach();  //  Destroyer
  /**
   * @brief calls the read method and creates the threads 
   *        that do the calculations
   */
  void run();
  /**
   * @brief Get the position
   * @return int64_t& 
   */
  int64_t& getPosition();
  /**
   * @brief Get the Solvers array
   * @return std::vector<Solver*>& 
   */
  std::vector<Solver*>& getSolvers();
  /**
   * @brief Get canAccessPosition
   * @return std::mutex& 
   */
  std::mutex& getCanAccessPosition();
  /**
   * @brief Get the Goldbach sums of each number in numbers array
   * @return std::vector< std::vector<std::string> > 
   */
  std::vector< std::vector<std::string> > getSolutions();
};

/**
 * @brief External method that finds the goldbach sums concurrently 
 *        for each object in the Solvers array
 * @param Goldbach* 
 */
void calculate(Goldbach* goldbach);

#endif  // !GOLDBACH_H
