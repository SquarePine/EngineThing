#ifndef SQUAREPINE_MATHS_H
#define SQUAREPINE_MATHS_H

//==============================================================================
/** A platform-independent 8-bit signed integer type. */
typedef signed char                 int8;
/** A platform-independent 8-bit unsigned integer type. */
typedef unsigned char               uint8;
/** A platform-independent 16-bit signed integer type. */
typedef signed short                int16;
/** A platform-independent 16-bit unsigned integer type. */
typedef unsigned short              uint16;
/** A platform-independent 32-bit signed integer type. */
typedef signed int                  int32;
/** A platform-independent 32-bit unsigned integer type. */
typedef unsigned int                uint32;

#if SQUAREPINE_MSVC
    /** A platform-independent 64-bit integer type. */
    typedef __int64                   int64;
    /** A platform-independent 64-bit unsigned integer type. */
    typedef unsigned __int64          uint64;
#else
    /** A platform-independent 64-bit integer type. */
    typedef long long                 int64;
    /** A platform-independent 64-bit unsigned integer type. */
    typedef unsigned long long        uint64;
#endif

/** A macro for creating 64-bit literals.

    Historically, this was needed to support portability with MSVC6, and is kept here
    so that old code will still compile, but nowadays every compiler will support the
    LL and ULL suffixes, so you should use those in preference to this macro.
*/
#define literal64bit(longLiteral) (longLiteral##LL)

#if SQUAREPINE_64BIT
    /** A signed integer type that's guaranteed to be large enough to hold a pointer without truncating it. */
    typedef int64                     pointer_sized_int;
    /** An unsigned integer type that's guaranteed to be large enough to hold a pointer without truncating it. */
    typedef uint64                    pointer_sized_uint;
#elif SQUAREPINE_MSVC
    /** A signed integer type that's guaranteed to be large enough to hold a pointer without truncating it. */
    typedef _W64 int                  pointer_sized_int;
    /** An unsigned integer type that's guaranteed to be large enough to hold a pointer without truncating it. */
    typedef _W64 unsigned int         pointer_sized_uint;
#else
    /** A signed integer type that's guaranteed to be large enough to hold a pointer without truncating it. */
    typedef int                       pointer_sized_int;
    /** An unsigned integer type that's guaranteed to be large enough to hold a pointer without truncating it. */
    typedef unsigned int              pointer_sized_uint;
#endif

#if SQUAREPINE_WINDOWS && ! SQUAREPINE_MINGW
    typedef pointer_sized_int ssize_t;
#endif

//==============================================================================
/** Remaps a normalised value (between 0 and 1) to a target range.
    This effectively returns (targetRangeMin + value0To1 * (targetRangeMax - targetRangeMin)).
*/
template<typename Type>
Type jmap (Type value0To1, Type targetRangeMin, Type targetRangeMax)
{
    return targetRangeMin + value0To1 * (targetRangeMax - targetRangeMin);
}

/** Remaps a value from a source range to a target range. */
template<typename Type>
Type jmap (Type sourceValue, Type sourceRangeMin, Type sourceRangeMax, Type targetRangeMin, Type targetRangeMax)
{
    jassert (sourceRangeMax != sourceRangeMin); // mapping from a range of zero will produce NaN!
    return targetRangeMin + ((targetRangeMax - targetRangeMin) * (sourceValue - sourceRangeMin)) / (sourceRangeMax - sourceRangeMin);
}

/** Scans an array of values, returning the minimum value that it contains. */
template<typename Type>
Type findMinimum (const Type* data, int numValues)
{
    if (numValues <= 0)
        return Type (0);

    auto result = *data++;

    while (--numValues > 0) // (> 0 rather than >= 0 because we've already taken the first sample)
    {
        auto v = *data++;

        if (v < result)
            result = v;
    }

    return result;
}

/** Scans an array of values, returning the maximum value that it contains. */
template<typename Type>
Type findMaximum (const Type* values, int numValues)
{
    if (numValues <= 0)
        return Type (0);

    auto result = *values++;

    while (--numValues > 0) // (> 0 rather than >= 0 because we've already taken the first sample)
    {
        auto v = *values++;

        if (result < v)
            result = v;
    }

    return result;
}

/** Scans an array of values, returning the minimum and maximum values that it contains. */
template<typename Type>
void findMinAndMax (const Type* values, int numValues, Type& lowest, Type& highest)
{
    if (numValues <= 0)
    {
        lowest = Type (0);
        highest = Type (0);
    }
    else
    {
        auto mn = *values++;
        auto mx = mn;

        while (--numValues > 0) // (> 0 rather than >= 0 because we've already taken the first sample)
        {
            auto v = *values++;

            if (mx < v)  mx = v;
            if (v < mn)  mn = v;
        }

        lowest = mn;
        highest = mx;
    }
}

//==============================================================================
/** Constrains a value to keep it within a given range.

    This will check that the specified value lies between the lower and upper bounds
    specified, and if not, will return the nearest value that would be in-range. Effectively,
    it's like calling std::max (lowerLimit, std::min (upperLimit, value)).

    Note that it expects that lowerLimit <= upperLimit. If this isn't true,
    the results will be unpredictable.

    @param lowerLimit           the minimum value to return
    @param upperLimit           the maximum value to return
    @param valueToConstrain     the value to try to return
    @returns    the closest value to valueToConstrain which lies between lowerLimit
                and upperLimit (inclusive)
    @see std::min, std::max, jmap
*/
template<typename Type>
Type jlimit (Type lowerLimit,
             Type upperLimit,
             Type valueToConstrain) noexcept
{
    jassert (lowerLimit <= upperLimit); // if these are in the wrong order, results are unpredictable..

    return valueToConstrain < lowerLimit ? lowerLimit
                                         : (upperLimit < valueToConstrain ? upperLimit
                                                                          : valueToConstrain);
}

/** Returns true if a value is at least zero, and also below a specified upper limit.

    This is basically a quicker way to write:
    @code
        valueToTest >= 0 && valueToTest < upperLimit
    @endcode
*/
template<typename Type1, typename Type2>
bool isPositiveAndBelow (Type1 valueToTest, Type2 upperLimit) noexcept
{
    jassert (Type1() <= static_cast<Type1> (upperLimit)); // makes no sense to call this if the upper limit is itself below zero..
    return Type1() <= valueToTest && valueToTest < static_cast<Type1> (upperLimit);
}

template<typename Type>
bool isPositiveAndBelow (int valueToTest, Type upperLimit) noexcept
{
    jassert (upperLimit >= 0); // makes no sense to call this if the upper limit is itself below zero..
    return static_cast<unsigned int> (valueToTest) < static_cast<unsigned int> (upperLimit);
}

/** Returns true if a value is at least zero, and also less than or equal to a specified upper limit.

    This is basically a quicker way to write:
    @code
        valueToTest >= 0 && valueToTest <= upperLimit
    @endcode
*/
template<typename Type1, typename Type2>
bool isPositiveAndNotGreaterThan (Type1 valueToTest, Type2 upperLimit) noexcept
{
    jassert (Type1() <= static_cast<Type1> (upperLimit)); // makes no sense to call this if the upper limit is itself below zero..
    return Type1() <= valueToTest && valueToTest <= static_cast<Type1> (upperLimit);
}

template<typename Type>
bool isPositiveAndNotGreaterThan (int valueToTest, Type upperLimit) noexcept
{
    jassert (upperLimit >= 0); // makes no sense to call this if the upper limit is itself below zero..
    return static_cast<unsigned int> (valueToTest) <= static_cast<unsigned int> (upperLimit);
}

//==============================================================================
/** Handy function for getting the number of elements in a simple const C array.
    E.g.
    @code
    static int myArray[] = { 1, 2, 3 };
    int numElements = numElementsInArray (myArray) // returns 3
    @endcode
*/
template<typename Type, int N>
int numElementsInArray (Type (&array)[N])
{
    (void) array;
    (void) sizeof (0[array]); // This line should cause an error if you pass an object with a user-defined subscript operator
    return N;
}

//==============================================================================
// Some useful maths functions that aren't always present with all compilers and build settings.

/** Using juce_hypot is easier than dealing with the different types of hypot function
    that are provided by the various platforms and compilers. */
template<typename Type>
Type juce_hypot (Type a, Type b) noexcept
{
   #if SQUAREPINE_MSVC
    return static_cast<Type> (_hypot (a, b));
   #else
    return static_cast<Type> (hypot (a, b));
   #endif
}

#ifndef DOXYGEN
template<>
inline float juce_hypot (float a, float b) noexcept
{
   #if SQUAREPINE_MSVC
    return _hypotf (a, b);
   #else
    return hypotf (a, b);
   #endif
}
#endif

#if SQUAREPINE_MSVC && ! defined (DOXYGEN)  // The MSVC libraries omit these functions for some reason...
    template<typename Type> Type asinh (Type x)  { return std::log (x + std::sqrt (x * x + (Type) 1)); }
    template<typename Type> Type acosh (Type x)  { return std::log (x + std::sqrt (x * x - (Type) 1)); }
    template<typename Type> Type atanh (Type x)  { return (std::log (x + (Type) 1) - std::log (((Type) 1) - x)) / (Type) 2; }
#endif

//==============================================================================
/** Commonly used mathematical constants
*/
template<typename FloatType>
struct MathConstants
{
    /** A predefined value for Pi */
    static const FloatType pi;

    /** A predefined value for 2 * Pi */
    static const FloatType twoPi;

    /** A predefined value for Pi / 2 */
    static const FloatType halfPi;

    /** A predefined value for Euler's number */
    static const FloatType euler;

    /** A predefined value for sqrt(2) */
    static const FloatType sqrt2;
};

template<typename FloatType>
const FloatType MathConstants<FloatType>::pi = static_cast<FloatType> (3.141592653589793238L);

template<typename FloatType>
const FloatType MathConstants<FloatType>::twoPi = static_cast<FloatType> (2 * 3.141592653589793238L);

template<typename FloatType>
const FloatType MathConstants<FloatType>::halfPi = static_cast<FloatType> (3.141592653589793238L / 2);

template<typename FloatType>
const FloatType MathConstants<FloatType>::euler = static_cast<FloatType> (2.71828182845904523536L);

template<typename FloatType>
const FloatType MathConstants<FloatType>::sqrt2 = static_cast<FloatType> (1.4142135623730950488L);

#ifndef DOXYGEN
/** A double-precision constant for pi.
    @deprecated This is deprecated in favour of MathConstants<double>::pi.
    The reason is that "double_Pi" was a confusing name, and many people misused it,
    wrongly thinking it meant 2 * pi !
*/
const double double_Pi  = MathConstants<double>::pi;

/** A single-precision constant for pi.
    @deprecated This is deprecated in favour of MathConstants<float>::pi.
    The reason is that "double_Pi" was a confusing name, and many people misused it,
    wrongly thinking it meant 2 * pi !
*/
const float float_Pi   = MathConstants<float>::pi;
#endif

/** Converts an angle in degrees to radians. */
template<typename FloatType>
FloatType degreesToRadians (FloatType degrees) noexcept     { return degrees * (MathConstants<FloatType>::pi / FloatType (180)); }

/** Converts an angle in radians to degrees. */
template<typename FloatType>
FloatType radiansToDegrees (FloatType radians) noexcept     { return radians * (FloatType (180) / MathConstants<FloatType>::pi); }

//==============================================================================
/** The isfinite() method seems to vary between platforms, so this is a
    platform-independent function for it.
*/
template<typename NumericType>
bool juce_isfinite (NumericType) noexcept
{
    return true; // Integer types are always finite
}

template<>
inline bool juce_isfinite (float value) noexcept
{
   #if SQUAREPINE_WINDOWS && ! SQUAREPINE_MINGW
    return _finite (value) != 0;
   #else
    return std::isfinite (value);
   #endif
}

template<>
inline bool juce_isfinite (double value) noexcept
{
   #if SQUAREPINE_WINDOWS && ! SQUAREPINE_MINGW
    return _finite (value) != 0;
   #else
    return std::isfinite (value);
   #endif
}

//==============================================================================
#if SQUAREPINE_MSVC
 #pragma optimize ("t", off)
 #ifndef __INTEL_COMPILER
  #pragma float_control (precise, on, push)
 #endif
#endif

/** Fast floating-point-to-integer conversion.
    This is faster than using the normal c++ cast to convert a float to an int, and
    it will round the value to the nearest integer, rather than rounding it down
    like the normal cast does.
    Note that this routine gets its speed at the expense of some accuracy, and when
    rounding values whose floating point component is exactly 0.5, odd numbers and
    even numbers will be rounded up or down differently.
*/
template<typename FloatType>
int roundToInt (const FloatType value) noexcept
{
  #ifdef __INTEL_COMPILER
   #pragma float_control (precise, on, push)
  #endif

    union { int asInt[2]; double asDouble; } n;
    n.asDouble = ((double) value) + 6755399441055744.0;

   #if SQUAREPINE_BIG_ENDIAN
    return n.asInt [1];
   #else
    return n.asInt [0];
   #endif
}

inline int roundToInt (int value) noexcept
{
    return value;
}

#if SQUAREPINE_MSVC
 #ifndef __INTEL_COMPILER
  #pragma float_control (pop)
 #endif
 #pragma optimize ("", on)  // resets optimisations to the project defaults
#endif

/** Fast floating-point-to-integer conversion.
    This is a slightly slower and slightly more accurate version of roundToInt(). It works
    fine for values above zero, but negative numbers are rounded the wrong way.
*/
inline int roundToIntAccurate (double value) noexcept
{
   #ifdef __INTEL_COMPILER
    #pragma float_control (pop)
   #endif

    return roundToInt (value + 1.5e-8);
}

//==============================================================================
/** Truncates a positive floating-point number to an unsigned int.
    This is generally faster than static_cast<unsigned int> (std::floor (x))
    but it only works for positive numbers small enough to be represented as an
    unsigned int.
*/
template<typename FloatType>
unsigned int truncatePositiveToUnsignedInt (FloatType value) noexcept
{
    jassert (value >= static_cast<FloatType> (0));
    jassert (static_cast<FloatType> (value) <= std::numeric_limits<unsigned int>::max());

    return static_cast<unsigned int> (value);
}

//==============================================================================
/** Returns true if the specified integer is a power-of-two. */
template<typename IntegerType>
bool isPowerOfTwo (IntegerType value)
{
   return (value & (value - 1)) == 0;
}

/** Returns the smallest power-of-two which is equal to or greater than the given integer. */
inline int nextPowerOfTwo (int n) noexcept
{
    --n;
    n |= (n >> 1);
    n |= (n >> 2);
    n |= (n >> 4);
    n |= (n >> 8);
    n |= (n >> 16);
    return n + 1;
}

/** Returns the index of the highest set bit in a (non-zero) number.
    So for n=3 this would return 1, for n=7 it returns 2, etc.
    An input value of 0 is illegal!
*/
int findHighestSetBit (uint32 n) noexcept;

/** Returns the number of bits in a 32-bit integer. */
inline int countNumberOfBits (uint32 n) noexcept
{
    n -= ((n >> 1) & 0x55555555);
    n =  (((n >> 2) & 0x33333333) + (n & 0x33333333));
    n =  (((n >> 4) + n) & 0x0f0f0f0f);
    n += (n >> 8);
    n += (n >> 16);
    return (int) (n & 0x3f);
}

/** Returns the number of bits in a 64-bit integer. */
inline int countNumberOfBits (uint64 n) noexcept
{
    return countNumberOfBits ((uint32) n) + countNumberOfBits ((uint32) (n >> 32));
}

/** Performs a modulo operation, but can cope with the dividend being negative.
    The divisor must be greater than zero.
*/
template<typename IntegerType>
IntegerType negativeAwareModulo (IntegerType dividend, const IntegerType divisor) noexcept
{
    jassert (divisor > 0);
    dividend %= divisor;
    return (dividend < 0) ? (dividend + divisor) : dividend;
}

/** Returns the square of its argument. */
template<typename NumericType>
inline NumericType square (NumericType n) noexcept
{
    return n * n;
}

//==============================================================================
#if SQUAREPINE_INTEL || defined (DOXYGEN)
 /** This macro can be applied to a float variable to check whether it contains a denormalised
     value, and to normalise it if necessary.
     On CPUs that aren't vulnerable to denormalisation problems, this will have no effect.
 */
 #define SQUAREPINE_UNDENORMALISE(x)   { (x) += 0.1f; (x) -= 0.1f; }
#else
 #define SQUAREPINE_UNDENORMALISE(x)
#endif

//==============================================================================
/** This namespace contains a few template classes for helping work out class type variations.
*/
namespace TypeHelpers
{
    /** The ParameterType struct is used to find the best type to use when passing some kind
        of object as a parameter.

        Of course, this is only likely to be useful in certain esoteric template situations.
        E.g. "myFunction (typename TypeHelpers::ParameterType<int>::type, typename TypeHelpers::ParameterType<MyObject>::type)"
        would evaluate to "myfunction (int, const MyObject&)", keeping any primitive types as
        pass-by-value, but passing objects as a const reference, to avoid copying.
    */
    template<typename SourceType> struct ParameterType              { typedef const SourceType& Type; };

   #if ! DOXYGEN
    template<typename SourceType> struct ParameterType<SourceType&> { typedef SourceType& Type; };
    template<typename SourceType> struct ParameterType<SourceType*> { typedef SourceType* Type; };
    template<> struct ParameterType<char>                           { typedef char Type; };
    template<> struct ParameterType<unsigned char>                  { typedef unsigned char Type; };
    template<> struct ParameterType<short>                          { typedef short Type; };
    template<> struct ParameterType<unsigned short>                 { typedef unsigned short Type; };
    template<> struct ParameterType<int>                            { typedef int type; };
    template<> struct ParameterType<unsigned int>                   { typedef unsigned int Type; };
    template<> struct ParameterType<long>                           { typedef long type; };
    template<> struct ParameterType<unsigned long>                  { typedef unsigned long Type; };
    template<> struct ParameterType<int64>                          { typedef int64 Type; };
    template<> struct ParameterType<uint64>                         { typedef uint64 Type; };
    template<> struct ParameterType<bool>                           { typedef bool Type; };
    template<> struct ParameterType<float>                          { typedef float Type; };
    template<> struct ParameterType<double>                         { typedef double Type; };
   #endif

    /** These templates are designed to take a type, and if it's a double, they return a double
        type; for anything else, they return a float type.
    */
    template<typename SourceType> struct SmallestFloatType          { typedef float Type; };

   #if ! DOXYGEN
    template<> struct SmallestFloatType<double>                     { typedef double Type; };
   #endif

    /** These templates are designed to take an integer type, and return an unsigned int
        version with the same size.
    */
    template<int bytes> struct UnsignedTypeWithSize                 {};

   #if ! DOXYGEN
    template<> struct UnsignedTypeWithSize<1>                       { typedef uint8  Type; };
    template<> struct UnsignedTypeWithSize<2>                       { typedef uint16 Type; };
    template<> struct UnsignedTypeWithSize<4>                       { typedef uint32 Type; };
    template<> struct UnsignedTypeWithSize<8>                       { typedef uint64 Type; };
   #endif
}
#endif //SQUAREPINE_MATHS_H
