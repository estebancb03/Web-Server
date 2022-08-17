/// @copyright 2021 ECCI, Universidad de Costa Rica. All rights reserved
/// This code is released under the GNU Public License version 3
/// @author Esteban Castañeda Blanco <esteban.castaneda@ucr.ac.cr>
/// @author Daniel Lizano Morales <daniel.lizanomorales@ucr.ac.cr>
/// @author Andrea Ramírez Rojas <andrea.ramirezrojas@ucr.ac.cr>
/// @author Carlos Ramírez Masís <carlos.ramirezmasis@ucr.ac.cr>

#include "Solver.hpp"

Solver :: Solver(int64_t value) {
  this -> count = 0;
  this -> value = value;
  this -> isEven = true;
  this -> isNegative = true;
}

Solver :: ~Solver() {}

void Solver :: calculate() {
  validateEven();
  validateNegative();
  generatePrimeNumbers();
  generateGoldbachSums();
  generateCount();
}

void Solver :: validateEven() {
  if (this -> value %2 != 0)
    this -> isEven = false;
}

void Solver :: validateNegative() {
  if (this -> value >= 0)
    this -> isNegative = false;
  else
    this -> value *= -1;
}

bool Solver :: validatePrime(int number) {
  bool answer = true;
  if (number > 1) {
    for (int index = 2; index <= number / 2; ++index) {
      if (number % index == 0)
        answer = false;
    }
  } else {
    answer = false;
  }
  return answer;
}

void Solver :: generatePrimeNumbers() {
  int number = this -> value;
  if (number > 5) {
    for (int index = 2; index <= number; ++index) {
      if (validatePrime(index))
        this -> primeNumbers.push_back(index);
    }
  }
}

void Solver :: generateGoldbachSums() {
  this -> isEven ? generateStrongSums() : generateWeakSums();
}

void Solver :: generateStrongSums() {
  std::vector<int64_t> sums;
  std::vector<int64_t> primeNumbers = this -> primeNumbers;
  int value = this -> value;
  int count = primeNumbers.size();
  for (int index = 0; index < count; ++index) {
    for (int jindex = index; jindex < count; ++jindex) {
      if (primeNumbers[index] + primeNumbers[jindex] == value) {
        sums.push_back(primeNumbers[index]);
        sums.push_back(primeNumbers[jindex]);
      }
    }
  }
  this -> sums = sums;
}

void Solver :: generateWeakSums() {
  std::vector<int64_t> sums;
  std::vector<int64_t> primeNumbers = this -> primeNumbers;
  int value = this -> value;
  int count = primeNumbers.size();
  for (int index = 0; index < count; ++index) {
    for (int jindex = index; jindex < count; ++jindex) {
      for (int kindex = jindex; kindex < count; ++kindex) {
        if (primeNumbers[index] + primeNumbers[jindex] +
            primeNumbers[kindex] == value) {
          sums.push_back(primeNumbers[index]);
          sums.push_back(primeNumbers[jindex]);
          sums.push_back(primeNumbers[kindex]);
      }
      }
    }
  }
  this -> sums = sums;
}

void Solver :: generateCount() {
  this -> count = this -> isEven ? this -> sums.size() / 2
                                  : this -> sums.size() / 3;
}

std::vector<std::string> Solver :: getSolutions() {
  std::vector<std::string> results;
  std::vector<int64_t> sums = this -> sums;
  std::string number;
  if (this->isNegative)
    number = "-" + std::to_string(this -> value);
  else
    number = std::to_string(this -> value);
  results.push_back(number);
  if (this -> count > 0) {
    std::string count_result(std::to_string(this -> count) + " sums");
    results.push_back(count_result);
    if (this -> isNegative) {
      int size = sums.size();
      if (this -> isEven) {
        for (int index = 1; index < size; index += 2) {
          std::string sum = std::to_string(this -> value);
          sum.append(" = ");
          sum.append(std::to_string(this -> sums[index - 1]));
          sum.append(" + ");
          sum.append(std::to_string(this -> sums[index]));
          results.push_back(sum);
        }
      } else {
        for (int index = 2; index < size; index += 3) {
          std::string sum = std::to_string(this -> value);
          sum.append(" = ");
          sum.append(std::to_string(this -> sums[index - 2]));
          sum.append(" + ");
          sum.append(std::to_string(this -> sums[index - 1]));
          sum.append(" + ");
          sum.append(std::to_string(this -> sums[index]));
          results.push_back(sum);
        }
      }
    }
  } else {
    results.push_back("NA");
  }
  return results;
}
