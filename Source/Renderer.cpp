/**
 *  @file       Renderer.cpp
 *  @brief      CRenderer class implementation
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

CRenderer::~CRenderer() noexcept
{
#ifdef _DEBUG
    util::DebugTrace(_T("%S \n"), __FUNCTION__);
#endif
    Destroy();
}

// @sa https://wiki.libsdl.org/SDL_DestroyRenderer
void CRenderer::Destroy(void) noexcept
{
    if (m_hSDL)
    {
        SDL_DestroyRenderer(Detach());
    };
};

bool CRenderer::Clear(void) noexcept
{
    if (get_Handle())
        return (SDL_RenderClear(get_Handle()) == 0);
    else
        return false;
};

bool CRenderer::Present(void) noexcept
{
    bool bReturn = false;
    if (get_Handle())
    {
        SDL_RenderPresent(get_Handle());
        bReturn = true;
    }
    return bReturn;
};

bool CRenderer::SetViewPort(const SDL_Rect& rect) noexcept
{
    return (SDL_RenderSetViewport(get_Handle(), &rect) == 0);
};

bool CRenderer::Copy(SDL_Texture* pSDLTexture, const SDL_Rect* pSrcRect, const SDL_Rect* pDestRect) noexcept
{
    return (SDL_RenderCopy(get_Handle(), pSDLTexture, pSrcRect, pDestRect) == 0);
};

bool CRenderer::CopyEx(SDL_Texture* pSDLTexture, const SDL_Rect* pSrcRect, const SDL_Rect* pDestRect,
                       DEGREES degAngle, const SDL_Point* pCenter, int iFlip) noexcept
{
    return (SDL_RenderCopyEx(get_Handle(), pSDLTexture, pSrcRect, pDestRect, degAngle,
                             pCenter, static_cast<SDL_RendererFlip>(iFlip) ) == 0);
};


bool CRenderer::GetOutputSize(int& iWidth, int& iHeight) noexcept
{
    if (get_Handle())
        return (SDL_GetRendererOutputSize(get_Handle(), &iWidth, &iHeight) == 0);
    else
        return false;
}

bool CRenderer::GetInfo(SDL_RendererInfo& info) noexcept
{
    if (get_Handle())
        return (SDL_GetRendererInfo(get_Handle(), &info) == 0);
    else
        return false;
};

SDL_Texture* CRenderer::CreateTextureFromSurface(SDL_Surface* pSDLSurface) noexcept
{
    if (get_Handle())
        return SDL_CreateTextureFromSurface(get_Handle(), pSDLSurface);
    else
        return nullptr;
};

bool CRenderer::SetDrawColor(uint8_t nRed, uint8_t nGreen, uint8_t nBlue, uint8_t nAlpha) noexcept
{
    if (get_Handle())
        return (SDL_SetRenderDrawColor(get_Handle(), nRed, nGreen, nBlue, nAlpha) == 0);
    else
        return false;
};

bool CRenderer::IsUsingIntegerScale(void) noexcept
{
    return get_Handle() && SDL_RenderGetIntegerScale(get_Handle());
}