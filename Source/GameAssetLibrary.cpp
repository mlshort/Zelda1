/**
 *  @file       GameAssetLibrary.cpp
 *  @brief      CGameAssetLibrary class implementation
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

#include "RedOctorok.h"
#include "BlueOctorok.h"
#include "RedLeever.h"
#include "BlueLeever.h"
#include "Utility\DebugUtils.h"

#include "GameAssetLibrary.h"

ACTOR_T StringToType(const tstring& str)
{
    if (str == _T("Red Leever"))
        return ACT_RED_LEEVER;
    if (str == _T("Blue Leever"))
        return ACT_BLUE_LEEVER;
    if (str == _T("Red Octorok"))
        return ACT_RED_OCTOROK;
    if (str == _T("Blue Octorok"))
        return ACT_BLUE_OCTOROK;

    return ACT_INVALID;
}


CGameAssetLibrary::~CGameAssetLibrary() noexcept
{
#ifdef _DEBUG
    util::DebugTrace(_T("%S \n"), __FUNCTION__);
#endif
}

bool CGameAssetLibrary::Initialize(void) noexcept
{
    return true;
}

std::unique_ptr<CActor> CGameAssetLibrary::CreateAsset(const tstring& strAssetType)
{
    auto type = StringToType(strAssetType);
    switch (type)
    {
    case ACT_RED_LEEVER:
        return std::move(m_RedLeeverFactory.Create());
        break;
    case ACT_BLUE_LEEVER:
        return std::move(m_BlueLeeverFactory.Create());
        break;
    case ACT_RED_OCTOROK:
        return std::move(m_RedOctorokFactory.Create());
        break;
    case ACT_BLUE_OCTOROK:
        return std::move(m_BlueOctorokFactory.Create());
        break;
    default:
        return std::unique_ptr<CActor>(nullptr);
        break;
    }
}


