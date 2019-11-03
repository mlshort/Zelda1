﻿/**
 *  @file       RedLeever.h
 *  @brief      CRedLeever class definition
 *  @author     Mark L. Short
 *  @date       March 12, 2017
 *
 * <b>Course:</b>     CPSC 5377 Advanced Game Programming
 *
 * <b>Instructor:</b> Sean Orme
 *
 * <b>Assignment:</b> Zelda1 Project
 *
 *   From the Object class we will derive multiple other classes (which will
 *   correspond with artistic assets and XML configuration files provided by
 *   the instructor):
 *
 *       *   Blue Octorok
 *       *   Red Octorok
 *       *   Blue Leever
 *       *   Red Leever
 *
 *   Each of these objects should contain properties and special capabilities
 *   necessary to provide unique behavior that suits them. Each object must
 *   overload the purely virtual method of its parent class in order to be
 *   instantiate-able. Each object must change its internal state via the
 *   Update method. Moreover, each object should display itself appropriately
 *   using the Draw method.
 *
 * <b>Implementation Details:</b>
 *
 */
#pragma once

#if !defined(__RED_LEEVER_H__)
#define __RED_LEEVER_H__

#ifndef __ACTOR_H__
    #include "Actor.h"
#endif

class CRedLeever :
    public CActor
{
public:
    /// Default Constructor
    constexpr CRedLeever(void) noexcept
        : CActor(ACT_RED_LEEVER)
    {};

    /// Copy Constructor
    constexpr CRedLeever(const CRedLeever& othr) noexcept
        : CActor(othr)
    {};

    /// Move Constructor
    CRedLeever(CRedLeever&& othr) noexcept
        : CActor( std::move(othr) )
    {};

    /// Default Destructor
    virtual ~CRedLeever();

/////////////////////////////////////////////////////////////////////////////
//  Base class pure virtual methods
    void Update(float fDeltaTime) noexcept override;
    void Render(const CView* pWhere) const override;

private:
    void          Move(float fDeltaTime) noexcept;
    void          Turn(float fDeltaTime) noexcept;
};

#endif
