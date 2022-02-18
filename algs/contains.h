//
// Created by franzs on 18.02.22.
//

#ifndef UTILLIB_CONTAINS_H
#define UTILLIB_CONTAINS_H

template <typename ForwardIt>
bool contains1(ForwardIt beg, ForwardIt end, int val)
{
    bool found = false;
    for (auto x = beg; x != end; ++x)
        if (*x == val)
            found = true;

    return found;
}


template <typename ForwardIt>
bool contains2(ForwardIt beg, ForwardIt end, int val)
{
    bool found = false;
    for (auto x = beg; x != end; ++x)
        if (*x == val)
            return true;
    return false;
}

template <typename ForwardIt>
bool contains3(ForwardIt beg, ForwardIt end, int val)
{
    if (beg - end >= 0)
        return false;
    auto middle = beg + (end  - beg) / 2;
    if (*middle == val)
        return true;
    if (*middle > val)
        return contains3(beg, middle-1, val);
    return contains3(middle+1, end, val);
}

#endif //UTILLIB_CONTAINS_H
