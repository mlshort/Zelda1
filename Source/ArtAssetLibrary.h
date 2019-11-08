/**
 *  @file       ArtAssetLibrary.h
 *  @brief      CArtAssetLibrary class definition
 *  @author     Mark L. Short
 *  @date       March 12, 2017
 *
 * <b>Course:</b>     CPSC 5377 Advanced Game Programming
 *
 * <b>Instructor:</b> Sean Orme
 *
 * <b>Assignment:</b> Zelda1 Project
 *
 *   This class contains the following (as well as initialization capabilities
 *   which are assumed for all classes) -
 *
 *   Properties:
 *       *   map<string, shared_ptr<Texture>> library;
 *       *   GraphicsDevice* gDevice;
 *
 *   Capabilities:
 *       *   bool AddAsset(string, string);
 *       *   shared_ptr<Texture> Search(string);
 *
 * <b>Implementation Details:</b>
 *
 *   1. The base template class TAssetLibrary<CTextureFactory, CTexture> implements the following:
 *       * map<string, shared_ptr<Texture>> library;
 *       * bool AddAsset(string, string);
 *       * shared_ptr<Texture> Search(string)
 */

#pragma once

#ifndef __ART_ASSET_LIBRARY_H__
#define __ART_ASSET_LIBRARY_H__

#ifndef __ASSET_LIBRARY_H__
    #include "AssetLibrary.h"
#endif // !__ART_ASSET_LIBRARY_H__

#ifndef __OBJECT_FACTORY_H__
    #include "ObjectFactory.h"
#endif

///////////////////////////////////////////////////////////////////////////////
//  Forward Declarations
class CTexture;
class CGraphicsDevice;

typedef TSharedFactory<CTexture>  CTextureFactory;

class CArtAssetLibrary
    : public TAssetLibrary<CTextureFactory, CTexture>
{
    CGraphicsDevice*    m_pGraphicsDev;

public:
    /// Default Constructor
    constexpr CArtAssetLibrary(void) noexcept
        : TAssetLibrary(),
          m_pGraphicsDev(nullptr)
    { };

   /// Default Destructor
    virtual ~CArtAssetLibrary(void) noexcept;

    /**
     * @brief This function sets the graphic's device for the library.
     *
     * @param [in] pDevice  pointer to the graphic device
     *
     * @retval true         on success
     * @retval false        on error or invalid pDevice
     */
    bool  Initialize(CGraphicsDevice* pDevice) noexcept;

    /**
     * @brief Adds a texture to the library based on the object's name and the filename of it's sprite
     *
     * @param [in] strAssetName   Name used as key value on adding asset to the library
     * @param [in] strFileName    Filename of the asset to load
     *
     * @retval true         on success
     * @retval false        on error or file not found
     */
    bool  LoadAsset(const tstring& strAssetName, const tstring& strFileName);

/////////////////////////////////////////////////////////////////////////
// disabling the copy constructor and assignment operator
    CArtAssetLibrary( const CArtAssetLibrary& ) = delete;
    CArtAssetLibrary& operator=( const CArtAssetLibrary& ) = delete;

};


#endif