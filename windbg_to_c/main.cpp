﻿#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include "windbg_structure.hpp"

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        for (;;) 
        {
            std::cout << "Enter dumped WinDbg data-type: ";

            std::string structString;
            for (;;)
            {
                std::string currentLine;
                std::getline( std::cin, currentLine );
                if (currentLine.empty( ))
                    break;
                if ((currentLine.at( 0 ) == 'X' || currentLine.at( 0 ) == 'x') ||
                    (currentLine.at( 0 ) == 'Q' || currentLine.at( 0 ) == 'q'))
                    goto quit;
                structString.append( currentLine + '\n' );
            }

            std::string structStringTrimmed = trim_trailing_and_leading_whitespaces( structString.c_str( ) );
            if (structStringTrimmed.empty( ))
                break;

            windbg_structure s( structStringTrimmed + '\n' );

            std::cout << s.as_string( 0 ) << std::endl;
        }

    quit:
        std::cout << "Press any key to exit...";
        getchar( );
    }
    else 
    {
        std::ifstream input(argv[1]);
        std::ofstream output("result.txt");
        
        std::stringstream inputstream;
        inputstream << input.rdbuf();
        windbg_structure s(inputstream.str());
        
        output << s.as_string(0) << std::endl;
    }
    
    return EXIT_SUCCESS;
}