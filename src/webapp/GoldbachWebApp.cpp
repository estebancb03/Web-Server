// Copyright 2021 Jeisson Hidalgo-Cespedes. Universidad de Costa Rica. CC BY 4.0

#include <algorithm>
#include <cassert>
#include <iostream>
#include <regex>
#include <stdexcept>
#include <string>

#include "GoldbachWebApp.hpp"
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"

GoldbachWebApp::GoldbachWebApp() {
}

GoldbachWebApp::~GoldbachWebApp() {
}

void GoldbachWebApp::start() {
  // TODO(you): Start producers, consumers, assemblers...
}

void GoldbachWebApp::stop() {
  // TODO(you): Stop producers, consumers, assemblers...
}

bool GoldbachWebApp::handleHttpRequest(HttpRequest& httpRequest,
    HttpResponse& httpResponse) {
  // If the home page was asked
  if (httpRequest.getMethod() == "GET" && httpRequest.getURI() == "/") {
    return this->serveHomepage(httpRequest, httpResponse);
  }

  // If the request starts with "goldbach/" is for this web app
  if (httpRequest.getURI().rfind("/goldbach", 0) == 0) {
    return this->serveGoldbach(httpRequest, httpResponse);
  }

  // Unrecognized request
  return false;
}

// TODO(you): Fix code redundancy in the following methods

bool GoldbachWebApp::serveHomepage(HttpRequest& httpRequest
  , HttpResponse& httpResponse) {
  (void)httpRequest;

  // Set HTTP response metadata (headers)
  this->setResponseHeaders(httpResponse);

  // Build the body of the response
  std::string title = "Goldbach sums";
  httpResponse.body() << "<!DOCTYPE html>\n"
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

  // Send the response to the client (user agent)
  return httpResponse.send();
}

bool GoldbachWebApp::serveGoldbach(HttpRequest& httpRequest
  , HttpResponse& httpResponse) {
  (void)httpRequest;

  // Set HTTP response metadata (headers)
  this->setResponseHeaders(httpResponse);

  // If a number was asked in the form "/goldbach/1223"
  // or "/goldbach?number=1223"
  std::smatch matches;
  this -> regex_mutex.lock();
  std::regex inQuery("^/goldbach(/|\\?number=)([+-]?\\d+(%2C[+-]?\\d+)*)$");
  this -> regex_mutex.unlock();
  if (std::regex_search(httpRequest.getURI(), matches, inQuery)) {
    assert(matches.length() >= 3);
    // const int64_t number = std::stoll(matches[2]);
    std::string num = matches[2];
    this->validRequest(httpResponse, this->analyzeString(num));
  } else {
    // Build the body for an invalid request
    this->invalidRequest(httpResponse);
  }
  // Send the response to the client (user agent)
  return httpResponse.send();
}


std::vector<int64_t> GoldbachWebApp::analyzeString(std::string numbers) {
  const std::string delimiter = "%2C";  //  porque es una coma
  std::string token;
  int64_t number;
  size_t index = 0;
  std::vector<int64_t> numberArray;
  bool condition = true;
  numbers += delimiter;
  index = numbers.find(delimiter);  // encontramos"," y lo usamos como index
  while (index != std::string::npos) {
      number = 0;
      token = numbers.substr(0, index);  // subcadena de , en adelante
      try {
        number = std::stoll(token);  // hacemos stoll para leerlo como un int
      } catch(...) {
          condition = false;
      }
      if (condition != false) {
        numberArray.push_back(number);  // metemos el numero en el array
      }
      numbers.erase(0, index + delimiter.length());  // borramos a numbers
      index = numbers.find(delimiter);
      condition = true;
  }
  return numberArray;
}


void GoldbachWebApp::setResponseHeaders(HttpResponse& httpResponse) {
  httpResponse.setHeader("Server", "AttoServer v1.1");
  httpResponse.setHeader("Content-type", "text/html; charset=ascii");
}

void GoldbachWebApp::validRequest(HttpResponse& httpResponse,
  std::vector<int64_t> inputArray) {
  httpResponse.body() << "<!DOCTYPE html>\n"
    << "<html lang=\"en\">\n"
    << "  <meta charset=\"ascii\"/>\n"
    << "  <title>" << "Results" << "</title>\n"
    << "  <style>body {font-family: monospace} .err {color: red}</style>\n"
    << "  <style>button{ cursor: pointer }\n"
    << "  a{ color: #000000;text-decoration: none; }</style>\n";
  // Loop through array with numbers
  for (size_t index = 0; index < inputArray.size(); ++index) {
    int64_t currentNumber = inputArray[index];
    this->serveGoldbachResult(httpResponse, currentNumber);
  }
  httpResponse.body()  << "<button><a href=\"/\">Back</a></button>\n"
    << "</html>\n";
}

void GoldbachWebApp::invalidRequest(HttpResponse& httpResponse) {
  std::string title = "Invalid request";
  httpResponse.body() << "<!DOCTYPE html>\n"
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

void GoldbachWebApp::serveGoldbachResult(HttpResponse& httpResponse,
  int64_t number) {
  std::string currentTitle = "Goldbach sums of " +
    std::to_string(number);
  std::vector<std::string> currentResults = this->solveGoldbach(number);
  std::string currentSumsAmount = currentResults[0];
  httpResponse.body() << "  <h1>" << currentTitle << "</h1>\n"
    << "  <h2>" << currentSumsAmount << "</h2>\n"
    << "  <ul>";
  // Loop to display results on the page
  for (size_t index = 1; index < currentResults.size(); index++) {
    httpResponse.body() << "<li>" << currentResults[index] << "</li>";
  }
  httpResponse.body() << "  </ul>\n\n"
    << "  <hr>\n";
}

std::vector<std::string> GoldbachWebApp::solveGoldbach(int64_t number) {
  std::vector<std::string> solution;
  // Calculate the goldbach Sums for the current number
  Goldbach* goldbach = new Goldbach(number);
  goldbach -> calculate();
  solution = goldbach -> getSolutions();
  delete goldbach;
  return solution;
}
