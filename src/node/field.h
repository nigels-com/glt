#ifndef NODE_FIELD_H
#define NODE_FIELD_H

/*

  GLT OpenGL C++ Toolkit (LGPL)
  Copyright (C) 2000-2004 Nigel Stewart


  WWW:    http://www.nigels.com/glt/
  Forums: http://sourceforge.net/forum/?group_id=36869

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

*/

/*! \file
    \brief   Base class for field serialisation/menu system
    \ingroup Node
*/

#include <string>
#include <iosfwd>
#include <misc/refcount.h>

class GltRegistry;
class GltFields;

class GltField;

///////////////////////////// GltField ///////////////////////////////////////

/// Reference counted field pointer
typedef ReferenceCountPtr<GltField> GltFieldPtr;

/*! \class   GltField
    \brief   Base class for field serialisation/menu system
    \ingroup Node
    \todo    Documentation
*/

class GltField
{
    friend class GltFields;
    friend class GltRegistry;

protected:
    GltField();                             ///< Protected default constructor
    GltField(const std::string &name);      ///< Protected constructor
    GltField(const GltField &);             ///< Protected constructor
    GltField &operator=(const GltField &);  ///< Protected assignment operator

public:

    virtual ~GltField();                                ///< Destructor

            std::string &name();                        ///< Field name
      const std::string &name() const;                  ///< Field name

    // Read

    virtual std::string get()     const;                ///< Get value as string
    virtual std::string display() const;                ///< Display value as string

    // Write

    virtual        bool set(const std::string &value);  ///< Set value
    virtual        bool reset();                        ///< Reset value
    virtual        bool isDefault() const;              ///< Is default

    /// Output to stream

    virtual  bool write(std::ostream &os,const std::string &prefix = "") const;

protected:

    std::string _name;
    bool        _output;    ///< Functions can be optionally written to output

    #ifdef GLT_WIN32
    virtual bool writeRegistry(void *key) const;
    virtual bool readRegistry (void *key);
    #endif
};

////////////

/*! \class   GltFieldFunc
    \brief   Callback function field
    \ingroup Node

    \note
        We'd like to migrate this into GltFields, but
        the microsoft compiler can't deal with it.
*/

template<class T>
class GltFieldFunc : public GltField
{
public:
    GltFieldFunc(T &obj,void (T::*func)(void),const std::string &name,const bool output = false)
    : GltField(name), _obj(&obj), _func(func)
    {
        _output = output;
    }

    GltFieldFunc(const GltFieldFunc &f)
    : GltField(f), _obj(f._obj), _func(f._func)
    {
    }

    virtual ~GltFieldFunc()
    {
    }

    GltFieldFunc &operator=(const GltFieldFunc &f)
    {
        if (this!=&f)
        {
            _name   = f._name;
            _obj    = f._obj;
            _func   = f._func;
            _output = f._output;
        }

        return *this;
    }

/*
    bool write(std::ostream &os,const std::string &prefix = std::string()) const
    {
        if (_output)
            GltField::write(os,prefix);

        return true;
    }
*/

    bool set(const std::string &value)
    {
        (_obj->*(_func))();
        return true;
    }

private:

    T *_obj;                    ///< Object to receive events
    void (T::*_func)(void);     ///< Void object callback function
};

#endif
