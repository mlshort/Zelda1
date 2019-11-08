/**
 *  @file       Actor.cpp
 *  @brief      CActor class implementation
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

#include "Utility\DebugUtils.h"

#include "Actor.h"


constexpr CActor::CActor(const CActor& oth) noexcept
    : IRenderable      (oth),
      m_Type           (oth.m_Type),
      m_pGraphicsDevice(oth.m_pGraphicsDevice),
      m_pTexture       (oth.m_pTexture),
      m_ptPosn         (oth.m_ptPosn),
      m_ptStart        (oth.m_ptStart),
      m_degDirection   (oth.m_degDirection),
      m_nMaxRange      (oth.m_nMaxRange)
{
};

CActor::CActor(CActor&& oth) noexcept
    : IRenderable      (std::move(oth)),
      m_Type           (oth.m_Type),
      m_pGraphicsDevice(std::move(oth.m_pGraphicsDevice)),
      m_pTexture       (), // smart ptr
      m_ptPosn         (oth.m_ptPosn),
      m_ptStart        (oth.m_ptStart),
      m_degDirection   (oth.m_degDirection),
      m_nMaxRange      (oth.m_nMaxRange)
{
    oth.m_pGraphicsDevice = nullptr;  // take ownership
    m_pTexture.swap(oth.m_pTexture);  // take ownership
}

CActor::~CActor(void) noexcept
{
#ifdef _DEBUG
    util::DebugTrace(_T("%S \n"), __FUNCTION__);
#endif
}

CActor& CActor::operator=(const CActor& rhs) noexcept
{
    if (this != &rhs)
    {
        m_Type            = rhs.m_Type;
        m_pGraphicsDevice = rhs.m_pGraphicsDevice;
        m_pTexture        = rhs.m_pTexture;
        m_ptPosn          = rhs.m_ptPosn;
        m_ptStart         = rhs.m_ptStart;
        m_degDirection    = rhs.m_degDirection;
        m_nMaxRange       = rhs.m_nMaxRange;
    }
    return *this;
};

CActor& CActor::operator=(CActor&& rhs) noexcept
{
    if (this != &rhs)
    {
        m_Type            = rhs.m_Type;
        m_pGraphicsDevice = rhs.m_pGraphicsDevice;
        m_pTexture        = nullptr;
        m_ptPosn          = rhs.m_ptPosn;
        m_ptStart         = rhs.m_ptStart;
        m_degDirection    = rhs.m_degDirection;
        m_nMaxRange       = rhs.m_nMaxRange;

        rhs.m_pGraphicsDevice = nullptr;  // take ownership
        m_pTexture.swap(rhs.m_pTexture);  // take ownership
    }
    return *this;
};

void  CActor::Initialize(num_t nX, num_t nY, DEGREES fAngle) noexcept
{
    m_ptStart.Init(nX, nY);
    m_ptPosn.Init(nX, nY);
    m_vVelocity.Init(0,0);
    m_degDirection = fAngle;
}

void  CActor::SetTexture(std::shared_ptr<CTexture> pTexture) noexcept
{
    m_pTexture = pTexture;
};

void  CActor::SetDevices(CGraphicsDevice* pGraphicsDev) noexcept
{
    m_pGraphicsDevice = pGraphicsDev;
};