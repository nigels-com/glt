#include "hex.h"

/*! \file
    \ingroup Misc

    $Id: hex.cpp,v 2.0 2004/02/08 19:44:13 nigels Exp $

    $Log: hex.cpp,v $
    Revision 2.0  2004/02/08 19:44:13  nigels
    Migrate to CVS on sourceforge, revision incremented to 2.0

    Revision 1.2  2004/02/08 14:13:22  jgasseli
    Sorry, first commit included some minor changes to the Makefiles to make GLT compile without
    errors on my puter.

    - Jacques.

    Revision 1.6  2003/05/10 17:02:52  nigels
    *** empty log message ***

    Revision 1.3  2003/03/06 12:34:46  nigels
    *** empty log message ***

*/

byte
fromHex(const char ch)
{
    if (ch>='0' && ch<='9')
        return ch-'0';

    if (ch>='a' && ch<='f')
        return ch-'a'+10;

    if (ch>='A' && ch<='F')
        return ch-'A'+10;

    // Ouch, not expecting anything exotic!
    assert((ch>='0' && ch<='9') || (ch>='a' && ch<='f') || (ch>='A' && ch<='F'));

    return 0;
}

byte
fromHex(const char a,const char b)
{
    return (fromHex(a)<<4) | fromHex(b);
}

char
toHex(const uint32 val)
{
    const char table[16] =
    {
        '0', '1', '2', '3', '4', '5', '6', '7',
        '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'
    };

    // Check sanity of input
    assert(val>=0 && val<=15);

    return table[val&15];
}

char
toHex(const int32 val)
{
    return toHex(uint32(val));
}
