/**
 *  @file       Window.h
 *  @brief      CWindow class definition
 *  @author     Mark L. Short
 *  @date       March 12, 2017
 *
 *  <b>Course:</b>     CPSC 5377 Advanced Game Programming
 *
 *  <b>Instructor:</b> Sean Orme
 *
 *  <b>Assignment:</b> Zelda1 Project
 */
#pragma once

#if !defined(__WINDOW_H__)
#define __WINDOW_H__

#ifndef _TYPE_TRAITS_
    #include <type_traits>
#endif
#ifndef __SDL_HANDLE_H__
    #include "SDLHandle.h"
#endif

///////////////////////////////////////////////////////////////////////////////
//  Forward Declarations
struct SDL_Window;
struct SDL_Renderer;
struct SDL_Surface;
class  CRenderer;
class  CWindow;

typedef TSDLHandle_Base<SDL_Window, CWindow>   WINDOW_HANDLE;

/**
 *  @brief An encapsulation of an SDL_Window context
 */
class CWindow
    : public WINDOW_HANDLE
{
    bool        m_bFullScreen;

public:
    /// Default Consturctor
    constexpr CWindow() noexcept
        : m_bFullScreen(false),
          WINDOW_HANDLE(nullptr)
    { };

    /// Initialization Constructor
    constexpr explicit CWindow(bool bFullScreen) noexcept
        : m_bFullScreen(bFullScreen),
          WINDOW_HANDLE(nullptr)
    { };

    /// Default Destructor
    ~CWindow() noexcept;

    bool Initialize(bool bFullScreen) noexcept;

    /**
     *  @brief Destroys & clears the underlying SDL resource
     */
    void               Destroy (void) noexcept;

    /**
     *  @brief Creates the underlying SDL Window context
     *
     *  @param [in] szName  The title of the window, in UTF-8 encoding.
     *  @param [in] iX      The x position of the window,
     *                      SDL_WINDOWPOS_CENTERED, or SDL_WINDOWPOS_UNDEFINED.
     *  @param [in] iY      The y position of the window,
     *                      SDL_WINDOWPOS_CENTERED, or SDL_WINDOWPOS_UNDEFINED.
     *  @param [in] iWidth  The width of the window, in screen coordinates.
     *  @param [in] iHeight The height of the window, in screen coordinates.
     *
     *  @retval true        if the window was created window
     *  @retval false       if window creation failed.
     */
    bool           Create        (const char* szName, int iX, int iY, int iWidth, int iHeight) noexcept;

    /**
     *  @brief Create a 2D SDL rendering context for this window.
     *
     *  @param [in] iIndex    The index of the rendering driver to initialize, or -1 to
     *                        initialize the first one supporting the requested flags.
     *  @param [in] flags     see SDL_RendererFlags
     *
     *  @retval SDL_Renderer*  containing a valid rendering context on success
     *  @retval nullptr        on error
     *
     *  @sa https://wiki.libsdl.org/SDL_CreateRenderer
     */
    SDL_Renderer*  CreateRenderer(int iIndex, unsigned int flags) noexcept;

    /**
     *  @brief Create a 2D CRenderer object for this window
     *
     *  @param [in] iIndex    The index of the rendering driver to initialize, or -1 to
     *                        initialize the first one supporting the requested flags.
     *  @param [in] flags     see SDL_RendererFlags
     *
     *  @retval CRenderer*     containing a valid rendering context on success
     *  @retval nullptr        on error
     */
    CRenderer*  CreateRendererEx(int iIndex, unsigned int flags);

    /**
     *  @brief Gets the SDL rendering context associated with this window.
     */
    SDL_Renderer*   GetRenderer(void) noexcept;

    /**
     *  @brief Get the SDL surface context associated with the window.
     *
     *  A new surface will be created with the optimal format for the window,
     *  if necessary. This surface will be freed when the window is destroyed.
     *
     *  @retval SDL_Surface*  containing the window's framebuffer surface
     *  @retval nullptr       on error.
     *
     */
    SDL_Surface*    GetSurface(void) noexcept;

    /**
     *  @brief Set the position of the underlying SDL Window context
     *
     *  @param iX        The x coordinate of the window in screen coordinates, or
     *                   SDL_WINDOWPOS_CENTERED or SDL_WINDOWPOS_UNDEFINED.
     *  @param iY        The y coordinate of the window in screen coordinates, or
     *                   SDL_WINDOWPOS_CENTERED or SDL_WINDOWPOS_UNDEFINED.
     *
     *  @retval true     on success
     *  @retval false    on failure
     *
     *  @note The window coordinate origin is the upper left of the display.
     *
     *  @sa https://wiki.libsdl.org/SDL_SetWindowPosition
     */
    bool            SetPosition(int iX, int iY) noexcept;

///////////////////////////////////////////////////////////////////////////////
// disabling the copy constructor and assignment operator
    CWindow(const CWindow&) = delete;
    CWindow& operator=(const CWindow&) = delete;
};

#endif
