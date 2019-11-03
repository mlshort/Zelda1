/**
 *  @file       Renderer.h
 *  @brief      CRenderer class definition
 *  @author     Mark L. Short
 *  @date       March 12, 2017
 *
 *  <b>Course:</b>     CPSC 5377 Advanced Game Programming
 *
 *  <b>Instructor:</b> Sean Orme
 *
 *  <b>Assignment:</b> Zelda1 Project
 *
 */
#pragma once

#if !defined(__RENDERER_H__)
#define __RENDERER_H__

#ifndef _TYPE_TRAITS_
    #include <type_traits>
#endif
#ifndef __COMMON_H__
    #include "Common.h"
#endif
#ifndef __SDL_HANDLE_H__
    #include "SDLHandle.h"
#endif

///////////////////////////////////////////////////////////////////////////////
//  Forward Declarations
struct SDL_Renderer;
struct SDL_RendererInfo;
struct SDL_Rect;
struct SDL_Texture;
class CRenderer;

typedef TSDLHandle_Base<SDL_Renderer, CRenderer>  RENDERER_HANDLE;

/**
 *  @brief An encapsulation of an SDL_Renderer context
 */
class CRenderer
    : public RENDERER_HANDLE
{

public:
    /// Default constructor
    constexpr CRenderer(void) noexcept
        : RENDERER_HANDLE(nullptr, true)
    { };

    /// Initialization Constructor
    /// @note takes ownership of pSDLRenderer
    constexpr explicit CRenderer(SDL_Renderer* pSDLRenderer) noexcept
        : RENDERER_HANDLE(pSDLRenderer)
    { };

    /// Default Destructor
    ~CRenderer();

   /**
    *  @brief Clear the current rendering target with the drawing color
    *
    *  This function clears the entire rendering target, ignoring the viewport and
    *  the clip rectangle.
    *
    *  @retval true         on success
    *  @retval false        on error
    */
    bool Clear(void) noexcept;

    /**
     *  @brief Update screen with rendering performed
     *
     *  @retval true        on success
     *  @retval false       on error
     */
    bool Present    (void) noexcept;

    /**
     *  @brief Set the drawing area for rendering on the current target
     *
     *  @param [in] rect    The rectangle representing the drawing area
     *                      The x,y of the viewport rect represents the origin
     *                      for rendering
     *
     *  @retval true        on success
     *  @retval false       on error
     *
     *  @note If the window associated with the renderer is resized, the viewport
     *        is automatically reset.
     */
    bool SetViewPort(const SDL_Rect& rect) noexcept;

    /**
     *  @brief Copy a portion of the texture to the current rendering target.
     *
     *  @param [in,out] pSDLTexture     The source texture.
     *  @param [in]     pSrcRect        The source rectangle, or nullptr for the entire
     *                                  texture.
     *  @param [in]     pDestRect       The destination rectangle, or nullptr for the
     *                                  entire rendering target.
     *
     *  @retval true                    on success
     *  @retval false                   on error
     */
    bool Copy       (SDL_Texture* pSDLTexture, const SDL_Rect* pSrcRect = nullptr, const SDL_Rect* pDestRect = nullptr);

    /**
     *  @brief Copy a portion of the source texture to the current rendering target, rotating it by angle around the given center
     *
     *  @param [in,out] pSDLTexture     The source texture.
     *  @param [in]     pSrcRect        The source rectangle, or nullptr for the entire
     *                                  texture
     *  @param [in]     pDestRect       The destination rectangle, or nullptr for the
     *                                  entire rendering target
     *  @param [in]     fAngle          An angle in degrees that indicates the rotation that will be applied to pDestRect
     *  @param [in]     pCenter         Point indicating the point around which pDestRect will be rotated
     *                                  (if nullptr, rotation will be done around pDestRect.w/2, pDestRect.h/2)
     *  @param [in]     iFlip           An SDL_RendererFlip value stating which flipping actions should be performed on
     *                                  the texture
     *
     *  @retval true    on success
     *  @retval false   on error
     */
    bool CopyEx     (SDL_Texture* pSDLTexture, const SDL_Rect* pSrcRect, const SDL_Rect* pDestRect,
                     DEGREES fAngle, const SDL_Point* pCenter, int iFlip);

    /// Deallocates managed SDL resource
    void Destroy    (void) noexcept;

    /**
     *  @brief Get the output size in pixels of the rendering context
     *
     *  @param [out] iWidth
     *  @param [out] iHeight
     *
     *  @retval true         on success
     *  @retval false        on error
     */
    bool GetOutputSize(int& iWidth, int& iHeight) noexcept;

   /**
    *  @brief Get information about this rendering context.
    *
    *  @param [out] info
    *
    *  @retval true         on success
    *  @retval false        on error
    */
    bool GetInfo(SDL_RendererInfo& info) noexcept;

    /**
     *  @brief Set the color used for drawing operations (Rect, Line and Clear).
     *
     *  @param [in] nRed    The red value used to draw on the rendering target.
     *  @param [in] nGreen  The green value used to draw on the rendering target.
     *  @param [in] nBlue   The blue value used to draw on the rendering target.
     *  @param [in] nAlpha  The alpha value used to draw on the rendering target,
     *                      usually SDL_ALPHA_OPAQUE (255).
     *
     *  @retval true        on success
     *  @retval false       on error
     */
    bool SetDrawColor(uint8_t nRed, uint8_t nGreen, uint8_t nBlue, uint8_t nAlpha) noexcept;

    /**
     *  @brief Create a texture from an existing surface.
     *
     *  @param [in,out] pSDLSurface     The surface containing pixel data used to fill the texture.
     *
     *  @retval SDL_Texture*            on success, containing created texture
     *  @retval nullptr                 on error
     *
     *  @note The surface is not modified or freed by this function.
     *
     */
    SDL_Texture* CreateTextureFromSurface(SDL_Surface* pSDLSurface);

    /**
     *  @brief Get whether integer scales are forced for resolution-independent rendering
     *
     *  @retval true        if integer scaling is enabled
     *  @retval false       on error or if integer scaling disabled
     */
    bool IsUsingIntegerScale(void) noexcept;


///////////////////////////////////////////////////////////////////////////////
// disabling the copy constructor and assignment operator
    CRenderer(const CRenderer&) = delete;
    CRenderer& operator=(const CRenderer&) = delete;
};

#endif

