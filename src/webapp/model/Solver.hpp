/// @copyright 2021 ECCI, Universidad de Costa Rica. All rights reserved
/// This code is released under the GNU Public License version 3
/// @author Esteban Castañeda Blanco <esteban.castaneda@ucr.ac.cr>
/// @author Daniel Lizano Morales <daniel.lizanomorales@ucr.ac.cr>
/// @author Andrea Ramírez Rojas <andrea.ramirezrojas@ucr.ac.cr>
/// @author Carlos Ramírez Masís <carlos.ramirezmasis@ucr.ac.cr>

#ifndef SOLVER_HPP
#define SOLVER_HPP

#include <string>
#include <vector>
#include <iostream>

class Solver {
 private:
    // Variable to do the calculations
    int64_t value;
    // Sums amount
    int64_t count;
    // Valid if the value is even
    bool isEven;
    // Valid if the value is negative
    bool isNegative;
    // Array containing the sums
    std::vector<int64_t> sums;
    // Array containing the prime numbers
    std::vector<int64_t> primeNumbers;
    /**
     * @brief Check if the number is negative or not
     */
    void validateNegative();

    /**
     * @brief Check if the number is a even or not 
     */
    void validateEven();

    /**
     * @brief Check if the number is prime
     * @param number Number
     * @return 
     *   true: if the number is prime
     *   false: if the number is not prime 
     */
    bool validatePrime(int number);

    /**
     * @brief Create an array with the prime numbers from 2 to the entered number
     */
    void generatePrimeNumbers();

    /**
     * @brief Returns array with the elements of the Goldbach sums for the strong conjecture
     */
    void generateStrongSums();

    /**
     * @brief Returns array with the elements of the Goldbach sums for the weak conjecture
     */
    void generateWeakSums();

    /**
     * @brief Returns array with the elements of the Goldbach sums
     */
    void generateGoldbachSums();

    /**
     * @brief Returns the Goldbach sums amount
     */
    void generateCount();

 public:
    explicit Solver(int64_t value);  // Constructor
    ~Solver();  // Destroyer
    /**
     * @brief The calculation methods of prime numbers and sums are invoked
     */
    void calculate();

    /**
     * @brief Create a string with the Goldbach sums with the proper format
     * @return String array with all the Goldbach sums
     */
    std::vector<std::string> getSolutions();
};

#endif  // !SOLVER_H
