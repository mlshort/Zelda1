/**
 *  @file       GameAssetLibrary.h
 *  @brief      CGameAssetLibrary class definition
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
 *   which are assumed for all classes) at minimum -
 *
 *   Property:
 *      * map<string,unique_ptr<ObjectFactory>> library;
 *
 *   Capability:
 *      * unique_ptr<Object> Search(string);
 *
 *   Each of the derived classes should be instantiated using an appropriate
 *   Factory class derived from a ObjectFactory class with respective overloaded
 *   unique_ptr<Object> create() methods (see class notes, example, and solution key
 *   to Homework 0). See the GameAssetLibrary class for how these factories will be
 *   used.
 *
 * <b>Implementation Details:</b>
 *
 *   1. The TUniqueFactory template class implements the required properties and capabilities.
 *
 */

#pragma once

#if !defined(__GAME_ASSET_LIBRARY_H__)
#define __GAME_ASSET_LIBRARY_H__

#ifndef __OBJECT_FACTORY_H__
    #include "ObjectFactory.h"
#endif

///////////////////////////////////////////////////////////////////////////////
//  Forward Declarations
class CActor;
class CRedLeever;
class CBlueLeever;
class CRedOctorok;
class CBlueOctorok;


typedef TUniqueFactory<CRedLeever>   CRedLeeverFactory;
typedef TUniqueFactory<CBlueLeever>  CBlueLeeverFactory;
typedef TUniqueFactory<CRedOctorok>  CRedOctorokFactory;
typedef TUniqueFactory<CBlueOctorok> CBlueOctorokFactory;


class CGameAssetLibrary
{
    CRedLeeverFactory   m_RedLeeverFactory;
    CBlueLeeverFactory  m_BlueLeeverFactory;
    CRedOctorokFactory  m_RedOctorokFactory;
    CBlueOctorokFactory m_BlueOctorokFactory;
public:
    /// Default Constructor
    constexpr CGameAssetLibrary(void) noexcept
        : m_RedLeeverFactory(),
          m_BlueLeeverFactory(),
          m_RedOctorokFactory(),
          m_BlueOctorokFactory()
    { };

    /// Default Destructor
    virtual ~CGameAssetLibrary();

    bool                    Initialize(void) noexcept;

    std::unique_ptr<CActor> CreateAsset(const tstring& strAssetType);

/////////////////////////////////////////////////////////////////////////
// disabling the copy constructor and assignment operator
    CGameAssetLibrary(const CGameAssetLibrary&) = delete;
    CGameAssetLibrary& operator=(const CGameAssetLibrary&) = delete;

};

#endif
