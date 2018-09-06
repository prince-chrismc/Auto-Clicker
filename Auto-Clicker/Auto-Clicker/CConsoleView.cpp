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
#include <thread>

CConsoleView::CConsoleView( const std::string & sTitle, double nVersion )
   : m_sTitle( sTitle )
   , m_nVersion( nVersion )
{
   _PrintTitle();
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

bool CConsoleView::GetRunAgain()
{
   bool bRetval = false;
   std::string choice = "";

   std::cout << std::endl << std::endl << "(y/n) Again: ";
   std::cin >> choice;
   if( choice == "y" )
   {
      bRetval = true;
   }

   std::cin.get();
   return bRetval;
}

void CConsoleView::DisplayCountdown()
{
   std::cout << std::endl << "Starting in 3...";
   std::this_thread::sleep_for( 1s );
   std::cout << std::endl << "Starting in 2...";
   std::this_thread::sleep_for( 1s );
   std::cout << std::endl << "Starting in 1...";
   std::this_thread::sleep_for( 1s );
   std::cout << std::endl << "In Progress...";
}

void CConsoleView::DisplayRemaining( size_t nClicks, std::chrono::milliseconds nMs )
{
   COORD c{ 0,11 };
   HANDLE hConsole = GetStdHandle( STD_OUTPUT_HANDLE );
   SetConsoleCursorPosition( hConsole, c );

   std::chrono::milliseconds nEtcInMs( ( nClicks > 0 ) ? nClicks * nMs.count() : 0 );
   std::chrono::minutes nEtcMinutes = std::chrono::duration_cast<std::chrono::minutes>( nEtcInMs );
   std::chrono::hours nEtcHours = std::chrono::duration_cast<std::chrono::hours>( nEtcInMs );

   std::cout << std::endl << "Clicks remaining: " << nClicks << ".";
   std::cout << std::endl << "Estimated time to completion: " << nEtcInMs.count() << "ms";
   std::cout << std::endl << "or...                         " << nEtcHours.count() << "hrs and " << nEtcMinutes.count() % 60 << "min.";
}

void CConsoleView::DisplayFinished()
{
   std::cout << std::endl << std::endl << "AutoClicker Finished.";
}

void CConsoleView::Reset()
{
   system( "cls" );
   _PrintTitle();
}

void CConsoleView::_PrintTitle()
{
   std::wstring swTitle( m_sTitle.begin(), m_sTitle.end() );
   SetConsoleTitle( swTitle.c_str() );
   std::cout << m_sTitle << std::endl << "Version ";
   printf( "%.01f\r\n", m_nVersion );
}
