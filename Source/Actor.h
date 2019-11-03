/**
 *  @file       Actor.h
 *  @brief      CActor abstract base class definition
 *  @author     Mark L. Short
 *  @date       March 12, 2017
 *
 * <b>Course:</b>     CPSC 5377 Advanced Game Programming
 *
 * <b>Instructor:</b> Sean Orme
 *
 * <b>Assignment:</b> Zelda1 Project
 *
 *   The Object class is an abstract class meant to be a generic on which the
 *   specific game objects are derived. In addition to default construction,
 *   destruction, and Initialization capability, the Object class has the
 *   following -
 *
 *   Properties:
 *       *   GraphicsDevice* gDevice;
 *       *   InputDevice* iDevice;
 *       *   shared_ptr<Texture> texture;
 *       *   GAME_VEC position;
 *       *   GAME_VEC startPosition;
 *       *   GAME_FLT angle;
 *
 *   Capabilities:
 *       *   virtual void Update(GAME_FLT) = 0;
 *       *   virtual void Draw(GAME_FLT, View*) = 0;
 *       *   as well as necessary accessor methods
 *
 * <b>Implementation Details:</b>
 *
 *      *   CActor is the "Object" class implementation
 *      *   various type & name changes, in accordance with naming conventions, etc...
 *      *   Draw(GAME_FLT, View*) implemented as Render(CView* pWhere)
 *      *   InputDevice* iDevice REMOVED.
 *              - A design decision was made to not have individual actor objects polling for input data.
 */
#pragma once

#if !defined (__ACTOR_H__)
#define __ACTOR_H__

#ifndef __COMMON_H__
    #include "Common.h"
#endif

#ifndef _MEMORY_
    #include <memory>
#endif

#ifndef __IRENDERABLE_H__
    #include "IRenderable.h"
#endif

#ifndef __VECTOR2_H__
    #include "Utility\Vector2.h"
#endif

///////////////////////////////////////////////////////////////////////////////
//  Forward Declarations
class CGraphicsDevice;
class CInputDevice;
class CTexture;
class CView;


/**
    @brief CActor is the arch-type Object base class

    Regarding mathematical POINTs and VECTORs (assumed 2D in this context)
        POINTs are simply an x,y coordinate pair; however,
        VECTORs can also be represented as an x,y coordinate pair.  BUT a vector inherently
        is a representation of both "Magnitude" & "Direction", whereas a POINT is nothing
        more than a location in 2d space.

    For simplicity, the VECTOR (vec_t) and the POINT (point_t) types have both been implemented using the
    same CVector2f template type.  This is not precisely correct.  Certain mathematical operations have
    questionable results when performed between a VECTOR and a POINT.  Additionally, a POINT has no
    "Direction" or "Magnitude".

    There have been some liberties taken regarding a POINT (x,y) being equivalent to the VECTOR [x, y] in
    certain contexts.  This is not correct and the code should be written such it prevents these types from
    being used in the wrong context.

    For example, Velocity is represented as VECTOR (having both direction and magnitude).  It should not be
    acceptable or possible to do something like:

        vec_t v(0,0);
        point_t pt(10,10);

        v = pt;  // THIS SHOULD CREATE A COMPILE ERROR, but probably doesn't.

    I do not have time to correctly address this.

*/
class __declspec(novtable) CActor
    : public IRenderable
{
public:
    typedef typename CVector2f     vec_t;
    typedef typename CVector2f     point_t;
    typedef typename point_t::type num_t;

protected:
    ACTOR_T                   m_Type;
    CGraphicsDevice*          m_pGraphicsDevice;
    std::shared_ptr<CTexture> m_pTexture;

    point_t                   m_ptPosn;         //< Current Position Point
    point_t                   m_ptStart;        //< Initial Start Point
    vec_t                     m_vVelocity;      //< Linear Velocity
    DEGREES                   m_degDirection;   //< Orientation in Degrees
    num_t                     m_nMaxRange;      //< Maximum distance from start

public:
    /// Default Constructor
    constexpr CActor::CActor(void) noexcept
        : IRenderable(),
          m_Type(ACT_INVALID),
          m_pGraphicsDevice(nullptr),
          m_pTexture(),
          m_ptPosn(),
          m_ptStart(),
          m_vVelocity(),
          m_degDirection(),
          m_nMaxRange()
    { };
    /// Initialization Constructor
    constexpr explicit CActor::CActor(ACTOR_T type) noexcept
        : IRenderable(),
          m_Type(type),
          m_pGraphicsDevice(nullptr),
          m_pTexture(),
          m_ptPosn(),
          m_ptStart(),
          m_vVelocity(),
          m_degDirection(),
          m_nMaxRange()
    { };
    /// Copy Constructor
    constexpr CActor(const CActor& othr) noexcept;
    /// Move Constructor
    CActor(CActor&& othr) noexcept;
    /// Default Destructor
    virtual  ~CActor(void);
    /// Assignment Operator
    CActor& operator=(const CActor& rhs) noexcept;
    /// Move Assignment Operator
    CActor& operator=(CActor&& rhs) noexcept;

    void         Initialize(num_t nX, num_t nY, DEGREES fAngle) noexcept;
    void         SetTexture(std::shared_ptr<CTexture> pTexture) noexcept;
    void         SetDevices(CGraphicsDevice* pGraphicsDev) noexcept;

///////////////////////////////////////////////////////////////////////////////
// IRenderable virtual methods
    virtual void Update(float fDeltaTime) = 0;
    virtual void Render(const CView* pWhere) const = 0;

///////////////////////////////////////////////////////////////////////////////
// Trivial Accessors
    inline constexpr const auto&       get_Start(void) const noexcept;

    inline constexpr const auto&       get_Posn(void) const noexcept;
    inline void                        set_Posn(num_t nX, num_t nY) noexcept;
    inline void                        set_Posn(const point_t& ptSet) noexcept;
    inline void                       incr_Posn(const point_t& ptDelta) noexcept;

    inline void                        set_PosnX(num_t nSet) noexcept;
    inline constexpr auto              get_PosnX(void) const noexcept;

    inline void                        set_PosnY(num_t nSet) noexcept;
    inline constexpr auto              get_PosnY(void) const noexcept;

    inline constexpr const auto&       get_Velocity(void) const noexcept;
    inline void                        set_Velocity(const vec_t& vSet) noexcept;
    inline void                        set_Velocity(num_t nX, num_t nY) noexcept;
    inline void                       incr_Velocity(const vec_t& vDelta) noexcept;

    inline constexpr auto              get_Direction(void) const noexcept;
    inline void                        set_Direction(DEGREES degSet) noexcept;
    inline void                       incr_Direction(DEGREES degDelta) noexcept;

    inline constexpr auto              get_MaxRange  (void) const noexcept;
    inline void                        set_MaxRange  (num_t nSet) noexcept;
};

constexpr const auto&
CActor::get_Start(void) const noexcept
{
    return m_ptStart;
};

constexpr const auto&
CActor::get_Posn(void) const noexcept
{
    return m_ptPosn;
};

void
CActor::set_Posn(num_t nX, num_t nY) noexcept
{
    m_ptPosn.Init(nX, nY);
};

void
CActor::set_Posn(const point_t& ptSet) noexcept
{
    m_ptPosn = ptSet;
};

void
CActor::incr_Posn(const point_t& ptDelta) noexcept
{
    m_ptPosn += ptDelta;
};

void
CActor::set_PosnX(num_t nSet) noexcept
{
    m_ptPosn.X = nSet;
};

constexpr auto
CActor::get_PosnX(void) const noexcept
{
    return m_ptPosn.X;
};

void
CActor::set_PosnY(num_t nSet) noexcept
{
    m_ptPosn.Y = nSet;
};

constexpr auto
CActor::get_PosnY(void) const noexcept
{
    return m_ptPosn.Y;
};

void
CActor::set_Velocity(num_t nX, num_t nY) noexcept
{
    m_vVelocity.Init(nX, nY);
};

void
CActor::set_Velocity(const vec_t& vSet) noexcept
{
    m_vVelocity = vSet;
};

constexpr const auto&
CActor::get_Velocity(void) const noexcept
{
    return m_vVelocity;
};

void
CActor::incr_Velocity(const vec_t& vDelta) noexcept
{
    m_vVelocity += vDelta;
};

constexpr auto
CActor::get_Direction(void) const noexcept
{
    return m_degDirection;
};

void
CActor::set_Direction(DEGREES degSet) noexcept
{
    m_degDirection = degSet;
};

void
CActor::incr_Direction(DEGREES degDelta) noexcept
{
    m_degDirection += degDelta;
};

constexpr auto
CActor::get_MaxRange(void) const noexcept
{
    return m_nMaxRange;
};

void
CActor::set_MaxRange(num_t nSet) noexcept
{
    m_nMaxRange = nSet;
};
#endif

