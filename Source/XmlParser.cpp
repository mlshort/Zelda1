/**
 *  @file       XmlParser.cpp
 *  @brief      CXmlParser class implementation
 *  @author     Mark L. Short
 *  @date       December 3, 2016
 *
 *  <b>Course:</b>     CPSC 5377 Advanced Game Programming
 *
 *  <b>Instructor:</b> Sean Orme
 *
 *  <b>Assignment:</b> Zelda1 Project
 *
 *  <b>Cite:</b>
 *              fixed & enhanced sample by Bjarke Viksoe
 *  @sa https://www.viksoe.dk/code
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

 // include the Microsoft XmlLite library
#include <xmllite.h>
#pragma comment(lib, "xmllite.lib")

#include "Utility\DebugUtils.h"
#include "XmlParser.h"


#ifndef _ASSERTE
    #define _ASSERTE(x)
#endif


CXmlParser::~CXmlParser()
{
    Destroy();
}


bool CXmlParser::Create(void)
{
    if (m_pIXmlReader != nullptr)
    {
        m_pIXmlReader->Release();
        m_pIXmlReader = nullptr;
    }

    ::CreateXmlReader(__uuidof( IXmlReader ), reinterpret_cast<LPVOID*>( &m_pIXmlReader ), nullptr);
    _ASSERTE(m_pIXmlReader);
    return m_pIXmlReader != nullptr;
}

void CXmlParser::Destroy() noexcept
{
    if (m_pIXmlReader != nullptr)
        m_pIXmlReader->Release();
    m_pIXmlReader = nullptr;
}

void CXmlParser::SetHandler(IXmlElementHandler * pHandler)
{
    _ASSERTE(m_pIXmlReader);
    m_pHandler = pHandler;
    if (pHandler)
       pHandler->OnParseInit(this);
}


bool CXmlParser::Parse( IStream* pInputStream )
{
    _ASSERTE( m_pIXmlReader );

    HRESULT hr = m_pIXmlReader->SetInput( pInputStream );

    LPCWSTR pszName  = nullptr;
    LPCWSTR pszValue = nullptr;


    XmlNodeType NodeType = XmlNodeType_None;
    while ( m_pIXmlReader->Read( &NodeType ) == S_OK )
    {
        switch ( NodeType )
        {
            case XmlNodeType_Element:
            {
                if ( m_pHandler != nullptr )
                {
                    if ( FAILED( hr = m_pIXmlReader->GetLocalName( &pszName, nullptr ) ) )
                    {
                        util::DebugTrace( _T( "XmlElement Error getting local name: %08.8lx \n" ), hr );
                        return false;
                    }


#ifdef _DEBUG
                    util::DebugTrace( _T( "< %s \n" ), pszName );
#endif
                    m_pHandler->OnElementInit( pszName );


                    hr = m_pIXmlReader->MoveToFirstAttribute();

                    while ( hr == S_OK )
                    {
                        if ( !m_pIXmlReader->IsDefault() )
                        {
                            LPCWSTR pszAttribName  = nullptr;
                            LPCWSTR pszAttribValue = nullptr;

                            if ( FAILED( hr = m_pIXmlReader->GetLocalName( &pszAttribName, nullptr ) ) )
                            {
                                util::DebugTrace( _T( "XmlAttribute Error getting local name: %08.8lx \n" ), hr );
                                return false;
                            }

                            if ( FAILED( hr = m_pIXmlReader->GetValue( &pszAttribValue, nullptr ) ) )
                            {
                                util::DebugTrace( _T( "XmlAttribute Error getting value: %08.8lx \n" ), hr );
                                return false;
                            }

#ifdef _DEBUG
                            util::DebugTrace( _T( "   XmlAttribute '%s' = '%s' \n" ), pszAttribName, pszAttribValue );
#endif
                            m_pHandler->OnAttribute( pszAttribName, pszAttribValue );
                        }
                        hr = m_pIXmlReader->MoveToNextAttribute();
                    }
                }
            }
            break;

            case XmlNodeType_Whitespace:
#ifdef _DEBUG
                util::DebugTrace( _T( "XmlWhitespace \n" ) );
#endif
                break;

            case XmlNodeType_EndElement:
#ifdef _DEBUG
                util::DebugTrace( _T( "XmlEndElement \n" ) );
#endif
                break;

            case XmlNodeType_Text:
#ifdef _DEBUG
                util::DebugTrace( _T( "XmlText \n" ) );
#endif
                break;

            case XmlNodeType_None:
#ifdef _DEBUG
                util::DebugTrace( _T( "XmlNone \n" ) );
#endif
                break;

            case XmlNodeType_Attribute:
#ifdef _DEBUG
                util::DebugTrace( _T( "XmlAttribute \n" ) );
#endif
                break;

            case XmlNodeType_CDATA:
                if ( FAILED( hr = m_pIXmlReader->GetValue( &pszValue, nullptr ) ) )
                {
                    util::DebugTrace( _T( "XmlCDATA Error getting value: %08.8lx \n" ), hr );
                    return false;
                }
#ifdef _DEBUG
                util::DebugTrace( _T( "XmlCDATA: %s\n" ), pszValue );
#endif
                break;

            case XmlNodeType_ProcessingInstruction:
                if ( FAILED( hr = m_pIXmlReader->GetLocalName( &pszName, nullptr ) ) )
                {
                    util::DebugTrace( _T( "Error getting name: %08.8lx \n" ), hr );
                    return false;
                }
                if ( FAILED( hr = m_pIXmlReader->GetValue( &pszValue, nullptr ) ) )
                {
                    util::DebugTrace( _T( "Error getting value: %08.8lx \n" ), hr );
                    return false;
                }
#ifdef _DEBUG
                util::DebugTrace( _T( "XmlProcessingInstruction Name:%s Value:%s \n" ), pszName, pszValue );
#endif
                break;

            case XmlNodeType_Comment:
                if ( FAILED( hr = m_pIXmlReader->GetValue( &pszValue, nullptr ) ) )
                {
                    util::DebugTrace( _T( "XmlComment Error getting value: %08.8lx \n" ), hr );
                    return false;
                }
#ifdef _DEBUG
                util::DebugTrace( _T( "<!--%s--> \n" ), pszValue );
#endif
                break;

            case XmlNodeType_DocumentType:
#ifdef _DEBUG
                util::DebugTrace( _T( "XmlDOCTYPE is not printed \n" ) );
#endif
                break;

            case XmlNodeType_XmlDeclaration:
#ifdef _DEBUG
                util::DebugTrace( _T( "XmlDeclaration \n" ) );
#endif
                break;

            default:
#ifdef _DEBUG
                util::DebugTrace( _T( "Unknown Xml Node Type \n" ) );
#endif
                break;

        }
    }

    return true;
}

