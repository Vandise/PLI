#ifndef __IOBINARY
#define __IOBINARY 1

#include <algorithm>
#include <iostream>
#include <sstream>
#include <bitset>
#include <climits>
#include <stdexcept>
#include <fstream>
#include <string>

namespace IO
{

  class Binary
  {

    private:
      std::string fileContents;

    public:
      Binary(std::string contents);
      void exportBuffer();
      void import();
      std::string stringToHex(std::string text);
      std::string hexToString(std::string text);

  };

}

#endif