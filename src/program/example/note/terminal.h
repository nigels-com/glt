#ifndef GLT_NOTE_TERMINAL
#define GLT_NOTE_TERMINAL

#include <string>
#include <list>

#include <glt/font.h>
#include <glt/color.h>

#include <glutm/input.h>

#include "textbuff.h"

class GltViewport;

// GltNoteTerminal - Handle keyboard input and OpenGL drawing

class GltNoteTerminal : public GlutInput
{
public:
    GltNoteTerminal(GltFont &font);
    ~GltNoteTerminal();

    void draw(const GltViewport &viewport);

    void OnKeyboard(unsigned char key, int x, int y);
    void OnSpecial(int key, int x, int y);

    void clear();

    typedef enum CursorStyle
    {
        CURSOR_OUTLINE,
        CURSOR_SOLID,
        CURSOR_UNDERLINE
    } CursorStyle;

private:

    GltTextBuffer         _buffer;
    GltTextBufferIterator _pos;

    GltColor   _textColor;
    GltColor   _cursorColor;
    GltColor   _currentLineFrontColor;
    GltColor   _currentLineBackColor;

    GltFont &_font;

    static void drawCursor(const CursorStyle cursor,const int width,const int height);
};

#endif
