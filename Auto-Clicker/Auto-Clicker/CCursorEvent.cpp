#include "stdafx.h"
#include "CCursorEvent.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <thread>

using namespace std::chrono_literals;

CCursorEvent::CCursorEvent( ECursorEvent eEvent ) : m_eEvent( eEvent ), m_RandGen( std::random_device{}( ) )
{
}

void CCursorEvent::Execute()
{
   switch( m_eEvent )
   {
   case CLICK:
      mouse_event( MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0 );
      std::this_thread::sleep_for(  std::chrono::microseconds( m_RandGen() % 300  + 25 ) );
      mouse_event( MOUSEEVENTF_LEFTUP, 0, 0, 0, 0 );
      break;
   case MOVE:
      // TBA
      break;
   default: break;
   }
}