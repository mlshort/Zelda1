/**
 *  @file       GraphicsDevice.h
 *  @brief      CGraphicsDevice class definition
 *  @author     Mark L. Short
 *  @date       March 12, 2017
 *
 *  <b>Course:</b>     CPSC 5377 Advanced Game Programming
 *
 *  <b>Instructor:</b> Sean Orme
 *
 *  <b>Assignment:</b> Zelda1 Project
 *
 *  <b>Cite:</b>
 *      * Sample code by Dr. Keith Bush, Sean Orme
 */
#pragma once

#ifndef __GRAPHICS_DEVICE_H__
#define __GRAPHICS_DEVICE_H__


///////////////////////////////////////////////////////////////////////////////
//  Forward Declarations
class  CWindow;
class  CRenderer;

class CGraphicsDevice
{
    CWindow*           m_pMainWindow;
    CRenderer*         m_pRenderer;

    //Parameter
    const unsigned int m_nScreenWidth;
    const unsigned int m_nScreenHeight;

public:
    /// Initialization constructor
    constexpr explicit CGraphicsDevice(unsigned int nWidth, unsigned int nHeight) noexcept
        : m_pMainWindow  (nullptr),
          m_pRenderer    (nullptr),
          m_nScreenWidth (nWidth),
          m_nScreenHeight(nHeight)
    { };

    /// Default Destructor
    ~CGraphicsDevice();

   /**
     *  @retval true on success
     *  @retval false on error
     */
    bool Initialize(bool bFullScreen);

   /**
     *  @retval true on success
     *  @retval false on error
     */
    bool ShutDown  (void) noexcept;

    /**
     *  @brief Clear the underlying SDL rendering target with the current drawing color
     *
     *  This function clears the entire rendering target, ignoring the viewport and
     *  the clip rectangle.
     *
     *  @retval true on success
     *  @retval false on error
     */
    bool Clear  (void) noexcept;

    /**
     *  @brief Update the screen with rendering performed
     *
     *  @retval true on success
     *  @retval false on error
     */
    bool Present(void) noexcept;

    constexpr inline auto GetRenderer(void) noexcept
    { return m_pRenderer; };

///////////////////////////////////////////////////////////////////////////////
// disabling the copy constructor and assignment operator
    CGraphicsDevice(const CGraphicsDevice&) = delete;
    CGraphicsDevice& operator=(const CGraphicsDevice&) = delete;

};

#endif