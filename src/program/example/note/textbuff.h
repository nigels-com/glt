#ifndef GLT_TEXTBUFF
#define GLT_TEXTBUFF

#ifdef MSC_VER
#pragma warning(disable : 4786)     // Lengthy STL symbols
#endif

#include <string>
#include <list>

//////////////////////////////////////////////////////////////////

// GltTextBuffer - list of std::string

class GltTextBuffer : public std::list<std::string>
{
    friend class GltTextBufferIterator;

public:
    GltTextBuffer();
    ~GltTextBuffer();

    void clear();
};

// GltTextBuffer iterator
//
// Mainly takes care of keyboard input and insertion
// of text.  Insert mode, wrap mode.

class GltTextBufferIterator
{
public:
    GltTextBufferIterator(GltTextBuffer &buffer);
    ~GltTextBufferIterator();

    void reset();

    bool goUp();
    bool goDown();
    bool goLeft();
    bool goRight();

    void insert(const char ch);
    void insert(const std::string &string);

          GltTextBuffer::iterator &line();
          GltTextBuffer::iterator begin();
          GltTextBuffer::iterator end();

    const int x() const;

    const bool &modeInsert() const;
          bool &modeInsert();

    const bool &modeWrap() const;
          bool &modeWrap();

protected:
    bool nextLine();
    bool prevLine();

    bool nextChar();
    bool prevChar();

private:
    GltTextBuffer          &_buffer;
    GltTextBuffer::iterator _line;
    unsigned int            _x;

    bool _insert;

    bool                    _wrap;
    unsigned int            _wrapColumn;
};

#endif
