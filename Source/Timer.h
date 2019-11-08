/**
 *  @file       Timer.h
 *  @brief      CTimer class definition
 *  @author     Mark L. Short
 *  @date       March 12, 2017
 *
 *  <b>Course:</b>     CPSC 5377 Advanced Game Programming
 *
 *  <b>Instructor:</b> Sean Orme
 *
 *  <b>Assignment:</b> Zelda1 Project
 *
 */
#pragma once

#if !defined(__TIMER_H__)
#define __TIMER_H__

#ifndef __COMMON_H__
    #include "Common.h"
#endif

class CTimer
{
    /// The clock time when the timer started
    uint32_t m_dwStartTicks;
    /// The ticks stored when the timer was paused
    uint32_t m_dwPausedTicks;
    /// Milliseconds per Frame
    uint32_t m_dwMsPerFrame;
    /// his stores the time of that last call to GetTimeSinceLastFrame()
    uint32_t m_dwTimeOfLastCall;

    bool     m_bPaused;
    bool     m_bStarted;

public:
    /// Default Constructor
    constexpr CTimer::CTimer(void) noexcept
        : m_dwPausedTicks( ),
          m_dwStartTicks( ),
          m_dwMsPerFrame( ),
          m_dwTimeOfLastCall(),
          m_bPaused( false ),
          m_bStarted( false )
    { };
    /// Default Destructor
    ~CTimer(void) noexcept;


    bool Initialize(void) noexcept;

    // Core Timer methods
    void Start (void) noexcept;
    void Stop  (void) noexcept;
    void Pause (void) noexcept;
    void Resume(void) noexcept;

    /**
     * @brief Returns milliseconds since timer entered current state
     *
     * @retval uint32_t   milliseconds since timer entered Start or Paused state
     * @retval 0          if timer is not running
     */
    uint32_t GetTicks(void) const noexcept;
    /**
        @brief Returns milliseconds since this object was initialized
    */
    uint32_t GetTimeSinceInit(void) const noexcept;
    /**
        @brief Returns milliseconds since it was last called
    */
    uint32_t GetTimeSinceLastFrame(void) noexcept;

    //Checks the status of the timer
    constexpr inline bool IsStarted(void) const noexcept
    { return m_bStarted; };

    constexpr inline bool IsPaused(void) const noexcept
    { return (m_bStarted && m_bPaused); };

    // Wait a specified number of milliseconds before returning
    void fpsRegulate(void) noexcept;


/////////////////////////////////////////////////////////////////////////
// disabling the copy constructor and assignment operator
    CTimer(const CTimer&) = delete;
    CTimer& operator=(const CTimer&) = delete;
};

#endif