#ifndef NODE_FIELDS_H
#define NODE_FIELDS_H

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
    \author  Nigel Stewart, RMIT (nigels.com@gmail.com)
    \ingroup Node
*/

#ifdef _MSC_VER
#pragma warning(disable: 4786)
#endif

#include <node/field.h>

#include <vector>
#include <string>

#include <cstdio>

class Vector2;
class Vector3;
class Vector4;
class Matrix;
class BoundingBox;
class GltColor;
class GltLight;
class GltMaterial;
class GltViewport;
class GltOrtho;

class GltRegistry;
class GltRegistryMenu;

///////////////////////////// GltFields ///////////////////////////////////////

/*! \clas    GltFields
    \brief   Field container class
    \ingroup Node
    \todo    Documentation
*/

class GltFields : public GltField
{
    friend class GltRegistry;
    friend class GltRegistryMenu;

public:
             GltFields(const std::string &name);
             GltFields(const GltFields &);
    virtual ~GltFields();

    GltFields &operator=(const GltFields &);

    void add(bool         &,                  const std::string &name);
    void add(short        &,                  const std::string &name);
    void add(int          &,                  const std::string &name);
    void add(unsigned int &,                  const std::string &name);
    void add(long         &,                  const std::string &name);
    void add(float        &,                  const std::string &name);
    void add(float        &,const float step, const std::string &name);
    void add(double       &,                  const std::string &name);
    void add(double       &,const double step,const std::string &name);
    void add(std::string  &,                  const std::string &name);
    void add(Vector2      &,                  const std::string &name);
    void add(Vector3      &,                  const std::string &name);
    void add(Vector4      &,                  const std::string &name);
    void add(Matrix       &,                  const std::string &name);
    void add(BoundingBox  &,                  const std::string &name);
    void add(GltColor     &,                  const std::string &name);
    void add(GltLight     &,                  const std::string &name);
    void add(GltMaterial  &,                  const std::string &name);
    void add(GltViewport  &,                  const std::string &name);
    void add(GltOrtho     &,                  const std::string &name);

    /// Enum

    void add(int          &,const int max,const std::string *labels,const std::string &name);

    /// Add object with settings() member

//  template<class T>
//  void add(T &v,const std::string &name)
//  {
//      GltFieldPtr root = v.settings();
//      root->name() = name;
//      add(root);
//  }

    void add(const GltFieldPtr &field);
    void add(const GltFieldPtr &field,const std::string &rename);
    void add(      GltField    *field);

    /// Add fixed-size array

    template<class T>
    void add(T *ptr,const int n,const std::string &name)
    {
        GltFields *root = new GltFields(name);
        _fields.push_back(GltFieldPtr(root));

        for (int i=0; i<n; i++,ptr++)
        {
            char buffer[10];
            sprintf(buffer,"%d",i);
            root->add(*ptr,buffer);
        }
    }

    /// Add function

    template<class T>
    void add(T &obj,void (T::*func)(void),const std::string &name,const bool output = false)
    {
        add(GltFieldPtr(new GltFieldFunc<T>(obj,func,name,output)));
    }

    bool reset();

    /// Merge

    void merge(const GltFieldPtr &root);

    bool write(std::ostream &os,const std::string &prefix = std::string()) const;

protected:

    #ifdef GLT_WIN32
    virtual bool writeRegistry(void *key) const;
    virtual bool readRegistry (void *key);
    #endif

private:

    std::vector<GltFieldPtr> _fields;

    ////////////////////////////////////////////////////////////////////////////

    /*! \clas    GltFieldBool
        \brief   Boolean field
        \ingroup Node
    */

    class GltFieldBool : public GltField
    {
    public:
        GltFieldBool(bool &val,const std::string &name);
        GltFieldBool(const GltFieldBool &);
        virtual ~GltFieldBool();

              bool &val();
        const bool &val() const;

        std::string get() const;
        bool        set(const std::string &value);
        bool        reset();
        bool        isDefault() const;

    private:

              bool &_val;
        const bool  _default;
    };

    /*! \class   GltFieldShort
        \brief   Short field
        \ingroup Node
     */
  
    class GltFieldShort : public GltField
    {
    public:
      GltFieldShort(short &val,const std::string &name);
      GltFieldShort(const GltFieldShort &);
      virtual ~GltFieldShort();
    
            short &val();
      const short &val() const;
    
      std::string get() const;
      bool        set(const std::string &value);
      bool        reset();
      bool        isDefault() const;
    
    private:
    
      short &_val;
      const short  _default;
    };

    /*! \class   GltFieldInt
        \brief   Short field
        \ingroup Node
    */

    class GltFieldInt : public GltField
    {
    public:
        GltFieldInt(int &val,const std::string &name);
        GltFieldInt(const GltFieldInt &);
        virtual ~GltFieldInt();

              int &val();
        const int &val() const;

        std::string get() const;
        bool        set(const std::string &value);
        bool        reset();
        bool        isDefault() const;

    private:

              int &_val;
        const int  _default;
    };

    /*! \class   GltFieldLong
        \brief   Short field
        \ingroup Node
    */

    class GltFieldLong : public GltField
    {
    public:
        GltFieldLong(long &val,const std::string &name);
        GltFieldLong(const GltFieldLong &);
        virtual ~GltFieldLong();

              long &val();
        const long &val() const;

        std::string get() const;
        bool        set(const std::string &value);
        bool        reset();
        bool        isDefault() const;

    private:

              long &_val;
        const long  _default;
    };
    
    /*! \clas    GltFieldDouble
        \brief   Double field
        \ingroup Node
    */

    class GltFieldDouble : public GltField
    {
    public:
        GltFieldDouble(double &val,const double step,const std::string &name);
        GltFieldDouble(const GltFieldDouble &);
        virtual ~GltFieldDouble();

              double &val();
        const double &val() const;

        std::string get() const;
        std::string display() const;
        bool        set(const std::string &value);
        bool        reset();
        bool        isDefault() const;

        GltFieldDouble &operator++();
        GltFieldDouble &operator--();

    private:

              double &_val;
              double  _step;
        const double  _default;
    };

    /*! \clas    GltFieldFloat
        \brief   Float field
        \ingroup Node
    */

    class GltFieldFloat : public GltField
    {
    public:
        GltFieldFloat(float &val,const float step,const std::string &name);
        GltFieldFloat(const GltFieldFloat &);
        virtual ~GltFieldFloat();

              float &val();
        const float &val() const;

        std::string get()     const;
        std::string display() const;
        bool        set(const std::string &value);
        bool        reset();
        bool        isDefault() const;

        GltFieldFloat &operator++();
        GltFieldFloat &operator--();

    private:

        float       &_val;
        float        _step;
        const float  _default;
    };

    /*! \clas    GltFieldString
        \brief   std::string field
        \ingroup Node
    */

    class GltFieldString : public GltField
    {
    public:
        GltFieldString(std::string &val,const std::string &name);
        GltFieldString(const GltFieldString &);
        virtual ~GltFieldString();

              std::string &val();
        const std::string &val() const;

        std::string get() const;
        bool        set(const std::string &value);
        bool        reset();
        bool        isDefault() const;

    private:

              std::string &_val;
        const std::string  _default;
    };

    /*! \clas    GltFieldEnum
        \brief   Enu, field
        \ingroup Node
    */

    class GltFieldEnum : public GltField
    {
    public:
        GltFieldEnum(int &val,const int max,const std::string *labels,const std::string &name);
        GltFieldEnum(const GltFieldEnum &);
        virtual ~GltFieldEnum();

              int &val();
        const int &val() const;

        std::string get() const;
        bool        set(const std::string &value);
        bool        reset();
        bool        isDefault() const;

        GltFieldEnum &operator++();
        GltFieldEnum &operator--();
        GltFieldEnum &operator=(const int i);

    private:

                      int &_val;
                const int  _default;
                const int  _max;
        const std::string *_labels;
    };
};

#endif
