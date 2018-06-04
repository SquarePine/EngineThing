#ifndef SQUAREPINE_MEMORY_H
#define SQUAREPINE_MEMORY_H

//==============================================================================
/** Fills a block of memory with zeros. */
inline void zeromem (void* memory, size_t numBytes) noexcept
{
    memset (memory, 0, numBytes);
}

/** Overwrites a structure or object with zeros. */
template<typename Type>
inline void zerostruct (Type& structure) noexcept
{
    memset (&structure, 0, sizeof (structure));
}

/** Delete an object pointer, and sets the pointer to null.

    Remember that it's not good c++ practice to use delete directly - always try to use a std::unique_ptr
    or other automatic lifetime-management system rather than resorting to deleting raw pointers!
*/
template<typename Type>
inline void deleteAndZero (Type& pointer)
{
    delete pointer;
    pointer = nullptr;
}

/** A handy function which adds a number of bytes to any type of pointer and returns the result.
    This can be useful to avoid casting pointers to a char* and back when you want to move them by
    a specific number of bytes,
*/
template<typename Type, typename IntegerType>
inline Type* addBytesToPointer (Type* basePointer, IntegerType bytes) noexcept
{
    return (Type*) (((char*) basePointer) + bytes);
}

/** A handy function to round up a pointer to the nearest multiple of a given number of bytes.
    alignmentBytes must be a power of two.
*/
template<typename Type, typename IntegerType>
inline Type* snapPointerToAlignment (Type* basePointer, IntegerType alignmentBytes) noexcept
{
    return (Type*) ((((size_t) basePointer) + (alignmentBytes - 1)) & ~(alignmentBytes - 1));
}

/** A handy function which returns the difference between any two pointers, in bytes.
    The address of the second pointer is subtracted from the first, and the difference in bytes is returned.
*/
template<typename Type1, typename Type2>
inline int getAddressDifference (Type1* pointer1, Type2* pointer2) noexcept
{
    return (int) (((const char*) pointer1) - (const char*) pointer2);
}

/** If a pointer is non-null, this returns a new copy of the object that it points to, or safely returns
    nullptr if the pointer is null.
*/
template<class Type>
inline Type* createCopyIfNotNull (const Type* objectToCopy)
{
    return objectToCopy != nullptr ? new Type (*objectToCopy) : nullptr;
}

//==============================================================================
/** A handy function to read un-aligned memory without a performance penalty or bus-error. */
template<typename Type>
inline Type readUnaligned (const void* sourcePointer) noexcept
{
    Type value;
    memcpy (&value, sourcePointer, sizeof (Type));
    return value;
}

/** A handy function to write un-aligned memory without a performance penalty or bus-error. */
template<typename Type>
inline void writeUnaligned (void* destinationPointer, Type value) noexcept
{
    memcpy (destinationPointer, &value, sizeof (Type));
}

#endif //SQUAREPINE_MEMORY_H
