/// @copyright 2021 ECCI, Universidad de Costa Rica. All rights reserved
/// This code is released under the GNU Public License version 3
/// @author Esteban Castañeda Blanco <esteban.castaneda@ucr.ac.cr>
/// @author Daniel Lizano Morales <daniel.lizanomorales@ucr.ac.cr>
/// @author Andrea Ramírez Rojas <andrea.ramirezrojas@ucr.ac.cr>
/// @author Carlos Ramírez Masís <carlos.ramirezmasis@ucr.ac.cr>

#ifndef HTTPASSEMBLER_HPP
#define HTTPASSEMBLER_HPP

#include "Queue.hpp"
#include "Assembler.hpp"
#include "HttpResponse.hpp"
#include "ResponsePackage.hpp"

class HttpResponseAssembler : public Assembler <ResponsePackage,
  HttpResponse> {
  /// Objects of this class cannot be copied
  DISABLE_COPY(HttpResponseAssembler);
 public:
 /**
  * @brief HttpResponseAssembler's constructor
  * @param responsesPackageQueue A consumming queue's pointer
  * @param httpResponseQueue A consumming queue's pointer
  */
  explicit HttpResponseAssembler(Queue<ResponsePackage>*
    responsesPackageQueue,
    Queue<HttpResponse>* httpResponseQueue);

  /**
   * @brief HttpResponseAssembler's destroyer
   */
  virtual ~HttpResponseAssembler();

  /**
   * @brief Overwrites Thread run() function, which creates threads
   * @return Error code, 0 for success
   */
  int run() override;

  /**
   * @brief Consumes a ResponsePackage and produces a HttpResponse from it
   * @param ResponsePackage
   */
  void consume(ResponsePackage responsesPackage) override;
};

#endif  // HTTPASSEMBLER_HPP
