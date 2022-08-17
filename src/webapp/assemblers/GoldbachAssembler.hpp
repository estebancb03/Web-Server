/// @copyright 2021 ECCI, Universidad de Costa Rica. All rights reserved
/// This code is released under the GNU Public License version 3
/// @author Esteban Castañeda Blanco <esteban.castaneda@ucr.ac.cr>
/// @author Daniel Lizano Morales <daniel.lizanomorales@ucr.ac.cr>
/// @author Andrea Ramírez Rojas <andrea.ramirezrojas@ucr.ac.cr>
/// @author Carlos Ramírez Masís <carlos.ramirezmasis@ucr.ac.cr>

#ifndef GOLDBACHASSEMBLER_HPP
#define GOLDBACHASSEMBLER_HPP

#include "Queue.hpp"
#include "Goldbach.hpp"
#include "Assembler.hpp"
#include "HttpResponse.hpp"
#include "ResultsPackage.hpp"

class GoldbachAssembler : public Assembler <ResultsPackage, ResultsPackage> {
  /// Objects of this class cannot be copied
  DISABLE_COPY(GoldbachAssembler);

 public:
  /**
   * @brief GoldbachAssembler's constructor
   * @param preResultsQueue A consuming queue's pointer
   * @param postResultsQueue A producing queue's pointer
   */
  explicit GoldbachAssembler(Queue<ResultsPackage>* preResultsQueue,
    Queue<ResultsPackage>* postResultsQueue);

  /**
   * @brief GoldbachAssembler's destroyer
   */
  virtual ~GoldbachAssembler();

  /**
   * @brief Overwrites Thread run() function, which creates threads
   * @return Error code, 0 for success
   */
  int run() override;

  /**
   * @brief Consumes a ResultPackage and produces a new ResultsPackage 
   *        with the Goldbach sums from it
   * @param resultPackage 
   */
  void consume(ResultsPackage resultPackage) override;
};

#endif  // GOLDBACHASSEMBLER_HPP
