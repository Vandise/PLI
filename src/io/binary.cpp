#include "io/binary.hpp"

IO::Binary::Binary(std::string contents)
{
  this->fileContents = contents;
}

void
IO::Binary::exportBuffer()
{
  std::ofstream savefile("bin.out", std::ios::out|std::ios::binary);
  
  //std::string hex = this->stringToHex(this->fileContents);
  if(savefile.good())
  {
    savefile.write(this->fileContents.c_str(), this->fileContents.length());
    savefile.close();
  }
}

void
IO::Binary::import()
{
  std::string buffer;
  std::ostringstream os;
  std::ofstream file;

  file.open("bin.out", std::ios::in|std::ios::binary);
  os << file.rdbuf();
  buffer = os.str();

  std::cout << buffer << std::endl << std::endl;

  //this->fileContents = this->hexToString(buffer);
  this->fileContents = buffer;
  file.close();
  std::cout << this->fileContents << std::endl;
}

std::string
IO::Binary::hexToString(std::string text)
{
  static const char* const lut = "0123456789ABCDEF";
  size_t len = text.length();
  if (len & 1) throw std::invalid_argument("odd length");

  std::string output;
  output.reserve(len / 2);
  for (size_t i = 0; i < len; i += 2)
  {
      char a = text[i];
      const char* p = std::lower_bound(lut, lut + 16, a);
      if (*p != a) throw std::invalid_argument("not a hex digit");

      char b = text[i + 1];
      const char* q = std::lower_bound(lut, lut + 16, b);
      if (*q != b) throw std::invalid_argument("not a hex digit");

      output.push_back(((p - lut) << 4) | (q - lut));
  }
  return output;
}

std::string
IO::Binary::stringToHex(std::string text)
{
  static const char* const lut = "0123456789ABCDEF";
  size_t len = text.length();

  std::string output;
  output.reserve(2 * len);
  for (size_t i = 0; i < len; ++i)
  {
      const unsigned char c = text[i];
      output.push_back(lut[c >> 4]);
      output.push_back(lut[c & 15]);
  }
  return output;
}
