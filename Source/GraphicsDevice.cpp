/**
 *  @file       GraphicsDevice.cpp
 *  @brief      CGraphicsDevice class implementation
 *  @author     Mark L. Short
 *  @date       March 12, 2017
 *
 *  <b>Course:</b>     CPSC 5377 Advanced Game Programming
 *
 *  <b>Instructor:</b> Sean Orme
 *
 *  <b>Assignment:</b> Zelda1 Project
 *
 *  <b>Cite:</b>
 *             * Example code from Dr. Bush, Sean Orme
 *             * Simple DirectMedia Layer (SDL) Wiki, https://wiki.libsdl.org/
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
#include "SDL_image.h"

#include "Utility\DebugUtils.h"
#include "Renderer.h"
#include "Window.h"

#include "GraphicsDevice.h"


CGraphicsDevice::~CGraphicsDevice()
{
#ifdef _DEBUG
    util::DebugTrace(_T("%S \n"), __FUNCTION__);
#endif
    if (!ShutDown())
    {
        util::DebugTrace( _T("SDL could not shut down! SDL_Error: %S \n"), SDL_GetError() );
        exit(1);
    }
}

bool CGraphicsDevice::ShutDown(void) noexcept
{
    //Free the window
    if (m_pMainWindow)
    {
        delete m_pMainWindow;
        m_pMainWindow = nullptr;
    }

    //Free renderer
    if (m_pRenderer)
    {
        delete m_pRenderer;
        m_pRenderer = nullptr;
    }

    //Quit SDL Subsystems
    SDL_QuitSubSystem(SDL_INIT_VIDEO);
    IMG_Quit();

    return true;
}

bool CGraphicsDevice::Initialize(bool bFullScreen)
{
    //Initialize all SDL subsystems
    if (SDL_InitSubSystem(SDL_INIT_VIDEO) != 0)
    {
        util::DebugTrace( _T("SDL could not initialize VIDEO! SDL_Error: %S \n"), SDL_GetError() );
        return false;
    }

    //Initialize SDL_image subsystems
    if (IMG_Init(IMG_INIT_PNG) == 0)  // returns 0 on failure... for some reason
    {
        util::DebugTrace( _T("SDL_image could not initialize! SDL_Error: %S \n"), IMG_GetError() );
        return false;
    }

    m_pMainWindow = new CWindow(bFullScreen);

    bool bResult = m_pMainWindow->Create("Zelda1",
                        SDL_WINDOWPOS_UNDEFINED,
                        SDL_WINDOWPOS_UNDEFINED,
                        m_nScreenWidth, m_nScreenHeight);

    if (!bResult)
    {
        util::DebugTrace( _T("Window could not be created! SDL_Error: %S \n"), SDL_GetError() );
        return false;
    }

    //Construct the renderer object
    m_pRenderer = m_pMainWindow->CreateRendererEx(-1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (m_pRenderer == nullptr)
    {
        util::DebugTrace( _T("Renderer could not be created! SDL_Error: %S \n"), SDL_GetError() );
        return false;
    }

    //Set the background color (default)
    m_pRenderer->SetDrawColor(0, 0, 0, 255);

    return true;

}

bool CGraphicsDevice::Clear(void) noexcept
{
    return (m_pRenderer && m_pRenderer->Clear());
}

bool CGraphicsDevice::Present(void) noexcept
{
    return (m_pRenderer && m_pRenderer->Present());
}

