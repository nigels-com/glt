#ifndef CSG_SPARSE_H
#define CSG_SPARSE_H

/** \file
 *  \brief   Generic STL style sparse-matrix class
 *  \ingroup CSG
 *  \author  Nigel Stewart (nigels@nigels.com)
 *  \author  RMIT School of Computer Science and Information Technology
 *  \author  RMIT Department of Mechanical and Manufacturing Engineering
 */

#ifdef _MSC_VER
#pragma warning(disable : 4786)
#endif

#include <vector>
#include <map>
#include <cassert>

//namespace std
//{

template<class T>
class sparse_matrix
{
public:

    typedef T Type;

    //
    // Constructor/Destructor
    //

    /// Default constructor
    sparse_matrix(const unsigned int size = 0,const T def = T())
    : _size(size), _default(def)
    {
        assert(_size>=0);
        _matrix.resize(_size);
    }

    sparse_matrix(const sparse_matrix &matrix)
    : _size(matrix._size), _default(matrix._default), _matrix(matrix._matrix)
    {
    }

    /// Destructor
    ~sparse_matrix()
    {
    }

    sparse_matrix &operator=(const sparse_matrix &matrix)
    {
        _size    = matrix._size;
        _default = matrix._default;
        _matrix  = matrix._matrix;
        return *this;
    }

    //
    // Get
    //

    /// Get size of matrix
    const unsigned int size() const { return _size; }

    /// Is there an entry for a particular row/column?
    const bool defined(const unsigned int i,const unsigned int j) const
    {
        assert(i>=0);
        assert(j>=0);
        assert(i<_size);
        assert(j<_size);
        typename std::map<unsigned int,T>::const_iterator k = _matrix[i].find(j);
        return k!=_matrix[i].end();
    }

    /// Get entry
    const T &get(const unsigned int i,const unsigned int j) const
    {
        assert(i>=0);
        assert(j>=0);
        assert(i<_size);
        assert(j<_size);
        typename std::map<unsigned int,T>::const_iterator k = _matrix[i].find(j);
        return (k!=_matrix[i].end() ? k->second : _default);
    }

    const std::map<unsigned int,T> &getRow(const unsigned int i) const
    {
        assert(i>=0);
        assert(i<_size);
        return _matrix[i];
    }

    /// Get the number of entries in a row
    const unsigned int rowSize(const unsigned int i) const
    {
        assert(i>=0);
        assert(i<_size);
        return _matrix[i].size();
    }

    //
    // Set
    //

    /// Set entry
    void set(const unsigned int i,const unsigned int j,const T &val)
    {
        if (val==_default)
            clear(i,j);
        else
        {
            assert(i>=0);
            assert(j>=0);
            assert(i<_size);
            assert(j<_size);

            (_matrix[i])[j] = val;
        }
    }

    //
    // Clear
    //

    /// Clear entry
    void clear(const unsigned int i,const unsigned int j)
    {
        assert(i>=0);
        assert(j>=0);
        assert(i<_size);
        assert(j<_size);

        _matrix[i].erase(j);
    }

    /// Clear row and column
    void clear(const unsigned int i)
    {
        assert(i>=0);
        assert(i<_size);

        _matrix[i].clear();

        for (unsigned int j=0; j<_size; j++)
            _matrix[j].erase(i);
    }

    /// Clear container of rows and columns
    template<class I>
    void clear(const I &begin,const I &end)
    {
        I i = begin;
        while (i!=end)
        {
            clear(*i);
            i++;
        }
    }

    /// Clear the entire table
    void clear()
    {
        for (unsigned int i=0; i<_size; i++)
            _matrix[i].clear();
    }

private:
    unsigned int _size;
    T            _default;

    std::vector< std::map<unsigned int,T> > _matrix;
};

//}

#endif
