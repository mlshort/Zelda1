/**
 *  @file       XmlGameDataHandler.h
 *  @brief      TXmlDataHandler template class XML data mapper for the XML Parser
 *  @author     Mark L. Short
 *  @date       December 2, 2016
 *
 *  <b>Course:</b>     CPSC 5377 Advanced Game Programming
 *
 *  <b>Instructor:</b> Sean Orme
 *
 *  <b>Assignment:</b> Zelda1 Project
 *
 *  @sa https://www.viksoe.dk/code
 */
#pragma once

#if !defined(__XMLGAME_DATAHANDLER_H__)
#define __XMLGAME_DATAHANDLER_H__


#ifndef __XMLGAME_DATA_H__
    #include "XmlGameData.h"
#endif
#ifndef __XMLPARSER_H__
    #include "XmlParser.h"
#endif


/**
    @brief provides basic XML data-mapping functionality
*/
template<class _TData>
class TXmlDataHandler
    : public IXmlElementHandler
{
protected:
    CXmlParser*         m_pParser;
    _TData*             m_pData;
    std::vector<_TData> m_rgData;
public:
    /// default constructor
    constexpr TXmlDataHandler(void) noexcept
        : IXmlElementHandler(),
          m_pParser(nullptr),
          m_pData(nullptr),
          m_rgData()
    {};

    virtual ~TXmlDataHandler() noexcept
    {};


    void OnParseInit(CXmlParser* pParser) noexcept override
    { m_pParser = pParser; };

    virtual void OnAttribute  (const TCHAR* pszName, const TCHAR* pszValue) = 0;
    virtual void OnElementInit(const TCHAR* pszName) = 0;

    constexpr const std::vector<_TData>& GetData(void) const noexcept
    { return m_rgData; };
};


class CXmlLevelDataHandler
    : public TXmlDataHandler<LEVEL_DATA>
{
public:
    constexpr CXmlLevelDataHandler(void) noexcept
        : TXmlDataHandler()
    { };

    virtual ~CXmlLevelDataHandler() noexcept
    { };

    void OnAttribute  (const TCHAR* pszName, const TCHAR* pszValue) override;
    void OnElementInit(const TCHAR* pszName) override;
};

class CXmlObjectDataHandler
    : public TXmlDataHandler<OBJECT_DATA>
{
public:
    constexpr CXmlObjectDataHandler(void) noexcept
        : TXmlDataHandler()
    { };

    virtual ~CXmlObjectDataHandler() noexcept
    { };

    void OnAttribute  (const TCHAR* pszName, const TCHAR* pszValue) override;
    void OnElementInit(const TCHAR* pszName) override;
};
#endif