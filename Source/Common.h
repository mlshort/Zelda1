/**
 *  @file       Common.h
 *  @brief      Common type definitions
 *  @author     Mark L. Short
 *  @date       February 12, 2017
 *
 *  <b>Course:</b>     CPSC 5377 Advanced Game Programming
 *
 *  <b>Instructor:</b> Sean Orme
 *
 *  <b>Assignment:</b> Zelda1 Project
 */
#pragma once

#if !defined(__COMMON_H__)
#define __COMMON_H__

#ifndef _INC_TCHAR
    #include <tchar.h>
#endif
#ifndef _IOSTREAM_
    #include <iostream>
#endif
#ifndef _STRING_
    #include <string>
#endif

#if !defined(_TSTRING_)
#define _TSTRING_
    #if defined(UNICODE) || defined(_UNICODE)
        #define tstring std::wstring
        #define tcout   std::wcout
        #define tcin    std::wcin
    #else
        #define tstring std::string
        #define tcout   std::cout
        #define tcin    std::cin
    #endif
#endif

//Basic Types
typedef float           DEGREES;

//========================================
//Base Game Constants
//========================================
constexpr const uint32_t g_SCREEN_WIDTH  = 800;// 1920;
constexpr const uint32_t g_SCREEN_HEIGHT = 600; // 1080;
constexpr const uint32_t GAME_FPS      = 100;
constexpr const size_t   INVALID_ACTOR = static_cast< size_t >(-1);

//Event Types
enum GAME_EVENT
{
    GAME_NA,
    GAME_UP,
    GAME_DOWN,
    GAME_LEFT,
    GAME_RIGHT,
    GAME_SPACE,
    GAME_SHIFT,
    GAME_TAB,
    GAME_B,
    GAME_VIEW_SIZE,
    GAME_QUIT,
    GAME_NUM_EVENTS
};

enum ACTOR_T
{
    ACT_INVALID = -1,
    ACT_RED_OCTOROK,
    ACT_RED_LEEVER,
    ACT_BLUE_OCTOROK,
    ACT_BLUE_LEEVER,
    ACT_NUM_ACTORS
};

constexpr bool IsValidType(ACTOR_T act) noexcept
{
    return (act != ACT_INVALID);
};


#endif