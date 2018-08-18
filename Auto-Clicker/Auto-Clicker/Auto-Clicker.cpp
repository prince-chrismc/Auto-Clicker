// Auto-Clicker.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

int main( int argc, char** argv )
{
start:

   SetConsoleTitle( L"Auto-Clicker" );
   int x = 0, y = 0, clicks, sleep;
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

   while( done < clicks )
   {
      mouse_event( MOUSEEVENTF_LEFTDOWN, x, y, 0, 0 );
      mouse_event( MOUSEEVENTF_LEFTUP, x, y, 0, 0 );
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
