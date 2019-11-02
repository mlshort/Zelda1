/**
 *  @file       Texture.cpp
 *  @brief      CTexture class implementation
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
#include "SDL_image.h"

#include <codecvt>
#include "Utility\DebugUtils.h"
#include "Renderer.h"
#include "View.h"

#include "Texture.h"

CTexture::~CTexture()
{
#ifdef _DEBUG
    util::DebugTrace(_T("%S \n"), __FUNCTION__);
#endif

    if (m_bDestroyOnDelete)
        Destroy();
}

void CTexture::Destroy(void)
{
    if (m_hSDL)
    {
#ifdef _DEBUG
       util::DebugTrace(_T("%S \n"), __FUNCTION__);
#endif // DEBUG

        SDL_DestroyTexture(Detach());
    }

    m_iWidth  = 0;
    m_iHeight = 0;
};

   /// Assignment Operator
    CTexture& CTexture::operator=(const CTexture& rhs) noexcept
    {
#ifdef _DEBUG
        util::DebugTrace(_T("%S \n"), __FUNCTION__);
#endif
        if (this != &rhs)
        {
            TEXTURE_HANDLE::operator=(rhs);
            m_iWidth           = rhs.m_iWidth;
            m_iHeight          = rhs.m_iHeight;
            m_bDestroyOnDelete = rhs.m_bDestroyOnDelete;
        }
        return *this;
    };

    /// Assignment Move Operator
    CTexture& CTexture::operator=(CTexture&& rhs) noexcept
    {
#ifdef _DEBUG
        util::DebugTrace(_T("%S move \n"), __FUNCTION__);
#endif
        if (this != &rhs)
        {
            TEXTURE_HANDLE::operator=( std::move(rhs) );
            m_iWidth           = rhs.m_iWidth;
            m_iHeight          = rhs.m_iHeight;
            m_bDestroyOnDelete = rhs.m_bDestroyOnDelete;

        }
        return *this;
    };


bool CTexture::SetColor(uint8_t nRed, uint8_t nGreen, uint8_t nBlue)
{
    return (SDL_SetTextureColorMod(get_Handle(), nRed, nGreen, nBlue) == 0);
}


bool CTexture::Load(CRenderer* pRenderer, const TCHAR* szImageFileName )
{
    //Destroy existing texture information
    Destroy();

    if (pRenderer)
    {
        if (szImageFileName && szImageFileName[0])
        {
#ifdef _UNICODE
    //Load the image

            std::wstring_convert<std::codecvt_utf8_utf16<TCHAR> > cvt;
            std::string str = cvt.to_bytes(szImageFileName);

            auto pSDLSurface = IMG_Load(str.c_str());
#else
            auto pSDLSurface = IMG_Load(szImageFileName);
#endif

    //If the image loaded
            if (pSDLSurface == nullptr)
            {
                util::DebugTrace(_T("Unable to load image %s ! SDL Error: %S \n"), szImageFileName, IMG_GetError());
            }
            else
            {
                //Color key image
                if (SDL_SetColorKey(pSDLSurface, SDL_TRUE, SDL_MapRGB(pSDLSurface->format, 255, 0, 255)) != 0)
                {
                    util::DebugTrace(_T("SDL_SetColorKey Failed! SDL Error: %S \n"), SDL_GetError());
                }

                //Create an optimized image
                Attach(pRenderer->CreateTextureFromSurface(pSDLSurface));

                if (m_hSDL == nullptr)
                {
                    util::DebugTrace(_T("Unable to create texture from image %s! SDL Error: %S \n"), szImageFileName, SDL_GetError());
                }
                else
                {
                    //Get the height and width from the texture
                    uint32_t nFormat;
                    int      iAccess;
                    Query(nFormat, iAccess, m_iWidth, m_iHeight);

                    //Free the loaded image; no longer needed
                    SDL_FreeSurface(pSDLSurface);
                }
            }
        }
    }

    return (m_hSDL != nullptr);
}



bool CTexture::Render(CRenderer* pRenderer, int iX, int iY, const SDL_Rect* pSrcRect)
{

    //Set rendering space and render to screen
    SDL_Rect destRect = { iX, iY, m_iWidth, m_iHeight};

    //Set clip rendering dimensions
    if ( pSrcRect != nullptr )
    {
        destRect.w = pSrcRect->w;
        destRect.h = pSrcRect->h;
    }

    //Render to screen
    return pRenderer->Copy(m_hSDL, pSrcRect, &destRect);

}

bool CTexture::Render(CRenderer* pRenderer, int iX, int iY, DEGREES fAngle, const SDL_Rect* pSrcRect)
{
    //Set rendering space and render to screen
    SDL_Rect destRect = { iX, iY, m_iWidth, m_iHeight};

    //Set clip rendering dimensions
    if ( pSrcRect != nullptr )
    {
        destRect.w = pSrcRect->w;
        destRect.h = pSrcRect->h;
    }

    //Render to screen
    return pRenderer->CopyEx(get_Handle(), pSrcRect, &destRect, fAngle, nullptr, SDL_FLIP_NONE);

}

bool CTexture::Render(CRenderer* pRenderer, const CView* pView, int iX, int iY, DEGREES fAngle, const SDL_Rect* pSrcRect)
{
    SDL_Rect destRect = { iX - pView->get_PosnX(),
                          iY - pView->get_PosnY(),
                          m_iWidth,
                          m_iHeight };


    //Render to screen
    return pRenderer->CopyEx(get_Handle(), // The source texture
                             pSrcRect,      // A pointer to the source rectangle
                             &destRect,     // A pointer to the destination rectangle, or nullptr for the entire rendering target
                             fAngle,        // An angle in degrees that indicates the rotation that will be applied to destRect
                             nullptr,       // A pointer to a point indicating the point around which destRect will be rotated
                                            //   (if nullptr, rotation will be done around destRect.w/2, destRect.h/2)
                             SDL_FLIP_NONE);
}

bool CTexture::Render(CRenderer* pRenderer, const CView* pView, int iX, int iY, DEGREES fAngle)
{
    // screen = world - camera
    SDL_Rect destRect = { iX - pView->get_PosnX(),
                          iY - pView->get_PosnY(),
                          m_iWidth,
                          m_iHeight };

    //Render to screen
    return pRenderer->CopyEx(get_Handle(), // The source texture
                             nullptr,       // nullptr for the entire texture.
                             &destRect,     // address of the destination rectangle
                             fAngle,        // An angle in degrees that indicates the rotation that will be applied to destRect
                             nullptr,       // a point indicating the point around which destRect will be rotated
                                            //   (if nullptr, rotation will be done around destRect.w/2, destRect.h/2)
                             SDL_FLIP_NONE);
}



bool CTexture::Query(uint32_t& nFormat, int& iAccess, int& iWidth, int& iHeight)
{
    return (SDL_QueryTexture(get_Handle(), &nFormat, &iAccess, &iWidth, &iHeight) == 0);
};

bool CTexture::SetColorMod(uint8_t nRed, uint8_t nGreen, uint8_t nBlue)
{
    return (SDL_SetTextureColorMod(get_Handle(), nRed, nGreen, nBlue) == 0);
};


bool CTexture::GetColorMod(uint8_t& nRed, uint8_t& nGreen, uint8_t& nBlue)
{
    return (SDL_GetTextureColorMod(get_Handle(), &nRed, &nGreen, &nBlue) == 0);
}

bool CTexture::SetAlphaMod(uint8_t alpha)
{
    return (SDL_SetTextureAlphaMod(get_Handle(), alpha) == 0);
};

bool CTexture::GetAlphaMod(uint8_t& alpha)
{
    return (SDL_GetTextureAlphaMod(get_Handle(), &alpha) == 0);
}

bool CTexture::Update(const SDL_Rect* pSDLRect, const void* pPixels, int iPitch)
{
    return (SDL_UpdateTexture(get_Handle(), pSDLRect, pPixels, iPitch) == 0);
};

bool CTexture::UpdateYUV(const SDL_Rect* pSDLRect,
                         const uint8_t* pYplane, int cbYpitch,
                         const uint8_t* pUplane, int cbUpitch,
                         const uint8_t* pVplane, int cbVpitch)
{
    return (SDL_UpdateYUVTexture(get_Handle(), pSDLRect, pYplane, cbYpitch,
                                 pUplane, cbUpitch, pVplane, cbVpitch) == 0);
};

bool CTexture::Lock(const SDL_Rect* pSDLRect, void** ppPixels, int& nPitch)
{
    return (SDL_LockTexture(get_Handle(), pSDLRect, ppPixels, &nPitch) == 0);
};

bool CTexture::Unlock(void)
{
    bool bReturn = false;

    if (get_Handle())
    {
        SDL_UnlockTexture(get_Handle());
        bReturn = true;
    }
    return bReturn;
}