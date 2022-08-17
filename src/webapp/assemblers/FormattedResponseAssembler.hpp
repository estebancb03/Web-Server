/// @copyright 2021 ECCI, Universidad de Costa Rica. All rights reserved
/// This code is released under the GNU Public License version 3
/// @author Esteban Castañeda Blanco <esteban.castaneda@ucr.ac.cr>
/// @author Daniel Lizano Morales <daniel.lizanomorales@ucr.ac.cr>
/// @author Andrea Ramírez Rojas <andrea.ramirezrojas@ucr.ac.cr>
/// @author Carlos Ramírez Masís <carlos.ramirezmasis@ucr.ac.cr>

#ifndef FORMATTEDRESPONSEASSEMBLER_HPP
#define FORMATTEDRESPONSEASSEMBLER_HPP

#include <vector>
#include <string>

#include "Queue.hpp"
#include "Assembler.hpp"
#include "HttpResponse.hpp"
#include "ResponsePackage.hpp"

class FormattedResponseAssembler : public Assembler<ResponsePackage,
  ResponsePackage> {
  /// Objects of this class cannot be copied
  DISABLE_COPY(FormattedResponseAssembler);
 public:
 /**
  * @brief FormattedResponseAssembler's constructor
  * @param responsePackageQueue A consuming queue's pointer
  * @param formattedResponsePackageQueue A producing queue's pointer
  */
  explicit FormattedResponseAssembler(Queue<ResponsePackage>*
    responsePackageQueue,
    Queue<ResponsePackage>* formattedResponsePackageQueue);
  /**
   * @brief FormattedResponseAssembler's destroyer
   */
  virtual ~FormattedResponseAssembler();

  /**
   * @brief Overwrites Thread run() function, which creates threads
   * @return Error code, 0 for success
   */
  int run() override;

  /**
   * @brief Consumes a ResponsesPackage and produces a new ResponsesPackage 
   *        with the required format from it
   * @param resultPackage 
   */
  void consume(ResponsePackage responsePackage) override;

 private:
  /**
   * @brief Apply the HTML formatting for the home page
   * @param responsePackage 
   */
  void formatHomePage(ResponsePackage responsePackage);

  /**
   * @brief Apply the HTML formatting for the headers
   * @param responsePackage 
   */
  void formatResponseHeaders(ResponsePackage responsePackage);

  /**
   * @brief Apply the HTML formatting for an invalid request
   * @param responsePackage 
   */
  void formatInvalidResponse(ResponsePackage responsePackage);

  /**
   * @brief Apply the HTML formatting for an valid request
   * @param responsePackage 
   */
  void formatValidResponse(ResponsePackage responsePackage);

  /**
   * @brief Apply the HTML formatting for Goldbach sums
   * @param responsePackage 
   */
  void formatGoldbach(ResponsePackage responsePackage);
};

#endif  // FORMATTEDRESPONSEASSEMBLER_HPP
