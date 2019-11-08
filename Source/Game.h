/**
 *  @file       Game.h
 *  @brief      CGame class definition
 *  @mainpage
 *  @author     Mark L. Short
 *  @date       February 12, 2017
 *
 * <b>Course:</b>      CPSC 5377 Advanced Game Programming
 *
 * <b>Instructor :</b> Sean Orme
 *
 * <b>Assignment :</b> Zelda1 Project
 *
 *   To achieve the desired functionality, the Game class should have the
 *   following -
 *
 *   Properties:
 *       *   unique_ptr<GameAssetLibrary> gLibrary;
 *       *   unique_ptr<ArtAssetLibrary> aLibrary;
 *       *   unique_ptr<GraphicsDevice> gDevice;
 *       *   unique_ptr<InputDevice> iDevice;
 *       *   unique_ptr<Timer> timer;
 *       *   GAME_FLT gameTime;
 *       *   unique_ptr<View> view;
 *       *   vector<unique_ptr<Object>> objects;
 *
 *   Capabilities:
 *       *   default constructor and destructor;
 *       *   bool Initialize();
 *               - initializes or constructs all the members of the class
 *       *   void Reset();
 *               - destroys the View object and all Objects stored in objects,
 *                 and resets its size to zero;
 *       *   bool LoadLevel(string, string);
 *               - constructs the View object, loads objects into the ArtAssetLibray
 *                 from an XML file, and loads from XML file (by both parsing the XML
 *                 and appropriate calls to the Art and Game Assets Libraries) and
 *                 constructs all Objects in the objects container;
 *       *   bool Run();
 *               - conducts a single frame of the game (i.e., Updating, Drawing,
 *                 and frame timing)
 *       *   bool Update();
 *               - calls the Update method of all Objects in objects
 *       *   void Draw();
 *               - calls the Draw method of all Objects in objects
 *
 * <b>Implementation Details:</b>
 *
 *   1. CActor is used in lieu of Object as the generic base class
 *   2. LoadLevel is implemented as 2 separate methods:
 *              - LoadLevelFile
 *              - LoadObjectFile
 *   3. Render is used in lieu of Draw
 *   4. Various type and name changes in accordance with adopted conventions...
*/
#pragma once

#if !defined(__GAME_H__)
#define __GAME_H__

#ifndef __COMMON_H__
    #include "Common.h"
#endif

#ifndef _MEMORY_
    #include <memory>
#endif
#ifndef _VECTOR_
    #include <vector>
#endif
#ifndef __ACTOR_H__
    #include "Actor.h"
#endif
#ifndef __TIMER_H__
    #include "Timer.h"
#endif
#ifndef __INPUT_DEVICE_H__
    #include "InputDevice.h"
#endif
#ifndef __VIEW_H__
    #include "View.h"
#endif
#ifndef __GAME_ASSET_LIBRARY_H__
    #include "GameAssetLibrary.h"
#endif
#ifndef __ART_ASSET_LIBRARY_H__
    #include "ArtAssetLibrary.h"
#endif
#ifndef __GRAPHICS_DEVICE_H__
    #include "GraphicsDevice.h"
#endif


class CGame
{
    uint32_t                                     m_dwGameTime;  ///< Game Time in milliseconds
    std::unique_ptr<CGameAssetLibrary>           m_pGameAssetLibrary;
    std::unique_ptr<CArtAssetLibrary>            m_pArtAssetLibrary;
    std::unique_ptr<CGraphicsDevice>             m_pGraphicsDevice;
    std::unique_ptr<CInputDevice>                m_pInputDevice;
    std::unique_ptr<CTimer>                      m_pTimer;
    std::unique_ptr<CView>                       m_pView;
    size_t                                       m_nActorFocus;
    std::vector<std::unique_ptr<CActor>>         m_rgActors;

public:
    /// Default Constructor
    CGame(void) noexcept
    : m_dwGameTime       (),
      m_pGameAssetLibrary(),
      m_pArtAssetLibrary (),
      m_pGraphicsDevice  (),
      m_pInputDevice     (),
      m_pTimer           (),
      m_pView            (),
      m_nActorFocus      (INVALID_ACTOR),
      m_rgActors()
{ };

    /// Default Destructor
    ~CGame(void);

    bool Initialize    (void);

    bool ShutDown      (void) noexcept;

    bool Reset         (void) noexcept;

    bool Run           (void);

    bool LoadLevelFile (const TCHAR* szLevelConfigFileName);

    bool LoadObjectFile(const TCHAR* szObjectConfigFileName);

private:
    bool Update        (float fDeltatime) noexcept;
    void Render        (void) noexcept;

///////////////////////////////////////////////////////////////////////////////
//  Internal Event Handlers
    void OnTabKeyEvent    (GAME_EVENT evt);
    void OnScrollKeyEvent (GAME_EVENT evt) noexcept;
    void OnViewResizeEvent(int iX, int iY) noexcept;
    void OnSpaceKeyEvent  (void) noexcept;

///////////////////////////////////////////////////////////////////////////////
// disabling the copy constructor and assignment operator
    CGame( const CGame& ) = delete;
    CGame& operator=( const CGame& ) = delete;

};

#endif
