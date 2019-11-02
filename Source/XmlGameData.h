/**
 *  @file       XmlGameData.h
 *  @brief      Raw Game data structures used by the Xml Parser
 *  @author     Mark L. Short
 *  @date       February 1, 2017
 *
 * <b>Course:</b>     CPSC 5377 Advanced Game Programming
 *
 * <b>Instructor:</b> Sean Orme
 *
 * <b>Assignment:</b> Zelda1 Project
 */
#pragma once

#if !defined(__XMLGAME_DATA_H__)
#define __XMLGAME_DATA_H__

#ifndef __COMMON_H__
    #include "Common.h"
#endif


 /**
    @brief primitive structure containing raw LEVEL data
 */
struct LEVEL_DATA
{
    tstring      m_strName;
    float        m_fX;
    float        m_fY;
    float        m_fAngle;

    /// default constructor
    constexpr LEVEL_DATA( void ) noexcept
        : m_strName(),
          m_fX(),
          m_fY(),
          m_fAngle()
    { };

    /// Copy constructor
    constexpr LEVEL_DATA( const LEVEL_DATA& othr ) noexcept
        : m_strName       ( othr.m_strName ),
          m_fX            ( othr.m_fX ),
          m_fY            ( othr.m_fY ),
          m_fAngle        ( othr.m_fAngle )
    { };

    /// Move constructor
    constexpr LEVEL_DATA(LEVEL_DATA&& othr) noexcept
        : m_strName(std::move(othr.m_strName)),
          m_fX(othr.m_fX),
          m_fY(othr.m_fY),
          m_fAngle(othr.m_fAngle)
    { };

    /// Assignment operator
    LEVEL_DATA& operator=(const LEVEL_DATA& rhs) noexcept
    {
        if (this != &rhs)
        {

            m_strName  = rhs.m_strName;
            m_fX       = rhs.m_fX;
            m_fY       = rhs.m_fY;
            m_fAngle   = rhs.m_fAngle;
        }
        return *this;
    };
};


/**
    @brief primitive structure containing raw OBJECT data
*/
struct OBJECT_DATA
{
    tstring      m_strName;
    tstring      m_strSpritePath;

    /// default constructor
    constexpr OBJECT_DATA(void) noexcept
        : m_strName(),
          m_strSpritePath()
    { };

    /// copy constructor
    constexpr OBJECT_DATA( const OBJECT_DATA& othr ) noexcept
        : m_strName       ( othr.m_strName ),
          m_strSpritePath ( othr.m_strSpritePath )
    { };

    /// Move constructor
    constexpr OBJECT_DATA(OBJECT_DATA&& othr) noexcept
        : m_strName(std::move(othr.m_strName)),
          m_strSpritePath(std::move(othr.m_strSpritePath))
    { };
    /// assignment operator
    OBJECT_DATA& operator=(const OBJECT_DATA& rhs ) noexcept
    {
        if (this != &rhs)
        {
            m_strName        = rhs.m_strName;
            m_strSpritePath  = rhs.m_strSpritePath;
        }
        return *this;
    };
};


#endif