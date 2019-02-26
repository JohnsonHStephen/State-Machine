#ifndef VIEW_H
#define VIEW_H

#include <fstream>
#include <sys/time.h>

class View {
  public:
    static int createFile() {
      std::stringstream strStream;
      strStream << "log";
      struct timeval tp;
      gettimeofday(&tp, NULL);
      strStream << (long long) tp.tv_sec * 1000 + tp.tv_usec / 1000;
      strStream << ".txt";
      fileStream.open(strStream.str(), std::ios::out | std::ios::app);
      if(fileStream.is_open()) {
        return 0;
      }
      return 1;
    }

    static int closeFile() {
      fileStream.close();
      return 1;
    }

    int printToFile(std::string output);
    int printToConsole(std::string output);
  private:
    static std::ofstream fileStream;
};

#endif
