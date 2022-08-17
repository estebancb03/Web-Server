/// @copyright 2021 ECCI, Universidad de Costa Rica. All rights reserved
/// This code is released under the GNU Public License version 3
/// @author Esteban Castañeda Blanco <esteban.castaneda@ucr.ac.cr>
/// @author Daniel Lizano Morales <daniel.lizanomorales@ucr.ac.cr>
/// @author Andrea Ramírez Rojas <andrea.ramirezrojas@ucr.ac.cr>
/// @author Carlos Ramírez Masís <carlos.ramirezmasis@ucr.ac.cr>

#ifndef URLASSEMBLER_HPP
#define URLASSEMBLER_HPP

#include <mutex>
#include <regex>
#include <vector>
#include <string>

#include "Queue.hpp"
#include "Assembler.hpp"
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"
#include "OrderPackage.hpp"
#include "ResultsPackage.hpp"

class UrlAssembler : public Assembler <OrderPackage, ResultsPackage> {
  /// Objects of this class cannot be copied
  DISABLE_COPY(UrlAssembler);

 private:
  // Mutex for the regex
  std::mutex regexMutex;

 public:
  /**
   * @brief UrlAssembler's constructor
   * @param orderPackageQueue A consuming queue's pointer
   * @param resultsPackageQueue A producing queue's pointer
   */
  explicit UrlAssembler(Queue<OrderPackage>* orderPackageQueue,
    Queue<ResultsPackage>* resultsPackageQueue);

  /**
   * @brief UrlAssembler's destroyer
   */
  virtual ~UrlAssembler();

  /**
   * @brief Overwrites Thread run() function, which creates threads
   * @return Error code, 0 for success
   */
  int run() override;

  /**
   * @brief Consumes an OrderPackage and produces a ResultsPackage from it
   * @param orderPackage
   */
  void consume(OrderPackage orderPackage) override;

 private:
  /**
   * @brief Extract the numbers that are in the string and save them in 
   *        an int64_t array
   * @param numbers
   * @return std::vector<int64_t> 
   */
  std::vector<int64_t> analyzeString(std::string numbers);

  /**
   * @brief The HTML is formatted deppending on whether the home page or the
   *        results page is requested by the user
   * @param httpRequest A HttpRequest pointer
   * @param resultPackage A resultPackage pointer
   */
  void redirectResultPackage(HttpRequest& httpRequest,
    ResultsPackage& resultPackage);

  /**
   * @brief The HTML is formatted deppending on whether the request is valid or not
   * @param httpRequest A HttpRequest pointer
   * @param resultPackage A resultPackage pointer 
   */
  void validateResultPackage(HttpRequest& httpRequest,
    ResultsPackage& resultPackage);
};

#endif  // URIASSEMBLER_HPP
