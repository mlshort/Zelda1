/**
 *  @file       IRenderable.h
 *  @brief      IRenderable abstract base class interface definition
 *  @author     Mark L. Short
 *  @date       March 12, 2017
 *
 *  <b>Course:</b>     CPSC 5377 Advanced Game Programming
 *
 *  <b>Instructor:</b> Sean Orme
 *
 *  <b>Assignment:</b> Zelda1
 *
 */
#pragma once

#if !defined(__IRENDERABLE_H__)
#define __IRENDERABLE_H__

///////////////////////////////////////////////////////////////////////////////
//  Forward Declarations
class CView;

struct __declspec(novtable) IRenderable
{
    virtual ~IRenderable() = default;

    virtual void    Update(float fDeltaTime) = 0;
    virtual void    Render(const CView* pWhere) const = 0;
};


#endif