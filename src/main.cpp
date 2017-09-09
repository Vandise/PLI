#include <dlfcn.h>
#include <iostream>
#include <fstream>
#include "shared/config.hpp"
#include "dev/debugnew/debug_new.h"
#include "module/driverLoader.hpp"
#include "generator/bytecode.hpp"
#include "io/binary.hpp"

using namespace std;

int main( const int argc, const char **argv )
{
  if ( argc == 2 )
  {
    Modules::DriverLoader* driver = new Modules::DriverLoader();
    Generator::ByteCode* bcGenerator = new Generator::ByteCode();

    driver->load();
    if (driver->loaded())
    {
      driver->getDriver()->parse(argv[1]);
      driver->getDriver()->getTree()->compile(bcGenerator);
    }

    IO::Binary file(bcGenerator->compile());
    file.exportBuffer();

    delete(bcGenerator);
    delete(driver);
    return 0;
  }
  return 1;
}

