/**
 *  @file       XmlGameDataHandler.cpp
 *  @brief      CXmlObjectDataHandler, CXmlLevelDataHandler class implementation(s)
 *  @author     Mark L. Short
 *  @date       March 12, 2017
 *
 *  <b>Course:</b>     CPSC 5377 Advanced Game Programming
 *
 *  <b>Instructor:</b> Sean Orme
 *
 *  <b>Assignment:</b> Zelda1 Project
 */
#ifdef _DEBUG
    #define _CRTDBG_MAP_ALLOC
    #include <stdlib.h>
    #include <crtdbg.h>
#endif
#ifdef _DEBUG
    #define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
    #define new DEBUG_NEW
#endif

#include "XmlGameDataHandler.h"

#define GET_XML_ATTRIB_STR(_Test, _Loc, _attrib, _value) if ( _tcsicmp( _Test, _attrib )==0 ) { _Loc = _value; }
#define GET_XML_ATTRIB_INT(_Test, _Loc, _attrib, _value) if ( _tcsicmp( _Test, _attrib )==0 ) { _Loc = _ttoi( _value ); }
#define GET_XML_ATTRIB_FLOAT(_Test, _Loc, _attrib, _value) if ( _tcsicmp( _Test, _attrib )==0 ) { _Loc = static_cast<float>(_ttof( _value )); }
#define GET_XML_ATTRIB_CHAR(_Test, _Loc, _attrib, _value) if ( _tcsicmp( _Test, _attrib )==0 ) { _Loc = _value[0]; }


void CXmlObjectDataHandler::OnElementInit(const TCHAR* pszName)
{
    if ( _tcsicmp( _T( "Creature" ), pszName ) == 0 )
    {
        OBJECT_DATA object;
        m_rgData.push_back( object );
        m_pData = &m_rgData.back();
    }
};

void CXmlLevelDataHandler::OnElementInit(const TCHAR* pszName)
{
    if (_tcsicmp( _T( "GameAsset" ), pszName) == 0)
    {
        LEVEL_DATA level;
        m_rgData.push_back(level);
        m_pData = &m_rgData.back();
    }
};


void CXmlObjectDataHandler::OnAttribute(const TCHAR* pszName, const TCHAR* pszValue)
{
    if (m_pData)
    {
        GET_XML_ATTRIB_STR( _T( "Name" ), m_pData->m_strName, pszName, pszValue )
        GET_XML_ATTRIB_STR( _T( "Sprite" ), m_pData->m_strSpritePath, pszName, pszValue )
    }
};

void CXmlLevelDataHandler::OnAttribute(const TCHAR* pszName, const TCHAR* pszValue)
{
    if (m_pData)
    {
        GET_XML_ATTRIB_STR(_T("Name"), m_pData->m_strName, pszName, pszValue)
        GET_XML_ATTRIB_FLOAT(_T("x"), m_pData->m_fX, pszName, pszValue)
        GET_XML_ATTRIB_FLOAT(_T("y"), m_pData->m_fY, pszName, pszValue)
        GET_XML_ATTRIB_FLOAT(_T("angle"), m_pData->m_fAngle, pszName, pszValue)
    }
};