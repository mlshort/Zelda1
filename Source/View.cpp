/**
 *  @file       View.cpp
 *  @brief      CView class implementation
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
#include "InputDevice.h"

#include "View.h"

//**************************************
//Set initial values
bool CView::Initialize(num_t nX, num_t nY, num_t nWidth, num_t nHeight) noexcept
{
    m_iWidth  = nWidth;
    m_iHeight = nHeight;
    m_ptPosn.Init(nX, nY);
    m_ptCenter.Init(nX + (nWidth / 2), nY + (nHeight / 2) );
    return true;
}


bool CView::Update(float /*fDeltaTime*/) noexcept
{
    return true;
}

/*
  The view responds to GAME_EVENTs. Initially the current GAME_EVENT is
  requested from the InputDevice. The View then responds to keyboard events
  by shifting its position in accordance with the events (in the example
  program, the instructor shifts the view by 2 pixels per detected event, e.g.,
  GAME_LEFT event causes the view’s x-position to be decremented by 2 pixels
  without any change to the view’s y-position).
*/
void CView::OnScrollEvent(GAME_EVENT evt) noexcept
{
    switch (evt)
    {
    case GAME_DOWN:
        m_ptPosn.Y += 2;
        m_ptCenter.Y += 2;
        break;
    case GAME_LEFT:
        m_ptPosn.X -= 2;
        m_ptCenter.X -= 2;
        break;
    case GAME_UP:
        m_ptPosn.Y -= 2;
        m_ptCenter.Y -= 2;
        break;
    case GAME_RIGHT:
        m_ptPosn.X += 2;
        m_ptCenter.X += 2;
        break;
    }
#ifdef _DEBUG
    Print();
#endif
}

void CView::OnTabKeyEvent(num_t nFocusX, num_t nFocusY) noexcept
{
    point_t pt;
    pt.X = ( nFocusX + (16 / 2) ) - m_iWidth / 2;
    pt.Y = ( nFocusY + (16 / 2) ) - m_iHeight / 2;

    // this should be the upper-left point of the view
    set_Posn( pt );

    // this should be the center point of the view
    set_Center( point_t(pt.X + m_iWidth / 2, pt.Y + m_iHeight / 2) );

#ifdef _DEBUG
    Print();
#endif
}

void CView::OnSizeEvent(num_t iWidth, num_t iHeight) noexcept
{
    m_iWidth  = iWidth;
    m_iHeight = iHeight;
};


//**************************************
//print view data
void CView::Print(void) noexcept
{
    util::DebugTrace(_T("*****VIEW****** \n"));
    util::DebugTrace(_T("ViewPosn X:[%d] Y:[%d] \n"), get_PosnX(),   get_PosnY() );
    util::DebugTrace(_T("ViewCtr  X:[%d] Y:[%d] \n"), get_CenterX(), get_CenterY() );
}