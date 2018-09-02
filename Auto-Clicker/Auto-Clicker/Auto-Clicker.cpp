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

#include "CCursorEvent.h"
#include "CClickSequence.h"
#include "CConsoleView.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

int main( int argc, char** argv )
{
   if( argc < 2 ) return -1;

   CConsoleView oDisplay( "Auto-Clicker", 0.0 );

start:
   const size_t clicks = oDisplay.GetNumberOfClicks();
   std::chrono::milliseconds sleep( oDisplay.GetIntervalDuration() );

   //oDisplay.DisplayCountdown();

   HWND oWindow = FindWindowA( NULL, argv[1] );

   keybd_event( VK_LEFT,
                0x45,
                KEYEVENTF_EXTENDEDKEY | 0,
                0 );


   std::this_thread::sleep_for( 5s );


   // Simulate a key release
   keybd_event( VK_LEFT,
                0x45,
                KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP,
                0 );

   ShowWindow( oWindow, SW_MINIMIZE );

   CClickSequence oSequence( { std::make_shared<CCursorClick>( CCursorClick::LEFT ), std::make_shared<CCursorPause>( sleep ) } );
   oSequence.Run( clicks );

   size_t clicksleft = 0;
   do
   {
      clicksleft = oSequence.GetRemainingInteration();
      oDisplay.DisplayRemaining( clicksleft, sleep );
      std::this_thread::sleep_for( sleep );
   } while( clicksleft );

   std::string choice;
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
