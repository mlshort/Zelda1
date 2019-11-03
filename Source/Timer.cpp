/**
 *  @file       Timer.cpp
 *  @brief      CTimer class implementation
 *  @author     Mark L. Short
 *  @date       March 12, 2017
 *
 *  <b>Course:</b>     CPSC 5377 Advanced Game Programming
 *
 *  <b>Instructor:</b> Sean Orme
 *
 *  <b>Assignment:</b> Zelda1 Project
 */
#ifdef _DEBUG
    #define _CRTDBG_MAP_ALLOC
    #include <stdlib.h>
    #include <crtdbg.h>
#endif
#ifdef _DEBUG
    #define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
    #define new DEBUG_NEW
#endif

#include "SDL.h"

#include "Utility\DebugUtils.h"

#include "Timer.h"


CTimer::~CTimer(void) noexcept
{
#ifdef _DEBUG
    util::DebugTrace(_T("%S \n"), __FUNCTION__);
#endif
    SDL_QuitSubSystem(SDL_INIT_TIMER);
}

bool CTimer::Initialize(void) noexcept
{
    bool bResult = (SDL_InitSubSystem(SDL_INIT_TIMER) == 0);

    if (GAME_FPS > 0)
    {
        m_dwMsPerFrame = 1000 / GAME_FPS;
    }

    return bResult;
};

void CTimer::Start(void) noexcept
{
    //Start the timer
    m_bStarted = true;

    //Unpause the timer
    m_bPaused = false;

    // Gets the number of milliseconds since the SDL library initialization.
    m_dwStartTicks = SDL_GetTicks();

    m_dwPausedTicks = 0;
}

void CTimer::Stop(void) noexcept
{
    //Stop the timer
    m_bStarted = false;

    //Unpause the timer
    m_bPaused = false;

    m_dwStartTicks  = 0;
    m_dwPausedTicks = 0;
}

void CTimer::Pause(void) noexcept
{
    //If the timer is running and isn't already paused
    if ( m_bStarted && !m_bPaused )
    {
        //Pause the timer
        m_bPaused = true;

        //Calculate the paused ticks
        m_dwPausedTicks = SDL_GetTicks() - m_dwStartTicks;
        m_dwStartTicks  = 0;
    }
}

void CTimer::Resume(void) noexcept
{
    //If the timer is paused
    if ( m_bStarted && m_bPaused )
    {
        //Unpause the timer
        m_bPaused = false;

        //Reset the starting ticks
        m_dwStartTicks = SDL_GetTicks() - m_dwPausedTicks;

        //Reset the paused ticks
        m_dwPausedTicks = 0;
    }
}

uint32_t CTimer::GetTicks(void) const noexcept
{
    // If the timer is running
    if( m_bStarted == true )
    {
        //If the timer is paused
        if( m_bPaused == true )
        {
            //Return the number of ticks when the timer was paused
            return m_dwPausedTicks;
        }
        else
        {
            //Return the current time minus the Start time
            return SDL_GetTicks() - m_dwStartTicks;
        }
    }

    //If the timer isn't running
    return 0;
}

void CTimer::fpsRegulate(void)
{
    //Pause for a length of time such that frame rate is maintained
    auto msTicks = GetTicks();
    if (msTicks < m_dwMsPerFrame)
    {
        SDL_Delay(static_cast<uint32_t>(m_dwMsPerFrame) - msTicks);
    }
}

uint32_t CTimer::GetTimeSinceInit(void) const noexcept
{
    return SDL_GetTicks();
}

uint32_t CTimer::GetTimeSinceLastFrame(void) noexcept
{
    if (m_bStarted && !m_bPaused)
    {
        auto thisTime = GetTimeSinceInit();
        auto deltaTime = thisTime - m_dwTimeOfLastCall;
        m_dwTimeOfLastCall = thisTime;

        return deltaTime;
    }
    else
    {
        return 0;
    }
}