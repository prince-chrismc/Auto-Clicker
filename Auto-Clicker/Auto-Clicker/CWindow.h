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

#pragma once

#include <mutex>
#include <memory>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

class CWindow final
{
public:
   ~CWindow() = default;

   CWindow( const CWindow& ) = delete;
   CWindow( const CWindow&& ) = delete;
   CWindow& operator=( const CWindow& ) = delete;
   CWindow& operator=( const CWindow&& ) = delete;

   static CWindow& CreateInstance( const std::string_view& name ) noexcept { std::call_once( s_Flag, [ &name = name ]() { s_Instance.reset( new CWindow( name ) ); } ); return *s_Instance; }
   static const CWindow& GetInstance() { if( s_Instance ) return *s_Instance;  throw std::exception{ "Object not initialized" }; }

   explicit operator bool() const { return ( m_oWindow != NULL ); }

   const CWindow& SetAsFocus() const;

private:
   explicit CWindow( const std::string_view& name );

   HWND m_oWindow;

   static std::once_flag s_Flag;
   static std::unique_ptr<CWindow> s_Instance;
};
