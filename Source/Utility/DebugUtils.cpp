/**
 *  @file       DebugUtils.cpp
 *  @brief      Implementation of debugging & utility methods
 *  @author     Mark L. Short
 *  @date       March 12, 2017
 *
 *  <b>Course:</b>     CPSC 5377 Advanced Game Programming
 *
 *  <b>Instructor:</b> Sean Orme
 *
 *  <b>Assignment:</b> Zelda1 Project
 */

/**
 *  @note  the following is currently only supported on the windows platforms
 */

#ifdef _MSC_VER

// turn off silly warnings that encourage use of xxxx_s functions
#define _CRT_SECURE_NO_WARNINGS
#ifdef _DEBUG
    #define _CRTDBG_MAP_ALLOC
    #include <stdlib.h>
    #include <crtdbg.h>
#endif
#ifdef _DEBUG
    #define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
    #define new DEBUG_NEW
#endif

#include <stdlib.h>
#include <stdarg.h>
#include <Windows.h>

#include "DebugUtils.h"

#ifdef _DEBUG

    #if defined(UNICODE) || defined(_UNICODE)
        std::wofstream dbg;
    #else
        std::ofstream  dbg;
    #endif

#endif


namespace util
{
    int DebugTrace(const TCHAR* szFmt, ...) noexcept
    {
        TCHAR szDebugMsg[512] = { 0 };

        va_list	vaArgs;
        va_start(vaArgs, szFmt);

        // use the format string and arguments to construct the debug output string
        int iReturnVal = _vsntprintf(szDebugMsg,
                                     _countof(szDebugMsg) - 1,
                                     szFmt,
                                     vaArgs);

        va_end(vaArgs);

        ::OutputDebugString(szDebugMsg);
        return iReturnVal;
    };

    TCHAR* GetModulePath(TCHAR* szModulePath, size_t cchLen) noexcept
    {
        TCHAR* szReturnVal = nullptr;

        // Get the executable file path
        TCHAR szModuleFileName[_MAX_PATH] = { 0 };

        // Note, if HANDLE is nullptr, GetModuleFileName is supposed to return the file
        // path to the current executable, but it appears that it is inconsistently
        // returning filename as well....
        DWORD dwStrLen = ::GetModuleFileName (nullptr, szModuleFileName,
                                              _countof(szModuleFileName));

        if (dwStrLen != 0)
        {
            TCHAR szDir[_MAX_PATH] = { 0 };

            _tsplitpath(szModuleFileName, szDir, &szDir[_MAX_DRIVE - 1], nullptr, nullptr);

            szReturnVal = _tcsncpy(szModulePath, szDir, cchLen);
        }

        return szReturnVal;
    };

}  // namespace util


#else

///////////////////////////////////////////////////////////////////////////////
// NOT IMPLIMENTED

#endif  // #ifdef _MSC_VER

