/// @copyright 2021 ECCI, Universidad de Costa Rica. All rights reserved
/// This code is released under the GNU Public License version 3
/// @author Esteban Castañeda Blanco <esteban.castaneda@ucr.ac.cr>
/// @author Daniel Lizano Morales <daniel.lizanomorales@ucr.ac.cr>
/// @author Andrea Ramírez Rojas <andrea.ramirezrojas@ucr.ac.cr>
/// @author Carlos Ramírez Masís <carlos.ramirezmasis@ucr.ac.cr>

#ifndef HTTPDISPATCHER_HPP
#define HTTPDISPATCHER_HPP

#include "Assembler.hpp"
#include "OrderPackage.hpp"

class HttpDispatcher : public Assembler<OrderPackage, OrderPackage> {
 public:
  /**
   * @brief Construct a new Http Dispatcher object
   * @param consumingQueue A consuming queue pointer
   * @param producingQueue A producing queue pointer
   */
  explicit HttpDispatcher(Queue<OrderPackage>* consumingQueue,
    Queue<OrderPackage>* producingQueue);
  /**
   * @brief Destroy the Http Dispatcher object
   * 
   */
  virtual ~HttpDispatcher();

  /**
   * @brief Overwrites Thread run() function, which creates threads
   * @return Error code, 0 for success
   */
  int run() override;

  /**
   * @brief Consumes a OrderPackage and produces a new OrderPackage 
   * @param orderPackage 
   */
  void consume(OrderPackage orderPackage) override;
};

#endif  //  !HTTPDISPATCHER_HPP
