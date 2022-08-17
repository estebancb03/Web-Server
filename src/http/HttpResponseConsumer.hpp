/// @copyright 2021 ECCI, Universidad de Costa Rica. All rights reserved
/// This code is released under the GNU Public License version 3
/// @author Esteban Castañeda Blanco <esteban.castaneda@ucr.ac.cr>
/// @author Daniel Lizano Morales <daniel.lizanomorales@ucr.ac.cr>
/// @author Andrea Ramírez Rojas <andrea.ramirezrojas@ucr.ac.cr>
/// @author Carlos Ramírez Masís <carlos.ramirezmasis@ucr.ac.cr>

#ifndef HTTPREPONSECONSUMER_HPP
#define HTTPREPONSECONSUMER_HPP

#include "Consumer.hpp"
#include "HttpResponse.hpp"

class HttpResponseConsumer : public Consumer<HttpResponse> {
 public:
  /**
   * @brief HttpResponseConsumer's constructor
   * @param httpResponseQueue A consuming queue's pointer
   */
  explicit HttpResponseConsumer(Queue<HttpResponse>* httpResponseQueue);

  /**
   * @brief HttpResponseConsumer's destroyer
   * 
   */
  virtual ~HttpResponseConsumer();

  /**
   * @brief Overwrites Thread run() function, which creates threads
   * @return Error code, 0 for success
   */
  int run() override;

  /**
   * @brief Consume a HttpResponse
   * @param httpResponse 
   */
  void consume(HttpResponse httpResponse) override;
};

#endif  // HTTPREPONSECONSUMER_HPP
