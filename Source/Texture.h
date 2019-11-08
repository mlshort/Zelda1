/**
 * @file       Texture.h
 * @brief      CTexture class definition
 * @author     Mark L. Short
 * @date       March 12, 2017
 *
 *
 * <b>Course:</b>     CPSC 5377 Advanced Game Programming
 *
 * <b>Instructor:</b> Sean Orme
 *
 * <b>Assignment:</b> Zelda1 Project
 *
 *   A simple way to implement the desired Viewing functionality is to modify
 *   the Texture class.  The Texture class is a conduit by which art resources
 *   represent objects in the game. However, the texture may apply conditions
 *   to this representation, e.g., by modifying the object’s visual representation
 *   to include a perspective as encoded in the View class. In this task, the
 *   Texture class has identical properties and capabilities as the examples shown
 *   in class except that the Render and RenderEx capabilities have been replaced
 *   with the following capability:
 *
 *       *   void Draw(SDL_Renderer* renderer, View* view, GAME_VEC position,
 *                      GAME_FLT angle, SDL_Rect* clip = nullptr );
 *
 *   Using this data the object can determine the appropriate transformation of its
 *   position and angle in order to achieve the appropriate graphical effect.
 *
 */
#pragma once

#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#ifndef _INC_TCHAR
    #include <tchar.h>
#endif
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
struct SDL_Rect;
struct SDL_Texture;
class  CRenderer;
class  CView;
class  CTexture;

typedef TSDLHandle_Base<SDL_Texture, CTexture>  TEXTURE_HANDLE;

/**
 *  @brief An encapsulation of an SDL_Texture context
 */
class CTexture
    : public TEXTURE_HANDLE
{
    //Image dimensions
    int          m_iWidth;
    int          m_iHeight;

public:
    /// Default Constructor
    constexpr CTexture(void) noexcept
        : TEXTURE_HANDLE(nullptr, true),
          m_iWidth(),
          m_iHeight()
    { };

    /// Copy Constructor
    constexpr CTexture(const CTexture& othr) noexcept
        : TEXTURE_HANDLE    (othr),
          m_iWidth          (othr.m_iWidth),
          m_iHeight         (othr.m_iHeight)
    { };

    /// Move Constructor
    CTexture(CTexture&& othr) noexcept
        : TEXTURE_HANDLE    ( std::move(othr) ),
          m_iWidth          ( othr.m_iWidth ),
          m_iHeight         ( othr.m_iHeight )
    { };

    /// Default Destructor
    ~CTexture() noexcept;

    /// Assignment Operator
    CTexture& operator=(const CTexture& rhs) noexcept;

    /// Assignment Move Operator
    CTexture& operator=(CTexture&& rhs) noexcept;

    /// Deallocates managed SDL resource
    void Destroy(void) noexcept;

    /// Returns Image Width
    constexpr int GetWidth(void) const noexcept
    { return m_iWidth; };

    /// Returns Image Height
    constexpr int GetHeight(void) const noexcept
    { return m_iHeight; };

    /**
      *  @brief Loads image file from specified path
      *
      *  @param [in] pRenderer
      *  @param [in] szPath
      *
      *  @retval true         on success
      *  @retval false        on error
      */
    bool Load(CRenderer* pRenderer, const TCHAR* szPath );

    /// Set color modulation
    bool SetColor(uint8_t nRed, uint8_t nGreen, uint8_t nBlue) noexcept;

    /// Renders texture at given point
    bool Render  (CRenderer* pRenderer, int iX, int iY, const SDL_Rect* pSDLRect = nullptr );
    bool Render  (CRenderer* pRenderer, int iX, int iY, DEGREES fAngle, const SDL_Rect* pSDLRect = nullptr );
    /// Renders texture using CView information
    bool Render  (CRenderer* pRenderer, const CView* pView, int iX, int iY, DEGREES fAngle, const SDL_Rect* pSDLRect);
    bool Render  (CRenderer* pRenderer, const CView* pView, int iX, int iY, DEGREES fAngle);

    /**
    *  @brief Query the attributes of a texture
    *
    *  @param [out] nFormat     The raw format of the texture.  The actual format
    *                           may differ, but pixel transfers will use this
    *                           format.
    *  @param [out] iAccess     The actual access to the texture.
    *  @param [out] iWidth      The width of the texture in pixels.
    *  @param [out] iHeight     The height of the texture in pixels.
    *
    *  @retval true             on success
    *  @retval false            on error or if the texture is not valid.
    */
    bool Query(uint32_t& nFormat, int& iAccess, int& iWidth, int& iHeight) noexcept;

    /**
    *  @brief Set an additional color value used in render copy operations.
    *
    *  @param [in] nRed         The red color value multiplied into copy operations.
    *  @param [in] nGreen       The green color value multiplied into copy operations.
    *  @param [in] nBlue        The blue color value multiplied into copy operations.
    *
    *  @retval true             on success
    *  @retval false            if the texture is not valid or color modulation
    *                           is not supported
    *
    */
    bool SetColorMod(uint8_t nRed, uint8_t nGreen, uint8_t nBlue) noexcept;

    /**
    *  @brief Get the additional color value used in render copy operations.
    *
    *  @param [out] nRed        The current red color value.
    *  @param [out] nGreen      The current green color value.
    *  @param [out] nBlue       The current blue color value.
    *
    *  @retval true             on success
    *  @retval false            on error or if the texture is not valid.
    *
    */
    bool GetColorMod(uint8_t& nRed, uint8_t& nGreen, uint8_t& nBlue) noexcept;

    /**
    *  @brief Set an additional alpha value used in render copy operations.
    *
    *  @param [in] alpha        The alpha value multiplied into copy operations.
    *
    *  @retval true             on success
    *  @retval false            if the texture is not valid or alpha modulation
    *                           is not supported.
    */
    bool SetAlphaMod(uint8_t alpha) noexcept;

    /**
    *  @brief Get the additional alpha value used in render copy operations.
    *
    *  @param [out] alpha       The current alpha value.
    *
    *  @retval true             on success
    *  @retval false            on error or if the texture is not valid.
    *
    */
    bool GetAlphaMod(uint8_t& alpha) noexcept;

    /**
    *  @brief Update the given texture rectangle with new pixel data.
    *
    *  @param [in] pSDLRect     The rectangle of pixels to update, or nullptr to
    *                           update the entire texture.
    *  @param [in] pPixels      The raw pixel data.
    *  @param [in] cbPitch      The number of bytes in a row of pixel data, including padding
    *                           between lines.
    *
    *  @retval true             on success
    *  @retval false            on error or if the texture is not valid.
    *
    *  @note This is a fairly slow function.
    */
    bool Update(const SDL_Rect* pSDLRect, const void* pPixels, int cbPitch) noexcept;

    /**
    *  @brief Update a rectangle within a planar YV12 or IYUV texture with new pixel data.
    *
    *  @param [in] pSDLRect     The rectangle of pixels to update, or nullptr to
    *                           update the entire texture.
    *  @param [in] pYplane      The raw pixel data for the Y plane.
    *  @param [in] cbYpitch     The number of bytes between rows of pixel data for the Y plane.
    *  @param [in] pUplane      The raw pixel data for the U plane.
    *  @param [in] cbUpitch     The number of bytes between rows of pixel data for the U plane.
    *  @param [in] pVplane      The raw pixel data for the V plane.
    *  @param [in] cbVpitch     The number of bytes between rows of pixel data for the V plane.
    *
    *  @retval true             on success
    *  @retval false            if the texture is not valid.
    *
    */
    bool UpdateYUV(const SDL_Rect* pSDLRect,
                    const uint8_t* pYplane, int cbYpitch,
                    const uint8_t* pUplane, int cbUpitch,
                    const uint8_t* pVplane, int cbVpitch) noexcept;

    /**
    *  @brief Lock a portion of the texture for write-only pixel access.
    *
    *  @param [in] pSDLRect     A pointer to the rectangle to lock for access. If the rect
    *                           is nullptr, the entire texture will be locked.
    *  @param [out] ppPixels    This is filled in with a pointer to the locked pixels,
    *                           appropriately offset by the locked area.
    *  @param [out] nPitch      This is filled in with the pitch of the locked pixels.
    *
    *  @retval true             on success
    *  @retval false            if the texture is not valid or was not created with
    *                           SDL_TEXTUREACCESS_STREAMING
    */
    bool Lock(const SDL_Rect* pSDLRect, void** ppPixels, int& nPitch) noexcept;

    /**
    *  @brief Unlock a texture, uploading the changes to video memory, if needed.
    *
    *  @retval true             on success
    *  @retval false            if the texture is not valid
    */
    bool Unlock(void) noexcept;
};

#endif