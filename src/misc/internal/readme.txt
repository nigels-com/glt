DESCRIPTION
    LZF is an extremely fast (not that much slower than a pure memcpy)
    compression algorithm. It is ideal for applications where you want to
    save *some* space but not at the cost of speed. It is ideal for
    repetitive data as well. The module is self-contained and very small (no
    large library to be pulled in).

    I do not know for certain wether any patents in any countries apply
    to this algorithm, but at the moment it is believed that it is free
    from any patents. More importantly, it is also free to use in every
    software package (see LICENSE).

    See the lzf.h file for details on how the functions in this
    mini-library are to be used.

    NOTE: This package contains a very bare-bones command-line utility
    which is neither optimized for speed nor for compression. This library
    is really intented to be used inside larger programs.

AUTHOR
    This library was written by Marc Lehmann <pcg@goof.com> (See also
    http://liblzf.plan9.de/).


