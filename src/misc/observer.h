#ifndef MISC_OBSERVER_H
#define MISC_OBSERVER_H

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
    \brief   Templated type-safe Observer-Subject pattern
    \ingroup Misc
*/

#include <glt/config.h>

#include <cassert>
#include <list>

class GltSubject;

/*! \class   GltObserverAbstract
    \brief   Abstract base-class for Observer classes
    \ingroup Misc

    This class can not be used directly, see
    GltObserver.
*/

class GltObserverAbstract
{
    friend class GltSubject;

protected:

    /// Constructor
    GltObserverAbstract();
    /// Copy constructor
    GltObserverAbstract(const GltObserverAbstract &);
    /// Destructor
    virtual ~GltObserverAbstract();

    /// Assignment operator
    GltObserverAbstract &operator=(const GltObserverAbstract &);

    /// Observe an object
    void observe(GltSubject &subject);
    /// Forget an object
    void forget (GltSubject &subject);

    /// Supplied by GltObserver to do type-specific OnNotify callback event
    virtual void OnNotify(const void *subject) = 0;

    /// List of subjects observed by this object
    std::list<GltSubject *> _subjects;
};

/*! \class   GltObserver
    \brief   Type-safe base-class for Observer classes
    \ingroup Misc

    Classes inheriting from GltObserver can observe
    one or more subjects of a particular type.  The
    derived class must define an OnNotify() handler
    for each type of subject that it observes.  When
    the GltSubject derived subject calls the notify()
    member function, each observer will receive the
    OnNotify() callback.

    It is safe to delete either the subject or
    observer at any time.  Both will "forget"
    about each other as soon as either of the
    destructors is called.
*/

template<class T>
class GltObserver : public GltObserverAbstract
{
public:

    /// Constructor
    GltObserver() {}
    /// Destructor
    ~GltObserver() {}

    /// Observe an object
    void observe(T &subject) { GltObserverAbstract::observe(subject); }
    /// Forget an object
    void forget (T &subject) { GltObserverAbstract::forget (subject); }

    /// Callback handler for subject updates -- should be supplied by subclass
    virtual void OnNotify(const T *subject) = 0;

protected:

    void OnNotify(const void *subject)
    {
        OnNotify((const T *) subject);
    }
};

/*! \class   GltSubject
    \brief   Subject Class
    \ingroup Misc

    Classes inheriting from GltSubject can be observed
    by one or more observers.  All registered observers
    will receive the OnNotify() callback when the GltSubject
    derived class calls notify().

    See also GltObserver.
*/

class GltSubject
{
    friend class GltObserverAbstract;

public:
    /// Constructor
    GltSubject();
    /// Copy-constructor -- copy does not receive observers
    GltSubject(const GltSubject &);
    /// Destructor
    ~GltSubject();

    /// Assignment operator -- observers are unaffected
    GltSubject &operator=(const GltSubject &);

    /// Notify observers of an update
    void notify(const void *object);

private:

    std::list<GltObserverAbstract *> _observers;
};

#define NOTIFY notify(this)

#endif

