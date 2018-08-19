#include "stdafx.h"
#include "CCursorEvent.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <thread>

CCursorEvent::CCursorEvent( ECursorEvent eEvent ) : m_eEvent( eEvent ), m_RandGen( std::random_device{}( ) )
{
}

CCursorEvent::CCursorEvent( const CCursorEvent & oEvent ) : CCursorEvent( oEvent.m_eEvent )
{
}

//void CCursorEvent::Execute()
//{
//   switch( m_eEvent )
//   {
//   case CLICK:
//      mouse_event( MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0 );
//      std::this_thread::sleep_for(  std::chrono::microseconds( m_RandGen() % 300  + 25 ) );
//      mouse_event( MOUSEEVENTF_LEFTUP, 0, 0, 0, 0 );
//      break;
//   case MOVE:
//      // TBA
//      break;
//
//   case PAUSE:
//      std::this_thread::sleep_for( std::chrono::microseconds( m_RandGen() % 300 + 25 ) );
//      break;
//   default: break;
//   }
//}

CCursorClick::CCursorClick() : CCursorEvent( CLICK )
{
}

void CCursorClick::Execute()
{
   mouse_event( MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0 );
   std::this_thread::sleep_for( std::chrono::microseconds( m_RandGen() % 300 ) + 27us );
   mouse_event( MOUSEEVENTF_LEFTUP, 0, 0, 0, 0 );
}

CCursorPause::CCursorPause( std::chrono::milliseconds tDuration ) : CCursorEvent( PAUSE ), m_tDuration( tDuration )
{
}

void CCursorPause::Execute()
{
   std::this_thread::sleep_for( std::chrono::milliseconds( m_RandGen() % 75 ) + m_tDuration );
}
