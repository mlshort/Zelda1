/**
 *  @file       Game.cpp
 *  @brief      CGame class implementation
 *  @author     Mark L. Short
 *  @date       February 12, 2017
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

#include <limits>

#include "XmlParser.h"
#include "XmlGameDataHandler.h"
#include "FileStream.h"

#include "Texture.h"
#include "Utility\DebugUtils.h"

#include "Game.h"

extern TCHAR g_szModulePath[MAX_PATH];

CGame::~CGame() noexcept
{
#ifdef _DEBUG
    util::DebugTrace(_T("%S GameTime:[%f] \n"), __FUNCTION__, m_dwGameTime / 1000.0);
#endif
}

bool CGame::ShutDown(void) noexcept
{
#ifdef _DEBUG
    util::DebugTrace(_T("%S \n"), __FUNCTION__);
#endif
    m_rgActors.clear();

    if (m_pArtAssetLibrary)
    {
        auto ptr = m_pArtAssetLibrary.release();
        delete ptr;
    }
    if (m_pGraphicsDevice)
    {
        m_pGraphicsDevice->ShutDown();
        auto ptr = m_pGraphicsDevice.release();
        delete ptr;
    }
    if (m_pGameAssetLibrary)
    {
        auto ptr = m_pGameAssetLibrary.release();
        delete ptr;
    }
    if (m_pInputDevice)
    {
        auto pInput = m_pInputDevice.release();
        delete pInput;
    }
    if (m_pView)
    {
        auto pView = m_pView.release();
        delete pView;
    }
    if (m_pTimer)
    {
        m_pTimer->Stop();
        auto ptr = m_pTimer.release();
        delete ptr;
    }

    SDL_Quit();

    return true;
}

bool CGame::Initialize(void)
{
    SDL_InitSubSystem(SDL_INIT_EVENTS);

    if (m_pGameAssetLibrary == nullptr)
        m_pGameAssetLibrary = std::make_unique<CGameAssetLibrary>();
    
    if (m_pArtAssetLibrary == nullptr)
        m_pArtAssetLibrary = std::make_unique<CArtAssetLibrary>();

    if (m_pGraphicsDevice == nullptr)
        m_pGraphicsDevice = std::make_unique<CGraphicsDevice>(g_SCREEN_WIDTH, g_SCREEN_HEIGHT);

    if (m_pInputDevice == nullptr)
        m_pInputDevice = std::make_unique<CInputDevice>();

    if (m_pTimer == nullptr)
        m_pTimer = std::make_unique<CTimer>();

    if (m_pView == nullptr)
        m_pView = std::make_unique<CView>();


    if (m_pTimer)
        m_pTimer->Initialize();
    else
        return false;

    if (m_pGraphicsDevice)
        m_pGraphicsDevice->Initialize(false);
    else
        return false;

    if (m_pArtAssetLibrary)
        m_pArtAssetLibrary->Initialize(m_pGraphicsDevice.get());
    else
        return false;

    if (m_pInputDevice)
        m_pInputDevice->Initialize();
    else
        return false;

    if (m_pView)
        m_pView->Initialize(0, 0, g_SCREEN_WIDTH, g_SCREEN_HEIGHT);
    else
        return false;


    // Start the game timer
    m_pTimer->Start();

    return true;
}

bool CGame::Reset(void) noexcept
{
    if (m_pTimer)
        m_pTimer->Stop();

    m_dwGameTime = 0;
    if (m_pView)
    {
        auto pView = m_pView.release();
        delete pView;
    }


    m_rgActors.clear();
    return true;
}

bool CGame::Run(void)
{
    bool bQuit   = false;
    auto tmDelta = m_pTimer->GetTimeSinceLastFrame();
    m_dwGameTime += tmDelta;

    if (m_pInputDevice)
    {
        GAME_EVENT evt;
        uint32_t   dwData1;
        uint32_t   dwData2;

        if (m_pInputDevice->PollEvent(evt, dwData1, dwData2))
        {
            switch (evt)
            {
            case GAME_UP:
            case GAME_DOWN:
            case GAME_LEFT:
            case GAME_RIGHT:
                OnScrollKeyEvent(evt);
                break;
            case GAME_TAB:
                OnTabKeyEvent(evt);
                break;
            case GAME_SPACE:
                OnSpaceKeyEvent();
                break;
            case GAME_VIEW_SIZE:
                OnViewResizeEvent(dwData1, dwData2);
                break;
            case GAME_QUIT:
                bQuit = true;
                break;

            }
        }
    }

    Update(static_cast<float>(tmDelta / 1000.0) );
    Render();

    return bQuit;
}

bool CGame::Update(float fDeltaTime) noexcept
{
    if (m_pView)
        m_pView->Update(fDeltaTime);

    for (auto& it : m_rgActors)
        it->Update(fDeltaTime);

    return true;
};


void CGame::Render(void) noexcept
{
    if (m_pGraphicsDevice)
    {
        m_pGraphicsDevice->Clear();

        for (auto& it : m_rgActors)
            it->Render(m_pView.get());

        m_pGraphicsDevice->Present();
    }
}

void CGame::OnTabKeyEvent(GAME_EVENT /*evt*/)
{
    auto nNumActors = m_rgActors.size();

    if (m_nActorFocus > (nNumActors - 2) )
        m_nActorFocus = 0;
    else
        m_nActorFocus++;

#ifdef _DEBUG
    util::DebugTrace(_T("%S Actor:[%d] Selected\n"), __FUNCTION__, m_nActorFocus);
#endif
    auto& pActor = m_rgActors[m_nActorFocus];
    auto  ptLoc  = pActor->get_Posn();

    if (m_pView)
        m_pView->OnTabKeyEvent(static_cast<CView::num_t>(ptLoc.X),
                               static_cast<CView::num_t>(ptLoc.Y) );

}

void CGame::OnScrollKeyEvent(GAME_EVENT evt) noexcept
{
    if (m_pView)
        m_pView->OnScrollEvent(evt);
}

void CGame::OnViewResizeEvent(int iX, int iY) noexcept
{
    if (m_pView)
        m_pView->OnSizeEvent(iX, iY);
}

void CGame::OnSpaceKeyEvent(void) noexcept
{
    if (m_pTimer)
    {
        bool bPaused = m_pTimer->IsPaused();
        if (bPaused)
            m_pTimer->Resume();
        else
            m_pTimer->Pause();

#ifdef _DEBUG
    util::DebugTrace(_T("%S Timer:[%s] \n"), __FUNCTION__, bPaused ? _T("Resumed") : _T("Paused") );
#endif
    }
};


bool CGame::LoadObjectFile(const TCHAR* szXmlFile)
{
    bool bResult = false;

    if (szXmlFile && szXmlFile[0])
    {
        HRESULT hr;
        IStream*  pFileStream;

        // open a read only input stream
        if (FAILED(hr = CFileStream::OpenFile(szXmlFile, &pFileStream, false)))
            return false;

        CXmlParser xmlParser;
        if (xmlParser.Create())
        {
            CXmlObjectDataHandler dataHandler;
            xmlParser.SetHandler(&dataHandler);

            bResult = xmlParser.Parse(pFileStream);

            if (bResult)
            {
                for (auto& it : dataHandler.GetData())
                {
                    if (!m_pArtAssetLibrary->LoadAsset(it.m_strName, tstring(g_szModulePath).append(it.m_strSpritePath)))
                        bResult = false;
                }
            }
        }
        pFileStream->Release();
    }
    return bResult;
};

bool CGame::LoadLevelFile(const TCHAR* szXmlFile)
{
    bool bResult = false;

    if (szXmlFile && szXmlFile[0])
    {
        HRESULT hr;
        IStream*  pFileStream;

        // open a read only input stream
        if (FAILED(hr = CFileStream::OpenFile(szXmlFile, &pFileStream, false)))
            return false;

        CXmlParser xmlParser;
        if (xmlParser.Create())
        {
            CXmlLevelDataHandler dataHandler;
            xmlParser.SetHandler(&dataHandler);

            bResult = xmlParser.Parse(pFileStream);

            if (bResult)
            {
                float nScreenDist = static_cast<float> (std::sqrt( (g_SCREEN_WIDTH * g_SCREEN_WIDTH) +
                                                                   (g_SCREEN_HEIGHT * g_SCREEN_HEIGHT) ) );
                float nRoamLower = nScreenDist / 4;
                float nRoamUpper = nRoamLower * 3;
                for (auto& it : dataHandler.GetData())
                {
                    auto pActor = m_pGameAssetLibrary->CreateAsset(it.m_strName);
                    if (pActor)
                    {
                        auto pTexture = m_pArtAssetLibrary->Search(it.m_strName);
                        if (pTexture)
                        {
                            // initialize actor, but translate angle to game direction
                            pActor->Initialize(it.m_fX, it.m_fY, it.m_fAngle);
                            pActor->SetTexture(pTexture);
                            pActor->SetDevices(m_pGraphicsDevice.get());

                            pActor->set_MaxRange(math::RangedRand(nRoamLower, nRoamUpper));
                            auto nVelMagnitude = math::RangedRand(5, 20);

                            // adding 90 degrees to convert to game engine directions

                            float X = math::CalcXComponent(pActor->get_Direction() - 90);
                            if (math::fEqual(X, 0.0f, 2))
                                X = 0.0f;

                            float Y = math::CalcYComponent(pActor->get_Direction() - 90);
                            if (math::fEqual(Y, 0.0f, 2))
                                Y = 0.0f;

                            CActor::vec_t vVelDirection(X, Y);

                            pActor->set_Velocity(vVelDirection * nVelMagnitude);

                            m_rgActors.push_back(std::move(pActor));
                        }
                        else
                        {
                            bResult = false;
                        }
                    }
                }
            }
        }
        pFileStream->Release();
    }
    return bResult;
}



