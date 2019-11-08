/**
 *  @file       RedOctorok.cpp
 *  @brief      CRedOctorok class implementation
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

#include "RedOctorok.h"


CRedOctorok::~CRedOctorok(void) noexcept
{
#ifdef _DEBUG
    util::DebugTrace(_T("%S \n"), __FUNCTION__);
#endif
}

void CRedOctorok::Update(float fDeltaTime) noexcept
{
    Move(fDeltaTime);
    Turn(fDeltaTime);
}

void CRedOctorok::Render(const CView* pWhere) const
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

void CRedOctorok::Move(float /*fDeltaTime*/) noexcept
{
    set_Posn(math::CalcXComponent(get_Direction()) * get_MaxRange(),
             math::CalcYComponent(get_Direction()) * get_MaxRange());

}

void CRedOctorok::Turn(float fDeltaTime) noexcept
{
    incr_Direction(static_cast<DEGREES>(30.0 * fDeltaTime) );
}
