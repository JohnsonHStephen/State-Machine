#include <sstream>
#include <iostream>
#include <string>

#include "view.h"

std::ofstream View::fileStream;

int View::printToFile(std::string output) {
  fileStream << output << std::endl;
  fileStream.flush();
}

int View::printToConsole(std::string output) {
  std::cout << output << std::endl;
}
