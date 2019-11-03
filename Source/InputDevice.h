/**
 *  @file       InputDevice.h
 *  @brief      CInputDevice class definition
 *  @author     Mark L. Short
 *  @date       March 12, 2017
 *
 *  <b>Course:</b>     CPSC 5377 Advanced Game Programming
 *
 *  <b>Instructor:</b> Sean Orme
 *
 *  <b>Assignment:</b> Zelda1 Project
 *
 *   The InputDevice class is a wrapper for the SDL_Event. (we poll the SDL_Event
 *   and then, if an event exists, we translate it to a game event and return it).
 *   The purpose here is to provide a layer between the Game and the SDL2 Libraries.
 *
 *   The InputDevice has the following properties:
 *   *   unique_ptr<SDL_Event> event;
 *
 *   And the following capabilities:
 *   *   bool Initialize();  -     initializes the InputDevice by creating the “event”
 *                                 unique pointer
 *   *   GAME_EVENT GetEvent(); -  polls SDL for the latest event and calls “Translate”
 *                                 to convert it to a game event
 *   *   GAME_EVENT Translate(); - this private method translates SDL_Event information
 *                                 into GAME_EVENT type information (see Definitions.h)
 *
 * <b>Implementation Details:</b>
 *
 *   1. unique_ptr<SDL_Event> event is not actually needed.
 *   2. GetEvent modified to "bool PollEvent(GAME_EVENT& evt)"
 *   3. Translate removed as a private method.  It is not dependent on any class member
 *      and is implemented as a local "helper" function.
 */
#pragma once

#ifndef __INPUT_DEVICE_H__
#define __INPUT_DEVICE_H__

#ifndef __COMMON_H__
    #include "Common.h"
#endif

#ifndef _VECTOR_
    #include <vector>
#endif

 ///////////////////////////////////////////////////////////////////////////////
 //  Forward Declarations
union SDL_Event;

class CInputDevice
{
    std::vector<bool>          m_KeyStates;

public:
    CInputDevice(void) noexcept
        : m_KeyStates( GAME_NUM_EVENTS, false )
    { };

    /// Default Destructor
    ~CInputDevice(void);

    bool Initialize     (void) noexcept;
/**
    @brief polls SDL for the latest game event

    @param [out] evt        current game event, translated from underlying SDL event
    @param [out] dwData1    event specific data, may not be valid for all events
    @param [out] dwData2    event specific data, may not be valid for all events

    @retval true            if an event was pending, translated and removed from event queue
    @retval false           if no events were available
 */
    bool PollEvent    (GAME_EVENT& evt, uint32_t& dwData1, uint32_t& dwData2);

    bool GetKeyState  (GAME_EVENT evt) const;

///////////////////////////////////////////////////////////////////////////////
// disabling the copy constructor and assignment operator
    CInputDevice(const CInputDevice&) = delete;
    CInputDevice& operator=(const CInputDevice&) = delete;

};


#endif