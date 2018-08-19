/*

MIT License

Copyright (c) 2018 Chris McArthur, prince.chrismc(at)gmail(dot)com

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

 */

// Auto-Clicker.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "CCursorEvent.h"
#include "CClickSequence.h"

int main( int argc, char** argv )
{
start:

   SetConsoleTitle( L"Auto-Clicker" );
   int clicks, sleep;
   int done = 0;
   long int etc_ms;
   std::string choice;

   std::cout << "AutoClicker";
   std::cout << std::endl << "Version 0.0" << std::endl;

   std::cout << std::endl << "How Many clicks Would You Like To Click: ";
   std::cin >> clicks;

   std::cout << std::endl << "How Much Time Should I Wait Inbetween Clicks (MS): ";
   std::cin >> sleep;

   std::cout << std::endl << "Starting in 3...";
   Sleep( 1000 );
   std::cout << std::endl << "Starting in 2...";
   Sleep( 1000 );
   std::cout << std::endl << "Starting in 1...";
   Sleep( 1000 );
   std::cout << std::endl << "In Progress...";

   CClickSequence oSequence( { std::make_shared<CCursorClick>(), std::make_shared<CCursorPause>( std::chrono::milliseconds( sleep ) ) } );
   oSequence.Run( clicks );

   while( done < clicks )
   {
      done++;

      COORD c;
      c.X = 0;
      c.Y = 11;
      HANDLE hConsole = GetStdHandle( STD_OUTPUT_HANDLE );
      SetConsoleCursorPosition( hConsole, c );

      const long int clicksleft = static_cast<int>(clicks) - static_cast<int>(done);

      if( clicksleft == 0 )
      {
         etc_ms = 0;
      }
      else
      {
         etc_ms = ( static_cast<long int>(clicksleft) + 1 ) * static_cast<int>(sleep);
      }

      const float etc_min = static_cast<long int>(etc_ms) / 60000.0f;
      std::cout << std::endl << "Clicks remaining: " << static_cast<long int>(clicksleft) << ".                ";
      std::cout << std::endl << "Duration till end (ms): " << static_cast<long int>(etc_ms) << ".               ";
      std::cout << std::endl << "Duration till end (min): " << static_cast<float>(etc_min) << ".               ";

      Sleep( sleep );
   }

   std::cout << std::endl << std::endl << "AutoClicker Finished.";
   std::cout << std::endl << std::endl << "(y/n) Again: ";
   std::cin >> choice;
   if( choice == "y" )
   {
      system( "cls" );
      goto start;
   }
   std::cin.get();
}
