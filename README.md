# Programming Language Implementations
Driving our Application with Flex and Bison

## Integrating Flex and Bison
Flex can be a standalone application; it does not need Bison. Bison, however, depends on Flex. In fact, the scanner object needs to be passed to the parser constructor. The scanner class entirely depends on our lex configuration. If you recall, we wrapped `yylex` in the `Frontend::Scanner` class.

## Telling Bison About Our Scanner
We've told bison that there would be a scanner class in the frontend namespace; now we need to actually include the class definition in order to allow the bison file to compile. If we were to try to compile it currently, we'd get an error like so:

```
error: member access into incomplete type 'Frontend::Scanner'
```

All we need to do is update our code section to include the scanner header file.

```C++

// parser.yy

%code {

#include "scanner.hpp"

#undef yylex
#define yylex scanner.yylex

}
```

Make sure the include is about the yylex definition. The program will not compile if it is not defined first!

## Joining Flex and Bison in Main
There are three things we need to include for our program:
- Filestream headers (required by flex)
- Our Scanner (scanner.hpp)
- Our Parser (parser.tab.hh)

Create a file called `main.cpp` and add the required headers with the main function.

```C++
// main.cpp

#include <fstream>
#include "scanner.hpp"
#include "parser.tab.hh"

int main( const int argc, const char **argv )
{
  return 0;
}

```

We can hardcode in a file to pass to our scanner, but preferably we'd want to pass one in through the command line. The first argument in argv is always the file name. The second argument can be our file:

```C++
// main.cpp

#include <fstream>
#include "scanner.hpp"
#include "parser.tab.hh"

int main( const int argc, const char **argv )
{
  if ( argc == 2 )
  {
    const char * const fileName = argv[1];
    std::ifstream inFile( fileName );

    // ensure a valid file was passed in
    if ( !inFile.good() ) { return 2; }
  }
  return 0;
}
```

Next we'll add our parser and scanner. After which we'll run run "parse" to parse the file. We can validate success or failure by the status code returned (0 for success, any other number for error).

```C++
// main.cpp

#include <fstream>
#include "scanner.hpp"
#include "parser.tab.hh"

int main( const int argc, const char **argv )
{
  if ( argc == 2 )
  {
    const char * const fileName = argv[1];
    std::ifstream inFile( fileName );

    // ensure a valid file was passed in
    if ( !inFile.good() ) { return 2; }

    Frontend::Scanner scanner( &inFile );
    Frontend::Parser parser( scanner );

    if ( parser.parse() != 0 ) { return 3; }

    return 0;
  }
  return 1;
}
``` 

## Compiling our Program
To compile our program, we need to generate the scanner and parser. These are the same commands we've entered before for flex and bison.

Scanner
```bash
# scanner
flex --outfile=lexer.yy.cc grammar.l 
```

Parser
```bash
# parser
bison -d -v parser.yy  
```

Remember, if you're using the version within util and did not install flex and bison on your system: you need to specify the full path. After a few files have been generated, you can compile the program. Be sure to include the path to the Flex header or it will not compile!

Here's an example with clang++ specifying the path to the flex include directory.
```bash
clang++ -Wno-deprecated-register -O0  -g -Wall -std=c++11 main.cpp lexer.yy.cc parser.tab.cc -I/usr/local/opt/flex/include -o my_program
```

## Running the program



## Copyrights
Benjamin J. Anderson - 2017