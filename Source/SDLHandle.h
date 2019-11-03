/**
 *  @file       SDLHandle.h
 *  @brief      TSDLHandle_Base template class definition
 *  @author     Mark L. Short
 *  @date       March 12, 2017
 *
 * <b>Course:</b>     CPSC 5377 Advanced Game Programming
 *
 * <b>Instructor:</b> Sean Orme
 *
 * <b>Assignment:</b> Zelda1 Project
 *
 */
#pragma once

#if !defined(__SDL_HANDLE_H__)
#define __SDL_HANDLE_H__

#ifndef _TYPE_TRAITS_
    #include <type_traits>
#endif

/**
 *  @brief An SDL Context manager template class
 *
 *  Implemented using the Curiously Recurring Template Pattern (CRTP)
 *
 *  @sa https://en.wikipedia.org/wiki/Curiously_recurring_template_pattern
 */
template<class _T, class Derived>
struct __declspec(novtable) TSDLHandle_Base
{
    typedef typename _T* SDL_HANDLE;

    SDL_HANDLE  m_hSDL;
    bool        m_bDestroyOnDelete;

    /// Default Constructor
    constexpr TSDLHandle_Base(void) noexcept
        : m_hSDL(),
          m_bDestroyOnDelete(true)
    { };

    /// Conversion Constructor
    constexpr explicit TSDLHandle_Base(SDL_HANDLE handle, bool bDestroy = true) noexcept
        : m_hSDL(handle),
          m_bDestroyOnDelete(bDestroy)
    { };

    /// Copy Constructor
    constexpr TSDLHandle_Base(const TSDLHandle_Base& othr) noexcept
        : m_hSDL(othr.m_hSDL),
          m_bDestroyOnDelete(othr.m_bDestroyOnDelete)
    { };

    /// Move Constructor
    TSDLHandle_Base(TSDLHandle_Base&& othr) noexcept
        : m_hSDL(std::move(othr.m_hSDL)),
          m_bDestroyOnDelete(othr.m_bDestroyOnDelete)
    {   // take explicit ownership by clearing other object's handle
        othr.m_hSDL = SDL_HANDLE();
    };

    /// Takes Ownership, by default
    void Attach(SDL_HANDLE hSDL, bool bDestroy = true) noexcept
    {
        m_hSDL             = hSDL;
        m_bDestroyOnDelete = bDestroy;
    };

    /// Relinquishes Ownership
    SDL_HANDLE Detach(void) noexcept
    {
        auto h   = m_hSDL;
        m_hSDL   = SDL_HANDLE();
        return h;
    };

    SDL_HANDLE get_Handle(void) noexcept
    {
        return m_hSDL;
    };

    operator SDL_HANDLE() noexcept
    {
        return m_hSDL;
    };

    /// Assignment operator
    TSDLHandle_Base& operator=(const TSDLHandle_Base& rhs) noexcept
    {
        if (this != &rhs)
        {
            m_hSDL             = rhs.m_hSDL;
            m_bDestroyOnDelete = rhs.m_bDestroyOnDelete;
        }
        return *this;
    };

    /// Move assignment operator
    TSDLHandle_Base& operator=(TSDLHandle_Base&& rhs) noexcept
    {
        if (this != &rhs)
        {
            m_hSDL             = std::move(rhs.m_hSDL);
            m_bDestroyOnDelete = rhs.m_bDestroyOnDelete;
            // take ownership by clearing the rhs handle
            rhs.m_hSDL         = SDL_HANDLE();
        }

        return *this;
    }

    void Destroy(void) noexcept
    {
        static_cast< Derived* >(this)->Destroy();
    }

    ~TSDLHandle_Base(void)
    {
        if (m_bDestroyOnDelete)
            Destroy();
    };
};

#endif
