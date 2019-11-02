/**
 *  @file       ObjectFactory.h
 *  @brief      TFactory_Base, TSharedFactory, TUniqueFactory, template class definition(s)
 *  @author     Mark L. Short
 *  @date       March 12, 2017
 *
 * <b>Course:</b>     CPSC 5377 Advanced Game Programming
 *
 * <b>Instructor:</b> Sean Orme
 *
 * <b>Assignment:</b> Zelda1 Project
 *
 *   Each of the derived classes should be instantiated using an appropriate
 *   Factory class derived from a ObjectFactory class with respective overloaded
 *   unique_ptr<Object> create() methods (see class notes, example, and solution
 *   key to Homework 0). See the GameAssetLibrary class for how these factories
 *   will be used.
 *
 * <b>Implementation Details:</b>
 */
#pragma once

#if !defined(__OBJECT_FACTORY_H__)
#define __OBJECT_FACTORY_H__

#ifndef _MEMORY_
    #include <memory>
#endif

/**
 *  @brief Base template class for other template-based factory specializations
 *
 *  Implemented using the Curiously Recurring Template Pattern (CRTP)
 *
 *  @sa https://en.wikipedia.org/wiki/Curiously_recurring_template_pattern
 */
template <class _Derived>
struct __declspec(novtable) TFactory_Base
{
    constexpr TFactory_Base() noexcept = default;

// following induces compile-time polymorphic behavior
// without the overhead of a "dynamic_cast"
    inline auto Create(void)
    { return static_cast<_Derived*>(this)->Create(); };
};

template <class _Ty>
class TSharedFactory
    : public TFactory_Base< TSharedFactory<_Ty> >
{
public:
    typedef typename std::shared_ptr<_Ty> smart_ptr;

    constexpr TSharedFactory(void) noexcept
        : TFactory_Base()
    { };

    inline auto Create(void)
    { return std::make_shared<_Ty>(); };

    inline auto Create(const _Ty& data)
    { return std::make_shared<_Ty>(data); };

};

template <class _Ty>
class TUniqueFactory
    : public TFactory_Base< TUniqueFactory<_Ty> >
{
public:
    typedef typename std::unique_ptr<_Ty> smart_ptr;

    constexpr TUniqueFactory(void) noexcept
        : TFactory_Base()
    { };

    inline auto Create(void)
    { return std::make_unique<_Ty>(); };

    inline auto Create(const _Ty& data)
    { return std::make_unique<_Ty>(data); };

    template<class _TDerived>
    inline auto Create(void)
    { static_assert(std::is_base_of<_Ty, _TDerived>::value, "Unrelated types");
      return std::make_unique<_TDerived>(); };

};

#endif

