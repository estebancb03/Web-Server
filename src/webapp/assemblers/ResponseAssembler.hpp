/// @copyright 2021 ECCI, Universidad de Costa Rica. All rights reserved
/// This code is released under the GNU Public License version 3
/// @author Esteban Castañeda Blanco <esteban.castaneda@ucr.ac.cr>
/// @author Daniel Lizano Morales <daniel.lizanomorales@ucr.ac.cr>
/// @author Andrea Ramírez Rojas <andrea.ramirezrojas@ucr.ac.cr>
/// @author Carlos Ramírez Masís <carlos.ramirezmasis@ucr.ac.cr>

#ifndef RESPONSEASSEMBLER_HPP
#define RESPONSEASSEMBLER_HPP

#include "Queue.hpp"
#include "Assembler.hpp"
#include "HttpResponse.hpp"
#include "ResultsPackage.hpp"
#include "ResponsePackage.hpp"

class ResponseAssembler : public Assembler <ResultsPackage, ResponsePackage> {
  /// Objects of this class cannot be copied
  DISABLE_COPY(ResponseAssembler);

 public:
  /**
   * @brief ResponseAssembler's constructor
   * @param resultsPackageQueue A consuming queue's pointer
   * @param responsePackageQueue A producing queue's pointer
   */
  explicit ResponseAssembler(Queue<ResultsPackage>* resultsPackageQueue,
    Queue<ResponsePackage>* responsePackageQueue);

  /**
   * @brief ResponseAssembler's destroyer
   */
  virtual ~ResponseAssembler();

  /**
   * @brief Overwrites Thread run() function, which creates threads
   * @return Error code, 0 for success
   */
  int run() override;

  /**
   * @brief Consumes a ResultsPackage and produces a ResponsesPackage from it
   * @param resultsPackage
   */
  void consume(ResultsPackage resultsPackage) override;
};

#endif  // RESPONSEASSEMBLER_HPP
