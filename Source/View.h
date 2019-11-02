/**
 *  @file       View.h
 *  @brief      CView class definition
 *  @author     Mark L. Short
 *  @date       March 12, 2017
 *
 *  <b>Course:</b>     CPSC 5377 Advanced Game Programming
 *
 *  <b>Instructor:</b> Sean Orme
 *
 *  <b>Assignment:</b> Zelda1 Project
 *
 *   You must implement an omniscient view of the game state in
 *   the form of a class View. In addition to default construction,
 *   destruction, and Initialization capability, the View class has
 *   the following -
 *
 *   Properties:
 *       *   InputDevice* iDevice;
 *       *   GAME_VEC position;
 *       *   GAME_VEC center;
 *
 *   Capabilities:
 *       * bool Initialize(InputDevice*, GAME_FLT, GAME_FLT);
 *              -  the GAME_FLT values correspond to the initial x- and y-coordinates
 *                  of the View object.
 *       * bool Update(GAME_FLT);
 *              - The view responds to GAME_EVENTs. Initially the current GAME_EVENT is
 *                requested from the InputDevice. The View then responds to keyboard events
 *                by shifting its position in accordance with the events (in the example
 *                program, the instructor shifts the view by 2 pixels per detected event,
 *                e.g., GAME_LEFT event causes the view’s x-position to be decremented by
 *                2 pixels without any change to the view’s y-position).
 *
 * <b>Implementation Details:</b>
 *
 *   1. This class was designed more as a "camera" than a "view" class
 */
#pragma once

#if !defined(__VIEW_H__)
#define __VIEW_H__

#ifndef __COMMON_H__
    #include "Common.h"
#endif

#ifndef __VECTOR2_H__
    #include "Utility\Vector2.h"
#endif


class CView
{
public:
    typedef typename CVector2i     point_t;
    typedef typename point_t::type num_t;

private:
    num_t       m_iWidth;
    num_t       m_iHeight;
    point_t     m_ptPosn;    //< upper left point of View
    point_t     m_ptCenter;  //< current center point

public:
    /// Default Constructor
    constexpr CView(void) noexcept
        : m_iWidth(),
          m_iHeight(),
          m_ptPosn(),
          m_ptCenter()
    { };

    /// Default Destructor
    ~CView() = default;

    bool Initialize      (num_t nX, num_t nY, num_t nWidth, num_t nHeight) noexcept;

    bool Update          (float fDeltaTime) noexcept;

///////////////////////////////////////////////////////////////////////////////
// Event Handlers
    void OnScrollEvent   (GAME_EVENT evt) noexcept;
    void OnTabKeyEvent   (num_t nFocusX,   num_t nFocusY) noexcept;
    void OnSizeEvent     (num_t nNewWidth, num_t nNewHeight) noexcept;

///////////////////////////////////////////////////////////////////////////////
// Accessors
    inline constexpr const auto&       get_Posn(void) const noexcept;
    inline constexpr auto              get_PosnX(void) const noexcept;
    inline constexpr auto              get_PosnY(void) const noexcept;

    inline void                        set_Posn(const point_t& ptSet) noexcept;
    inline void                        set_PosnX(num_t nSet) noexcept;
    inline void                        set_PosnY(num_t nSet) noexcept;
    inline void                       incr_Posn(const point_t& ptDelta) noexcept;

    inline constexpr const auto&       get_Center(void) const noexcept;
    inline constexpr auto              get_CenterX(void) const noexcept;
    inline constexpr auto              get_CenterY(void) const noexcept;

private:
    inline void                        set_Center(const point_t& ptSet) noexcept;
    inline void                        set_CenterX(num_t nSet) noexcept;
    inline void                        set_CenterY(num_t nSet) noexcept;

    inline void                       incr_Center(const point_t& ptDelta) noexcept;

    void Print        (void);

///////////////////////////////////////////////////////////////////////////////
// disabling the copy constructor and assignment operator
    CView(const CView&) = delete;
    CView& operator=(const CView&) = delete;
};

constexpr const auto&
CView::get_Posn(void) const noexcept
{
    return m_ptPosn;
};

void
CView::set_Posn(const point_t& ptSet) noexcept
{
    m_ptPosn = ptSet;
};

void
CView::incr_Posn(const point_t& ptDelta) noexcept
{
    m_ptPosn += ptDelta;
};

void
CView::set_PosnX(num_t nSet) noexcept
{
    m_ptPosn.X = nSet;
};

constexpr auto
CView::get_PosnX(void) const noexcept
{
    return m_ptPosn.X;
};

void
CView::set_PosnY(num_t nSet) noexcept
{
    m_ptPosn.Y = nSet;
};

constexpr auto
CView::get_PosnY(void) const noexcept
{
    return m_ptPosn.Y;
};

constexpr const auto&
CView::get_Center(void) const noexcept
{
    return m_ptCenter;
};

void
CView::set_Center(const point_t& ptSet) noexcept
{
    m_ptCenter = ptSet;
};

void
CView::incr_Center(const point_t& ptDelta) noexcept
{
    m_ptCenter += ptDelta;
};

void
CView::set_CenterX(num_t nSet) noexcept
{
    m_ptCenter.X = nSet;
};

constexpr auto
CView::get_CenterX(void) const noexcept
{
    return m_ptCenter.X;
};

void
CView::set_CenterY(num_t nSet) noexcept
{
    m_ptCenter.Y = nSet;
};

constexpr auto
CView::get_CenterY(void) const noexcept
{
    return m_ptCenter.Y;
};


#endif