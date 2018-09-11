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
#include "CKeyboardEvent.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <thread>

CKeyboardEvent::CKeyboardEvent( EKeyboardEvent eKey ) : m_eKeyEvent( eKey )
{
}

void CKeyboardEvent::Execute()
{
   HWND oWindow = FindWindowA( NULL, "TEST_!@#" );
   BOOL bRetval = SetForegroundWindow( oWindow );

   // key down
   keybd_event( VK_SPACE, 0x45, KEYEVENTF_EXTENDEDKEY | 0, 0 );

   std::this_thread::sleep_for( std::chrono::microseconds( m_RandGen() % 300 ) + 27us );

   // Simulate a key release
   keybd_event( VK_SPACE, 0x45, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0 );
}
