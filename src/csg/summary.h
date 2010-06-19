#ifndef CSG_SUMMARY_H
#define CSG_SUMMARY_H

/** \file
 *  \brief   Summary Template
 *  \ingroup CSG
 *  \author  Nigel Stewart (nigels.com@gmail.com)
 *  \author  RMIT School of Computer Science and Information Technology
 *  \author  RMIT Department of Mechanical and Manufacturing Engineering
 */

#include <string>
#include <cstdio>

#include <math/real.h>
#include <misc/string.h>

template<class T>
class summary
{
public:
    summary()
    : _current(T()), _last(T()), _min(T()), _max(T()), _sum(T()), _samples(0), _defined(false)
    {
    }

    ~summary()
    {
    }

    operator       T &()       { _defined = true; return _current; }
    operator const T &() const {                  return _current; }

    summary<T> &operator=(const T &val) { _defined = true; _current = val; return *this; }

    const int    samples() const { return _samples;              }
    const bool   defined() const { return _defined;              }
    const double mean()    const { return double(_sum)/_samples; }

    void update()
    {
        if (!_defined)
            return;

        if (_samples==0)
            _last = _min = _max = _sum = _current;
        else
        {
            _last = _current;
            _min  = std::min(_min,_current);
            _max  = std::max(_max,_current);
            _sum  += _current;
        }

        _samples++;

        _current = 0;
        _defined = false;
    }

    void reset()
    {
        _current = _last = _min = _max = _sum = T();
        _samples = 0;
        _defined = false;
    }

    std::string str() const
    {
        std::string tmp;

        if (_samples>0)
        {
            sprintf
            (
                tmp,
                "%10.2f %10.2f %10.2f %10.2f",
                float(_last),
                float(_min),
                float(_max),
                float(mean())
            );
        }

        return tmp;
    }

private:

    T      _current;
    T      _last;
    T      _min;
    T      _max;
    T      _sum;
    uint32 _samples;
    bool   _defined;
};

/// Template-specialisation for integer display
template<>
inline std::string summary<int>::str() const
{
    std::string tmp;

    if (_samples>0)
    {
        sprintf
        (
            tmp,
            "%7d %7d %7d %10.2f",
            int(_last),
            int(_min),
            int(_max),
            float(mean())
        );
    }

    return tmp;
}

/// Template-specialisation for unsigned integer display
template<>
inline std::string summary<unsigned int>::str() const
{
    std::string tmp;

    if (_samples>0)
    {
        sprintf
        (
            tmp,
            "%7u %7u %7u %10.2f",
            (unsigned int)(_last),
            (unsigned int)(_min),
            (unsigned int)(_max),
            float(mean())
        );
    }

    return tmp;
}

/// Template-specialisation for long integer display
template<>
inline std::string summary<long int>::str() const
{
    std::string tmp;

    if (_samples>0)
    {
        sprintf
        (
            tmp,
            "%7ld %7ld %7ld %10.2f",
            (long int)_last,
            (long int)_min,
            (long int)_max,
            float(mean())
        );
    }

    return tmp;
}

#if defined(linux) && defined(i386)

/// Template-specialisation for int64 display
template<>
inline std::string summary<int64>::str() const
{
    std::string tmp;

    if (_samples>0)
    {
        sprintf
        (
            tmp,
            "%7lld %7lld %7lld %10.2f",
            (int64) _last,
            (int64) _min,
            (int64) _max,
            float(mean())
        );
    }

    return tmp;
}

/// Template-specialisation for int64 display
template<>
inline std::string summary<uint64>::str() const
{
    std::string tmp;

    if (_samples>0)
    {
        sprintf
        (
            tmp,
            "%7llu %7llu %7llu %10.2f",
            (uint64) _last,
            (uint64) _min,
            (uint64) _max,
            float(mean())
        );
    }

    return tmp;
}
#endif

#endif

