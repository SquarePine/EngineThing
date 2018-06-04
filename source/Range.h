#ifndef SQUAREPINE_RANGE_H
#define SQUAREPINE_RANGE_H

#undef _ALLOW_KEYWORD_MACROS
#define _ALLOW_KEYWORD_MACROS 1

/** A general-purpose range object, that simply represents any linear range with a start and end point.

    Note that when checking whether values fall within the range,
    the start value is considered to be inclusive,
    and the end of the range exclusive.

    The templated parameter is expected to be a primitive integer or floating point type,
    though class types could also be used if they behave in a number-like way.
*/
template<typename ValueType>
class Range final
{
public:
    //==============================================================================
    /** Constructs an empty range. */
    Range() noexcept :
        start(),
        end()
    {
    }

    /** Constructs a range with given start and end values. */
    Range (ValueType startValue, ValueType endValue) noexcept :
        start (startValue),
        end (std::max (startValue, endValue))
    {
    }

    /** Constructs a copy of another range. */
    Range (const Range& other) noexcept :
        start (other.start),
        end (other.end)
    {
    }

    /** Copies another range object. */
    Range& operator= (Range other) noexcept
    {
        start = other.start;
        end = other.end;
        return *this;
    }

    /** Returns the range that lies between two positions (in either order). */
    static Range between (ValueType position1, ValueType position2) noexcept
    {
        return position1 < position2
                ? Range (position1, position2)
                : Range (position2, position1);
    }

    /** Returns a range with a given start and length. */
    static Range withStartAndLength (ValueType startValue, ValueType length) noexcept
    {
        jassert (length >= ValueType());
        return Range (startValue, startValue + length);
    }

    /** Returns a range with the specified start position and a length of zero. */
    static Range emptyRange (ValueType start) noexcept
    {
        return Range (start, start);
    }

    //==============================================================================
    /** Returns the start of the range. */
    inline ValueType getStart() const noexcept  { return start; }

    /** Returns the length of the range. */
    inline ValueType getLength() const noexcept { return end - start; }

    /** Returns the end of the range. */
    inline ValueType getEnd() const noexcept    { return end; }

    /** Returns true if the range has a length of zero. */
    inline bool isEmpty() const noexcept        { return start == end; }

    //==============================================================================
    /** Changes the start position of the range, leaving the end position unchanged.
        If the new start position is higher than the current end of the range, the end point
        will be pushed along to equal it, leaving an empty range at the new position.
    */
    void setStart (ValueType newStart) noexcept
    {
        start = newStart;
        if (end < newStart)
            end = newStart;
    }

    /** Returns a range with the same end as this one, but a different start.

        If the new start position is higher than the current end of the range, the end point
        will be pushed along to equal it, returning an empty range at the new position.
    */
    Range withStart (ValueType newStart) const noexcept
    {
        return Range (newStart, std::max (newStart, end));
    }

    /** Returns a range with the same length as this one, but moved to have the given start position. */
    Range movedToStartAt (ValueType newStart) const noexcept
    {
        return Range (newStart, end + (newStart - start));
    }

    /** Changes the end position of the range, leaving the start unchanged.

        If the new end position is below the current start of the range, the start point
        will be pushed back to equal the new end point.
    */
    void setEnd (ValueType newEnd) noexcept
    {
        end = newEnd;
        if (newEnd < start)
            start = newEnd;
    }

    /** Returns a range with the same start position as this one, but a different end.

        If the new end position is below the current start of the range, the start point
        will be pushed back to equal the new end point.
    */
    Range withEnd (ValueType newEnd) const noexcept
    {
        return Range (std::min (start, newEnd), newEnd);
    }

    /** Returns a range with the same length as this one, but moved to have the given end position. */
    Range movedToEndAt (ValueType newEnd) const noexcept
    {
        return Range (start + (newEnd - end), newEnd);
    }

    /** Changes the length of the range.
        Lengths less than zero are treated as zero.
    */
    void setLength (ValueType newLength) noexcept
    {
        end = start + std::max (ValueType(), newLength);
    }

    /** Returns a range with the same start as this one, but a different length.
        Lengths less than zero are treated as zero.
    */
    Range withLength (ValueType newLength) const noexcept
    {
        return Range (start, start + newLength);
    }

    /** Returns a range which has its start moved down and its end moved up by the
        given amount.
        @returns The returned range will be (start - amount, end + amount)
    */
    Range expanded (ValueType amount) const noexcept
    {
        return Range (start - amount, end + amount);
    }

    //==============================================================================
    /** Adds an amount to the start and end of the range. */
    inline Range operator+= (ValueType amountToAdd) noexcept
    {
        start += amountToAdd;
        end += amountToAdd;
        return *this;
    }

    /** Subtracts an amount from the start and end of the range. */
    inline Range operator-= (ValueType amountToSubtract) noexcept
    {
        start -= amountToSubtract;
        end -= amountToSubtract;
        return *this;
    }

    /** Returns a range that is equal to this one with an amount added to its
        start and end.
    */
    Range operator+ (ValueType amountToAdd) const noexcept
    {
        return Range (start + amountToAdd, end + amountToAdd);
    }

    /** Returns a range that is equal to this one with the specified amount
        subtracted from its start and end. */
    Range operator- (ValueType amountToSubtract) const noexcept
    {
        return Range (start - amountToSubtract, end - amountToSubtract);
    }

    bool operator== (Range other) const noexcept { return start == other.start && end == other.end; }
    bool operator!= (Range other) const noexcept { return start != other.start || end != other.end; }

    //==============================================================================
    /** Returns true if the given position lies inside this range.

        When making this comparison, the start value is considered to be inclusive,
        and the end of the range exclusive.
    */
    bool contains (ValueType position) const noexcept
    {
        return start <= position && position < end;
    }

    /** Returns the nearest value to the one supplied, which lies within the range. */
    ValueType clipValue (ValueType value) const noexcept
    {
        return jlimit (start, end, value);
    }

    /** Returns true if the given range lies entirely inside this range. */
    bool contains (Range other) const noexcept
    {
        return start <= other.start && end >= other.end;
    }

    /** Returns true if the given range intersects this one. */
    bool intersects (Range other) const noexcept
    {
        return other.start < end && start < other.end;
    }

    /** Returns the range that is the intersection of the two ranges, or an empty range
        with an undefined start position if they don't overlap. */
    Range getIntersectionWith (Range other) const noexcept
    {
        return Range (std::max (start, other.start),
                      std::min (end, other.end));
    }

    /** Returns the smallest range that contains both this one and the other one. */
    Range getUnionWith (Range other) const noexcept
    {
        return Range (std::min (start, other.start),
                      std::max (end, other.end));
    }

    /** Returns the smallest range that contains both this one and the given value. */
    Range getUnionWith (ValueType valueToInclude) const noexcept
    {
        return Range (std::min (valueToInclude, start),
                      std::max (valueToInclude, end));
    }

    /** Returns a given range, after moving it forwards or backwards to fit it
        within this range.

        If the supplied range has a greater length than this one, the return value
        will be this range.

        Otherwise, if the supplied range is smaller than this one, the return value
        will be the new range, shifted forwards or backwards so that it doesn't extend
        beyond this one, but keeping its original length.
    */
    Range constrainRange (Range rangeToConstrain) const noexcept
    {
        const ValueType otherLen = rangeToConstrain.getLength();

        return getLength() <= otherLen
                ? *this
                : rangeToConstrain.movedToStartAt (jlimit (start, end - otherLen, rangeToConstrain.getStart()));
    }

    /** Scans an array of values for its min and max, and returns these as a Range. */
    static Range findMinAndMax (const ValueType* values, int numValues) noexcept
    {
        if (numValues <= 0)
            return Range();

        const ValueType first (*values++);
        Range r (first, first);

        while (--numValues > 0) // (> 0 rather than >= 0 because we've already taken the first sample)
        {
            const ValueType v (*values++);

            if (r.end < v)
                r.end = v;

            if (v < r.start)
                r.start = v;
        }

        return r;
    }

private:
    //==============================================================================
    ValueType start, end;
};

#endif //SQUAREPINE_RANGE_H
