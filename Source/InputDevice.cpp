/**
 *  @file       InputDevice.cpp
 *  @brief      CInputDevice class implementation
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

#include <memory>

#include "SDL.h"

#include "Utility\DebugUtils.h"

#include "InputDevice.h"

// Local helper functions

GAME_EVENT Translate                (const SDL_Event& sdlEvt) noexcept;
void       PrintKeyDownEvent        (const SDL_Event& sdlEvt) noexcept;
void       PrintMouseButtonDownEvent(const SDL_Event& sdlEvt) noexcept;
void       PrintWindowEvent         (const SDL_Event& sdlEvt) noexcept;

CInputDevice::~CInputDevice(void)
{
#ifdef _DEBUG
    util::DebugTrace(_T("%S \n"), __FUNCTION__);
#endif
}

bool CInputDevice::Initialize(void) noexcept
{
    return true;
}

// Updates the event based on the current SDL_EVENT
// @sa https://wiki.libsdl.org/SDL_PollEvent
bool CInputDevice::PollEvent(GAME_EVENT& evt, uint32_t& dwData1, uint32_t& dwData2)
{
    SDL_Event  sdlEvent;
    bool bResult = (SDL_PollEvent(&sdlEvent) == 1);
    if (bResult)
    {
        //updates the proper key state based on the event that was retrieved
        switch (sdlEvent.type)
        {
        case SDL_KEYDOWN:
            //translates the SDL event to a game event.
            evt = Translate(sdlEvent);
            m_KeyStates[evt] = true;
            break;
        case SDL_KEYUP:
            //translates the SDL event to a game event.
            evt = Translate(sdlEvent);
            m_KeyStates[evt] = false;
            // lets clear the event since we took care of clearing the key
            evt = GAME_NA;
            break;
        case SDL_QUIT:
            evt = GAME_QUIT;
            m_KeyStates[evt] = true;
            break;
        case SDL_WINDOWEVENT:
            {
                switch (sdlEvent.window.event)
                {
                case SDL_WINDOWEVENT_RESIZED:
                case SDL_WINDOWEVENT_SIZE_CHANGED:
                    evt     = GAME_VIEW_SIZE;
                    dwData1 = sdlEvent.window.data1;
                    dwData2 = sdlEvent.window.data2;
                    PrintWindowEvent(sdlEvent);
                    break;
                }
            }
            break;
        case SDL_MOUSEBUTTONDOWN:
#ifdef _DEBUG
            PrintMouseButtonDownEvent(sdlEvent);
#endif
            break;
        default:
            evt = GAME_NA;
            break;
        }
    }
    return bResult;
}

bool CInputDevice::GetKeyState(GAME_EVENT evt) const
{
    return m_KeyStates[evt];
}


//**************************************
// Prints out the SDL_KEYDOWN event
void PrintKeyDownEvent(const SDL_Event& sdlEvt) noexcept
{
    switch(sdlEvt.type)
    {
    case SDL_KEYDOWN:
        util::DebugTrace(_T("SDL event Type: KEYDOWN \n"));
        util::DebugTrace(_T("Key Pressed: %d \n"), sdlEvt.key.keysym.sym);
    }
}

void PrintMouseButtonDownEvent(const SDL_Event& sdlEvt) noexcept
{
    switch(sdlEvt.type)
    {
    case SDL_MOUSEBUTTONDOWN:
        util::DebugTrace(_T("SDL event Type: MOUSEBUTTONDOWN \n"));
        util::DebugTrace(_T("Mouse Click x:[%d], y:[%d] \n"), sdlEvt.button.x, sdlEvt.button.y);
    }
}

// following is modified from the SDL Wiki, which I found helpful
// @sa https://wiki.libsdl.org/SDL_WindowEvent
void PrintWindowEvent(const SDL_Event& sdlEvt) noexcept
{
    if (sdlEvt.type == SDL_WINDOWEVENT)
    {
        switch (sdlEvt.window.event)
        {
        case SDL_WINDOWEVENT_SHOWN:
            util::DebugTrace(_T("Window %d shown \n"), sdlEvt.window.windowID);
            break;
        case SDL_WINDOWEVENT_HIDDEN:
            util::DebugTrace(_T("Window %d hidden \n"), sdlEvt.window.windowID);
            break;
        case SDL_WINDOWEVENT_EXPOSED:
            util::DebugTrace(_T("Window %d exposed \n"), sdlEvt.window.windowID);
            break;
        case SDL_WINDOWEVENT_MOVED:
            util::DebugTrace(_T("Window %d moved to %d,%d \n"),
                    sdlEvt.window.windowID, sdlEvt.window.data1,
                    sdlEvt.window.data2);
            break;
        case SDL_WINDOWEVENT_RESIZED:
            util::DebugTrace(_T("Window %d resized to %dx%d \n"),
                    sdlEvt.window.windowID, sdlEvt.window.data1,
                    sdlEvt.window.data2);
            break;
        case SDL_WINDOWEVENT_SIZE_CHANGED:
            util::DebugTrace(_T("Window %d size changed to %dx%d \n"),
                    sdlEvt.window.windowID, sdlEvt.window.data1,
                    sdlEvt.window.data2);
            break;
        case SDL_WINDOWEVENT_MINIMIZED:
            util::DebugTrace(_T("Window %d minimized \n"), sdlEvt.window.windowID);
            break;
        case SDL_WINDOWEVENT_MAXIMIZED:
            util::DebugTrace(_T("Window %d maximized \n"), sdlEvt.window.windowID);
            break;
        case SDL_WINDOWEVENT_RESTORED:
            util::DebugTrace(_T("Window %d restored \n"), sdlEvt.window.windowID);
            break;
        case SDL_WINDOWEVENT_ENTER:
            util::DebugTrace(_T("Mouse entered window %d \n"),
                    sdlEvt.window.windowID);
            break;
        case SDL_WINDOWEVENT_LEAVE:
            util::DebugTrace(_T("Mouse left window %d \n"), sdlEvt.window.windowID);
            break;
        case SDL_WINDOWEVENT_FOCUS_GAINED:
            util::DebugTrace(_T("Window %d gained keyboard focus \n"),
                    sdlEvt.window.windowID);
            break;
        case SDL_WINDOWEVENT_FOCUS_LOST:
            util::DebugTrace(_T("Window %d lost keyboard focus \n"),
                    sdlEvt.window.windowID);
            break;
        case SDL_WINDOWEVENT_CLOSE:
            util::DebugTrace(_T("Window %d closed \n"), sdlEvt.window.windowID);
            break;
#if SDL_VERSION_ATLEAST(2, 0, 5)
        case SDL_WINDOWEVENT_TAKE_FOCUS:
            util::DebugTrace(_T("Window %d is offered a focus \n"), sdlEvt.window.windowID);
            break;
        case SDL_WINDOWEVENT_HIT_TEST:
            util::DebugTrace(_T("Window %d has a special hit test \n"), sdlEvt.window.windowID);
            break;
#endif
        default:
            util::DebugTrace(_T("Window %d got unknown event %d \n"),
                    sdlEvt.window.windowID, sdlEvt.window.event);
            break;
        }
    }
}

GAME_EVENT Translate(const SDL_Event& sdlEvt) noexcept
{
    //This switch is here in case we want to add other events, such as mouse events.
    switch (sdlEvt.key.keysym.sym)
    {
    case SDLK_LEFT:
        return GAME_LEFT;
        break;
    case SDLK_RIGHT:
        return GAME_RIGHT;
        break;
    case SDLK_UP:
        return GAME_UP;
        break;
    case SDLK_DOWN:
        return GAME_DOWN;
        break;
    case SDLK_SPACE:
        return GAME_SPACE;
        break;
    case SDLK_RSHIFT:
    case SDLK_LSHIFT:
        return GAME_SHIFT;
        break;
    case SDLK_b:
        return GAME_B;
        break;
    case SDLK_TAB:
        return GAME_TAB;
        break;
    case SDLK_ESCAPE:
        return GAME_QUIT;
        break;
    }

    return GAME_NA;
}
