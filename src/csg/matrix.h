#ifndef CSG_MATRIX_H
#define CSG_MATRIX_H

/** \file
 *  \brief   Generic STL style matrix class
 *  \ingroup CSG
 *  \author  Nigel Stewart (nigels.com@gmail.com)
 *  \author  RMIT School of Computer Science and Information Technology
 *  \author  RMIT Department of Mechanical and Manufacturing Engineering
 */

#ifdef WIN32
#pragma warning(disable : 4786)
#endif

#include <vector>
#include <cassert>

namespace std
{

template<class T>
class matrix
{
public:

    typedef T Type;

    //
    // Constructor/Destructor
    //

    /// Default constructor
    matrix(const int size = 0,const T &val = T())
    : _size(size), _default(val)
    {
        assert(_size>=0);
        _matrix.resize(_size*_size);
        clear();
    }

    /// Destructor
    ~matrix()
    {
    }

    //
    // Get
    //

    /// Get size of matrix
    const int size() const                  { return _size; }

    /// Get entry
    const T &get(const int i,const int j) const
    {
        return _matrix[index(i,j)];
    }

    //
    // Set
    //

    /// Set entry
    void set(const int i,const int j,const T &val)
    {
        _matrix[index(i,j)] = val;
    }

    //
    // Clear
    //

    /// Clear entry
    void clear(const int i,const int j)
    {
        _matrix[index(i,j)] = _default;
    }

    /// Clear row and column
    void clear(const int i)
    {
        for (int j=0; j<_size; j++)
        {
            _matrix[index(i,j)] = _default;
            _matrix[index(j,i)] = _default;
        }
    }

    /// Clear the entire table
    void clear()
    {
        for (int i=0; i<_size; i++)
            _matrix[i] = _default;
    }

private:
    const int _size;
    const T   _default;
    vector<T> _matrix;

    int index(const int i,const int j) const
    {
        assert(i>=0);
        assert(j>=0);
        assert(i<_size);
        assert(j<_size);
        return i + j*_size;
    }
};

}

#endif
