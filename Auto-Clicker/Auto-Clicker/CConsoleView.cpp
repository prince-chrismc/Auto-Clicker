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

#include "stdafx.h"
#include "CConsoleView.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <iomanip>

CConsoleView::CConsoleView( const std::string & sTitle, double nVersion )
{
   std::wstring swTitle( sTitle.begin(), sTitle.end() );
   SetConsoleTitle( swTitle.c_str() );
   std::cout << sTitle;
   std::cout << std::endl << "Version " << std::setprecision( 2 ) << nVersion << std::endl;
}

size_t CConsoleView::GetNumberOfClicks()
{
   size_t clicks = 0;
   std::cout << std::endl << "How many clicks would you like to perform: ";
   std::cin >> clicks;
   return clicks;
}

size_t CConsoleView::GetIntervalDuration()
{
   size_t sleep = 0;
   std::cout << std::endl << "How long should the delay be between clicks (ms): ";
   std::cin >> sleep;
   return sleep;
}

void CConsoleView::DisplayCountdown()
{
   std::cout << std::endl << "Starting in 3...";
   Sleep( 1000 );
   std::cout << std::endl << "Starting in 2...";
   Sleep( 1000 );
   std::cout << std::endl << "Starting in 1...";
   Sleep( 1000 );
   std::cout << std::endl << "In Progress...";
}

void CConsoleView::DisplayRemaining( size_t nClicks, std::chrono::milliseconds nMs )
{
   COORD c{ 0,11 };
   HANDLE hConsole = GetStdHandle( STD_OUTPUT_HANDLE );
   SetConsoleCursorPosition( hConsole, c );

   size_t etc_ms = ( nClicks > 0 ) ? nClicks * nMs.count() : 0;

   const double etc_min = etc_ms / 60000.0;
   std::cout << std::endl << "Clicks remaining: " << nClicks << ".";
   std::cout << std::endl << "Duration till end (ms): " << etc_ms << ".";
   std::cout << std::endl << "Duration till end (min): " << std::setprecision( 3 ) << etc_min << ".";
}

