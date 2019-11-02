/**
 *  @file       BlueOctorok.cpp
 *  @brief      CBlueOctorok class implementation
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

#include "Texture.h"
#include "GraphicsDevice.h"
#include "Utility\DebugUtils.h"

#include "BlueOctorok.h"


CBlueOctorok::~CBlueOctorok()
{
#ifdef _DEBUG
    util::DebugTrace(_T("%S \n"), __FUNCTION__);
#endif
}

void CBlueOctorok::Update(float fDeltaTime)
{
    Move(fDeltaTime);
    Turn(fDeltaTime);
}

void CBlueOctorok::Render(const CView* pWhere) const
{
    if (m_pTexture && m_pGraphicsDevice)
    {
        bool bResult = m_pTexture->Render(m_pGraphicsDevice->GetRenderer(), 
                                          pWhere, 
                                          static_cast<int>(get_PosnX()), 
                                          static_cast<int>(get_PosnY()), 
                                           get_Direction());
        if (!bResult)
        {
            util::DebugTrace(_T("%S failed [%S] \n"), __FUNCTION__, SDL_GetError());
        }
    }
}

void CBlueOctorok::Move(float fDeltaTime) noexcept
{
    auto vel = get_Velocity();
    auto delta = vel * fDeltaTime;
    incr_Posn(delta);

    auto nDistance = get_Posn().CalcDistance(get_Start());

    if (nDistance > get_MaxRange())
    {
        set_Velocity(-get_Velocity());
#ifdef _DEBUG
         util::DebugTrace(_T("%S X:[%.2f] Y:[%.2f] velX:[%.2f] velY:[%.2f] dir:[%.2f] \n"), __FUNCTION__,
                      get_PosnX(), get_PosnY(), vel.X, vel.Y, get_Direction() );
#endif
    }
}


void CBlueOctorok::Turn(float fDeltaTime) noexcept
{
    incr_Direction(static_cast<DEGREES>(30.0 * fDeltaTime) );
}
