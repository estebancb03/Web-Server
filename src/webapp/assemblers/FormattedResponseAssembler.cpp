/// @copyright 2021 ECCI, Universidad de Costa Rica. All rights reserved
/// This code is released under the GNU Public License version 3
/// @author Esteban Castañeda Blanco <esteban.castaneda@ucr.ac.cr>
/// @author Daniel Lizano Morales <daniel.lizanomorales@ucr.ac.cr>
/// @author Andrea Ramírez Rojas <andrea.ramirezrojas@ucr.ac.cr>
/// @author Carlos Ramírez Masís <carlos.ramirezmasis@ucr.ac.cr>

#include "FormattedResponseAssembler.hpp"

FormattedResponseAssembler::FormattedResponseAssembler(Queue<ResponsePackage>*
  responsePackageQueue, Queue<ResponsePackage>*
    formattedResponsePackageQueue) {
  // Consumming and producing queues are set
  this->setConsumingQueue(responsePackageQueue);
  this->setProducingQueue(formattedResponsePackageQueue);
}

FormattedResponseAssembler::~FormattedResponseAssembler() {
}

int FormattedResponseAssembler::run() {
  this->consumeForever();
  return EXIT_SUCCESS;
}

void FormattedResponseAssembler::consume(ResponsePackage responsePackage) {
  // If the home page is requested
  if (responsePackage.url == "/")
    this->formatHomePage(responsePackage);
  // If the results page is requested
  if (responsePackage.url.rfind("/goldbach", 0) == 0) {
    if (responsePackage.valid)
      // If the request is valid
      this->formatValidResponse(responsePackage);
    else
      // If the request is not valid
      this->formatInvalidResponse(responsePackage);
  }
  // A formatted ResponsesPackage is produced
  this->produce(responsePackage);
}

void FormattedResponseAssembler::formatResponseHeaders(ResponsePackage
  responsePackage) {
  responsePackage.httpResponse.setHeader("Server", "AttoServer v1.1");
  responsePackage.httpResponse.setHeader("Content-type",
    "text/html; charset=ascii");
}

void FormattedResponseAssembler::formatHomePage(ResponsePackage
  responsePackage) {
  // Set HTTP response metadata (headers)
  this->formatResponseHeaders(responsePackage);
  // Build the body of the response
  std::string title = "Goldbach sums";
  responsePackage.httpResponse.body() << "<!DOCTYPE html>\n"
    << "<html lang=\"en\">\n"
    << "  <meta charset=\"ascii\"/>\n"
    << "  <title>" << title << "</title>\n"
    << "  <h1>" << title << "</h1>\n"
    << "  <form method=\"get\" action=\"/goldbach\">\n"
    << "    <label for=\"number\">Numbers</label>\n"
    << "    <input type=\"text\" name=\"number\" required/>\n"
    << "    <button type=\"submit\">Calculate</button>\n"
    << "  </form>\n"
    << "  <style>body{font-family:monospace}button{cursor: pointer}</style>\n"
    << "</html>\n";
}

void FormattedResponseAssembler::formatInvalidResponse(ResponsePackage
  responsePackage) {
  // Set HTTP response metadata (headers)
  this->formatResponseHeaders(responsePackage);
  std::string title = "Invalid request";
  responsePackage.httpResponse.body() << "<!DOCTYPE html>\n"
    << "<html lang=\"en\">\n"
    << "  <meta charset=\"ascii\"/>\n"
    << "  <title>" << title << "</title>\n"
    << "  <style>body {font-family: monospace} .err {color: red}</style>\n"
    << "  <style>button{ cursor: pointer }\n"
    << "  a{ color: #000000;text-decoration: none; }</style>"
    << "  <h1 class=\"err\">" << title << "</h1>\n"
    << "  <p>Invalid request for Goldbach sums</p>\n"
    << "  <hr><button><a href=\"/\">Back</a></button>\n"
    << "</html>\n";
}

void FormattedResponseAssembler::formatValidResponse(ResponsePackage
  responsePackage) {
  responsePackage.httpResponse.body() << "<!DOCTYPE html>\n"
    << "<html lang=\"en\">\n"
    << "  <meta charset=\"ascii\"/>\n"
    << "  <title>" << "Results" << "</title>\n"
    << "  <style>body {font-family: monospace} .err {color: red}</style>\n"
    << "  <style>button{ cursor: pointer }\n"
    << "  a{ color: #000000;text-decoration: none; }</style>\n";
  // Put HTML of Goldbach sums
  this->formatGoldbach(responsePackage);
  responsePackage.httpResponse.body()  <<
    "<button><a href=\"/\">Back</a></button>\n"
    << "</html>\n";
}

void FormattedResponseAssembler::formatGoldbach(ResponsePackage
  responsePackage) {
  std::vector< std::vector<std::string> > solutions;
  solutions = responsePackage.results;
  for (size_t index = 0; index < solutions.size(); ++index) {
    std::vector<std::string> currentSolution = solutions[index];
    std::string currentSumsAmount = currentSolution[1];
    std::string currentTitle = "Goldbach sums of " +
      currentSolution[0];
    responsePackage.httpResponse.body() << "  <h1>" <<
      currentTitle << "</h1>\n"
      << "  <h2>" << currentSumsAmount << "</h2>\n"
      << "  <ul>";
    for (size_t index = 2; index < currentSolution.size(); index++)
      responsePackage.httpResponse.body() << "<li>" <<
        currentSolution[index] << "</li>";
    responsePackage.httpResponse.body() << "  </ul>\n\n"
      << "  <hr>\n";
  }
}
