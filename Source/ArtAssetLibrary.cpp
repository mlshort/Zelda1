/**
 *  @file       ArtAssetLibrary.cpp
 *  @brief      CArtAssetLibrary class implementation
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

#include "Texture.h"
#include "GraphicsDevice.h"
#include "Utility\DebugUtils.h"

#include "ArtAssetLibrary.h"


CArtAssetLibrary::~CArtAssetLibrary(void)
{
#ifdef _DEBUG
    util::DebugTrace(_T("%S \n"), __FUNCTION__);
#endif
}


bool CArtAssetLibrary::Initialize(CGraphicsDevice* pGraphicsDev) noexcept
{
    m_pGraphicsDev = pGraphicsDev;
    return (m_pGraphicsDev != nullptr);
}


bool CArtAssetLibrary::LoadAsset(const tstring& strAssetName, const tstring& strFileName)
{
    bool bRetVal = false;

    if (m_pGraphicsDev)
    {
        auto pRenderer = m_pGraphicsDev->GetRenderer();

        if (pRenderer)
        {
            CTexture NewTexture;

            if (NewTexture.Load(pRenderer, strFileName.c_str()))
            {
                bRetVal = AddAsset(strAssetName, NewTexture);

                // make sure to detach underlying SDL_Texture
                // so that it does not get destroyed when
                // temp object goes out of scope.
                if (bRetVal)
                    NewTexture.Detach();
            }
        }
    }

    return bRetVal;
}
