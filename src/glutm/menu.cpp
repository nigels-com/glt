#include "menu.h"

/*! \file
    \ingroup GlutMaster

    \todo Possible crash when inserting empty sub-menu
*/

#include <glutm/master.h>

//////////////

GlutMenu::GlutMenu(int button)
: _button(button), _menuID(-1)
{
}

GlutMenu::~GlutMenu()
{
    reset();
}

GlutMenu &
GlutMenu::subMenu()
{
    _subMenu.push_back(new GlutMenu(_button));
    return *_subMenu.back();
}

void
GlutMenu::resetList()
{
    for (std::list<GlutMenu *>::iterator i=_subMenu.begin(); i!=_subMenu.end(); i++)
        delete *i;

    _subMenu.clear();
}

#if !defined(GLUTM_SAVER)

void
GlutMenu::addEntry(const std::string &name,int value)
{
    if (_menuID==-1)
        _menuID = glutCreateMenu(GlutMaster::OnMenu);

    glutSetMenu(_menuID);
    glutAddMenuEntry(name.c_str(),value);
}

void
GlutMenu::addEntry(const std::string &name,GlutMenu &menu)
{
    if (_menuID==-1)
        _menuID = glutCreateMenu(GlutMaster::OnMenu);

    glutSetMenu(_menuID);
    glutAddSubMenu(name.c_str(),menu._menuID);
}

void
GlutMenu::reset()
{
    if (_menuID!=-1)
    {
        glutSetMenu(_menuID);
        int n = glutGet(GLenum(GLUT_MENU_NUM_ITEMS));
        for (int i=0; i<n; i++)
            glutRemoveMenuItem(1);
    }

    resetList();
}

void
GlutMenu::attach()
{
    if (_menuID!=-1)
    {
        glutSetMenu(_menuID);
        glutAttachMenu(_button);
    }
}

void
GlutMenu::detach()
{
    if (_menuID!=-1)
    {
        glutSetMenu(_menuID);
        glutDetachMenu(_button);
    }
}

#else

void GlutMenu::addEntry(const std::string &name,int value)      {}
void GlutMenu::addEntry(const std::string &name,GlutMenu &menu) {}
void GlutMenu::attach() {}
void GlutMenu::detach() {}

void GlutMenu::reset()
{
    resetList();
}

#endif
