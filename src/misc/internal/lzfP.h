/*
 * Copyright (c) 2000-2002 Marc Alexander Lehmann <pcg@goof.com>
 *
 * Redistribution and use in source and binary forms, with or without modifica-
 * tion, are permitted provided that the following conditions are met:
 *
 *   1.  Redistributions of source code must retain the above copyright notice,
 *       this list of conditions and the following disclaimer.
 *
 *   2.  Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *
 *   3.  The name of the author may not be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MER-
 * CHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO
 * EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPE-
 * CIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTH-
 * ERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef LZFP_h
#define LZFP_h

#define STANDALONE /* at the moment, this is ok. */

#ifndef STANDALONE
# include "lzf.h"
#endif

/*
 * size of hashtable is (1 << HLOG) * sizeof (char *)
 * decompression is independent of the hash table size
 * the difference between 15 and 14 is very small
 * for small blocks (and 14 is also faster).
 * For a low-memory configuration, use HLOG == 13;
 * For best compression, use 15 or 16.
 */
#ifndef HLOG
# define HLOG 14
#endif

/*
 * sacrifice some compression quality in favour of compression speed.
 * (roughly 1-2% worse compression for large blocks and
 * 9-10% for small, redundant, blocks and >>20% better speed in both cases)
 * In short: enable this for binary data, disable this for text data.
 */
#ifndef ULTRA_FAST
# define ULTRA_FAST 1
#endif

/*
 * unconditionally aligning does not cost very much, so do it if unsure
 */
#ifndef STRICT_ALIGN
# define STRICT_ALIGN !defined(__i386)
#endif

/*
 * use string functions to copy memory.
 * this is usually a loss, even with glibc's optimized memcpy
 */
#ifndef USE_MEMCPY
# define USE_MEMCPY 0
#endif

/*
 * you may choose to pre-set the hash table (might be faster on modern cpus
 * and large (>>64k) blocks)
 */
#ifndef INIT_HTAB
# define INIT_HTAB 0
#endif

/*****************************************************************************/
/* nothing should be changed below */

typedef unsigned char u8;

#if !STRICT_ALIGN
/* for unaligned accesses we need a 16 bit datatype. */
# include <limits.h>
# if USHRT_MAX == 65535
    typedef unsigned short u16;
# elif UINT_MAX == 65535
    typedef unsigned int u16;
# else
#  warn need 16 bit datatype when STRICT_ALIGN == 0, this is non-fatal
#  undef STRICT_ALIGN
#  define STRICT_ALIGN 1
# endif
#endif

#if USE_MEMCPY || INIT_HTAB
# include <string.h>
#endif

#endif

