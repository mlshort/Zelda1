/**
 *  @file       Window.cpp
 *  @brief      CWindow class implementation
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

#include "Renderer.h"
#include "Window.h"


CWindow::~CWindow()
{
#ifdef _DEBUG
    util::DebugTrace(_T("%S \n"), __FUNCTION__);
#endif
    Destroy();
}

void CWindow::Destroy(void)
{
    if (get_Handle())
    {
        SDL_DestroyWindow(Detach());
    };
};


bool CWindow::Initialize(bool bFullScreen) noexcept
{
    m_bFullScreen = bFullScreen;
    return true;
}

bool CWindow::Create(const char* szName, int iX, int iY, int iWidth, int iHeight)
{
    Attach (SDL_CreateWindow(szName, iX, iY,
                             iWidth, iHeight,
                             m_bFullScreen ? SDL_WINDOW_FULLSCREEN | SDL_WINDOW_RESIZABLE : 
                                             SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE));

    return (get_Handle() != nullptr);
}

SDL_Renderer*  CWindow::CreateRenderer(int iIndex, unsigned int nFlags)
{
    return get_Handle() ? SDL_CreateRenderer(get_Handle(), iIndex, nFlags) : nullptr;
}

CRenderer*  CWindow::CreateRendererEx(int iIndex, unsigned int nFlags)
{
    auto pSDLRenderer = CreateRenderer(iIndex, nFlags);
    if (pSDLRenderer)
        return new CRenderer(pSDLRenderer);
    else
        return nullptr;
};

SDL_Renderer*  CWindow::GetRenderer(void)
{
    return get_Handle() ? SDL_GetRenderer(get_Handle()) : nullptr;
};

SDL_Surface*   CWindow::GetSurface(void)
{
    return get_Handle() ? SDL_GetWindowSurface(get_Handle()) : nullptr;
};

bool CWindow::SetPosition(int iX, int iY)
{
    if (get_Handle())
    {
        SDL_SetWindowPosition(get_Handle(), iX, iY);
        return true;
    }
    else
    {
        return false;
    }
};