/**
 *  @file       AssetLibrary.h
 *  @brief      TAssetLibrary template class definition
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
 *      *   map<string, shared_ptr<Texture>> library;
 *      *   GraphicsDevice* gDevice;
 *
 *   Capabilities:
 *      *   bool AddAsset(string, string);
 *      *   shared_ptr<Texture> Search(string);
 *
 * <b>Implementation Details:</b>
 *
 *   1. TAssetLibrary was originally meant as a base class
 *      for both CArtAssetLibrary & CGameAssetLibrary.
 *   2. However, CArtAssetLibrary & CGameAssetLibrary proved too
 *      divergent for this to be possible.
 *   3. In the alternative, TAssetLibrary is only used as the
 *      base class of CArtAssetLibrary.
 *
 */
#pragma once

#if !defined(__ASSET_LIBRARY_H__)
#define __ASSET_LIBRARY_H__

#ifndef __COMMON_H__
    #include "Common.h"
#endif

#ifndef _MAP_
    #include <map>
#endif // !_MAP_

#ifndef _MEMORY_
    #include <memory>
#endif // !_MEMORY_

template <class _TFactory, class _TAsset>
class TAssetLibrary
{
public:
    typedef typename _TFactory::smart_ptr  smart_ptr;

protected:

    std::unique_ptr<_TFactory>       m_pAssetFactory;
    std::map<tstring, smart_ptr >    m_mapAssets;

public:
    constexpr TAssetLibrary(void) noexcept
        : m_pAssetFactory(std::make_unique<_TFactory>()),
          m_mapAssets()
    { };

    /// Default Destructor
    virtual ~TAssetLibrary() = default;


    smart_ptr CreateAsset(void)
    {
        if (m_pAssetFactory)
            return m_pAssetFactory->Create();
        else
            return smart_ptr(nullptr);
    }

    template<class _Derived>
    smart_ptr CreateAsset(void)
    {
        if (m_pAssetFactory)
            return m_pAssetFactory->Create<_Derived>();
        else
            return smart_ptr(nullptr);
    }

    smart_ptr Search(const tstring & strName)
    {
        auto it = m_mapAssets.find(strName);
        if (it != m_mapAssets.end())
            return it->second;
        else
            return smart_ptr(nullptr);
    };

    /**
      @retval true      if asset was newly added
      @retval false     on error or if asset already existed
     */
    bool      AddAsset(const tstring& strName, const _TAsset& asset);

/////////////////////////////////////////////////////////////////////////
// disabling the copy constructor and assignment operator
    TAssetLibrary(const TAssetLibrary&) = delete;
    TAssetLibrary& operator=(const TAssetLibrary&) = delete;

};



template<class _TFactory, class _TAsset>
inline bool TAssetLibrary<_TFactory, _TAsset>::AddAsset(const tstring& strName, const _TAsset& asset)
{
    bool bRetVal = false;
    auto it = m_mapAssets.find(strName);
    if (it != m_mapAssets.end())
    {
    //    Do not add asset if it already exists
    //    it->second.reset(new _TAsset(asset));
    }
    else
    {
        m_mapAssets[strName] = std::move(m_pAssetFactory->Create(asset));
        bRetVal = true;
    }
    return bRetVal;
}



#endif