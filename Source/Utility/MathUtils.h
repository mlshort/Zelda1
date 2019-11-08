/**
 *  @file       MathUtils.h
 *  @brief      Math utility method declarations
 *
 *  @author     Mark L. Short
 *  @date       September 8, 2015
 *
 *
 */

#pragma once

#if !defined(__MATH_UTILS_H__)
#define __MATH_UTILS_H__

#ifndef _CSTDLIB_
    #include <cstdlib>
#endif

#ifndef _CMATH_
    #include <cmath>
#endif

#ifndef _ALGORITHM_
    #include <algorithm>
#endif


namespace math
{

// 1 Radian = (180 / PI ) degrees

constexpr const double PI                 = static_cast<double>(3.1415926535897932384626433832795);
constexpr const double TWO_PI             = static_cast<double>(2.0 * math::PI);
constexpr const double DEGREES_PER_RADIAN = static_cast<double>(180.0 / math::PI); // effectively the same as ( 360 / 2 PI )
constexpr const double RADIANS_PER_DEGREE = static_cast<double>(math::PI / 180.0);
constexpr const double RADIANS_PER_CIRCLE = static_cast<double>(360.0 / math::DEGREES_PER_RADIAN);  // 2 PI

template <class _Ty>
constexpr _Ty Delta(const _Ty& x1, const _Ty& x2) noexcept
{
    return (x1 - x2);
};


template <class _Ty>
constexpr _Ty CalcDistanceSquared(const _Ty& xPt1, const _Ty& yPt1, const _Ty& xPt2, const _Ty& yPt2) noexcept
{
//    auto xDelta = xPt1 - xPt2;
//    auto yDelta = yPt1 - yPt2;
//    return (xDelta * xDelta) + (yDelta * yDelta);
    return ((math::Delta(xPt1, xPt2) * math::Delta(xPt1, xPt2)) +
            (math::Delta(yPt1, yPt2) * math::Delta(yPt1, yPt2)));
};

template <class _Ty>
inline _Ty CalcDistance(const _Ty& xPt1, const _Ty& yPt1, const _Ty& xPt2, const _Ty& yPt2) noexcept
{
    return static_cast<_Ty>(std::sqrt(math::CalcDistanceSquared(xPt1, yPt1, xPt2, yPt2)));
};

template <class _Ty>
constexpr _Ty RadiansToDegrees(const _Ty& fRadians) noexcept
{
    return static_cast<_Ty>(fRadians * math::DEGREES_PER_RADIAN);
};

template <class _Ty>
constexpr _Ty DegreesToRadians(const _Ty& fDegrees) noexcept
{
    return static_cast<_Ty>(fDegrees * math::RADIANS_PER_DEGREE);
};

template <class _Ty>
inline _Ty RangedRand( const _Ty& fRangeMin, const _Ty& fRangeMax ) noexcept
{
   // Generate random numbers in the half-closed interval
   // [fRangeMin, fRangeMax). In other words,
   // fRangeMin <= random number < fRangeMax

   return static_cast<_Ty>(static_cast<double>(std::rand()) / static_cast<_Ty>(RAND_MAX + 1) * (fRangeMax - fRangeMin)
            + fRangeMin);
};


template <class _Ty>
constexpr _Ty Clamp( const _Ty& fValue, const _Ty& fMin, const _Ty& fMax )
{
    return std::max(fMin, std::min(fMax, fValue));
};

template <class _Ty>
inline _Ty CalcXComponent(const _Ty& fDegrees) noexcept
{
    return std::cos(DegreesToRadians(fDegrees));
};

template <class _Ty>
inline _Ty CalcYComponent(const _Ty& fDegrees) noexcept
{
    return std::sin(DegreesToRadians(fDegrees));
};

/**
  @retval _Ty containing the angle (in Radians) from Origin to Target
 */
template <class _Ty>
inline _Ty CalcAngleToTarget(const _Ty& fOrigX, const _Ty& fOrigY, const _Ty& fTargetX, const _Ty& fTargetY) noexcept
{
    auto fDeltaX = fOrigX - fTargetX;
    auto fDeltaY = fOrigY - fTargetY;

    return std::atan2( fDeltaY, fDeltaX );
};

template<class _Ty>
inline bool fEqual(const _Ty& x, const _Ty& y, int iEpsilonFactor) noexcept
{
    if (x == y)
    {
        return true;
    }
    else
    {
        _Ty nDelta = std::abs(x - y);
        _Ty nTolerance = iEpsilonFactor * std::numeric_limits<_Ty>::epsilon();
        return (nDelta <= nTolerance);
    }
};

/*
  @todo implement a 'RangeMap' like method

  i.e. [3 to 18] -> [0.5 to 2.5]
  1. Input Range Start, Input Range End : Subtract Input Start, [0 to 15]
  2. Divide by Input Range End, [0 to 1.0]
float RangeMap(float fValue, float fInputMin, float fInputMax, float fOutMin, float fOutMax);
*/

}

#endif