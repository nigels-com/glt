/* A Bison parser, made by GNU Bison 1.875.  */

/* Skeleton parser for Yacc-like parsing with Bison,
   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

/* Written by Richard Stallman by simplifying the original so called
   ``semantic'' parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0

/* If NAME_PREFIX is specified substitute the variables and functions
   names.  */
#define yyparse Vrmlparse
#define yylex   Vrmllex
#define yyerror Vrmlerror
#define yylval  Vrmllval
#define yychar  Vrmlchar
#define yydebug Vrmldebug
#define yynerrs Vrmlnerrs


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     TRUEFALSE = 258,
     NUMBER = 259,
     AFLOAT = 260,
     STRING = 261,
     NAME = 262,
     ANCHOR = 263,
     APPEARANCE = 264,
     AUDIOCLIP = 265,
     BACKGROUND = 266,
     BILLBOARD = 267,
     BOX = 268,
     COLLISION = 269,
     COLOR = 270,
     COLOR_INTERP = 271,
     COORDINATE = 272,
     COORDINATE_INTERP = 273,
     CYLINDER_SENSOR = 274,
     NULL_STRING = 275,
     CONE = 276,
     CUBE = 277,
     CYLINDER = 278,
     DIRECTIONALLIGHT = 279,
     FONTSTYLE = 280,
     AERROR = 281,
     EXTRUSION = 282,
     ELEVATION_GRID = 283,
     FOG = 284,
     INLINE = 285,
     MOVIE_TEXTURE = 286,
     NAVIGATION_INFO = 287,
     PIXEL_TEXTURE = 288,
     GROUP_NODE = 289,
     INDEXEDFACESET = 290,
     INDEXEDLINESET = 291,
     S_INFO = 292,
     LOD = 293,
     MATERIAL = 294,
     NORMAL = 295,
     POSITION_INTERP = 296,
     PROXIMITY_SENSOR = 297,
     SCALAR_INTERP = 298,
     SCRIPT = 299,
     SHAPE = 300,
     SOUND = 301,
     SPOTLIGHT = 302,
     SPHERE_SENSOR = 303,
     ATEXT = 304,
     TEXTURE_COORDINATE = 305,
     TEXTURE_TRANSFORM = 306,
     TIME_SENSOR = 307,
     SWITCH = 308,
     TOUCH_SENSOR = 309,
     VIEWPOINT = 310,
     VISIBILITY_SENSOR = 311,
     WORLD_INFO = 312,
     NORMAL_INTERP = 313,
     ORIENTATION_INTERP = 314,
     POINTLIGHT = 315,
     POINTSET = 316,
     SPHERE = 317,
     PLANE_SENSOR = 318,
     TRANSFORM = 319,
     DEF = 320,
     USE = 321,
     PROTO = 322,
     ROUTE = 323,
     S_CHILDREN = 324,
     S_PARAMETER = 325,
     S_URL = 326,
     S_MATERIAL = 327,
     S_TEXTURETRANSFORM = 328,
     S_TEXTURE = 329,
     S_LOOP = 330,
     S_STARTTIME = 331,
     S_STOPTIME = 332,
     S_GROUNDANGLE = 333,
     S_GROUNDCOLOR = 334,
     S_SPEED = 335,
     S_AVATAR_SIZE = 336,
     S_BACKURL = 337,
     S_BOTTOMURL = 338,
     S_FRONTURL = 339,
     S_LEFTURL = 340,
     S_RIGHTURL = 341,
     S_TOPURL = 342,
     S_SKYANGLE = 343,
     S_SKYCOLOR = 344,
     S_AXIS_OF_ROTATION = 345,
     S_COLLIDE = 346,
     S_COLLIDETIME = 347,
     S_PROXY = 348,
     S_SIDE = 349,
     S_AUTO_OFFSET = 350,
     S_DISK_ANGLE = 351,
     S_ENABLED = 352,
     S_MAX_ANGLE = 353,
     S_MIN_ANGLE = 354,
     S_OFFSET = 355,
     S_BBOXSIZE = 356,
     S_BBOXCENTER = 357,
     S_VISIBILITY_LIMIT = 358,
     S_AMBIENT_INTENSITY = 359,
     AS_NORMAL = 360,
     S_TEXCOORD = 361,
     S_CCW = 362,
     S_COLOR_PER_VERTEX = 363,
     S_CREASE_ANGLE = 364,
     S_NORMAL_PER_VERTEX = 365,
     S_XDIMENSION = 366,
     S_XSPACING = 367,
     S_ZDIMENSION = 368,
     S_ZSPACING = 369,
     S_BEGIN_CAP = 370,
     S_CROSS_SECTION = 371,
     S_END_CAP = 372,
     S_SPINE = 373,
     S_FOG_TYPE = 374,
     S_VISIBILITY_RANGE = 375,
     S_HORIZONTAL = 376,
     S_JUSTIFY = 377,
     S_LANGUAGE = 378,
     S_LEFT2RIGHT = 379,
     S_TOP2BOTTOM = 380,
     IMAGE_TEXTURE = 381,
     S_SOLID = 382,
     S_KEY = 383,
     S_KEYVALUE = 384,
     S_REPEAT_S = 385,
     S_REPEAT_T = 386,
     S_CONVEX = 387,
     S_BOTTOM = 388,
     S_PICTH = 389,
     S_COORD = 390,
     S_COLOR_INDEX = 391,
     S_COORD_INDEX = 392,
     S_NORMAL_INDEX = 393,
     S_MAX_POSITION = 394,
     S_MIN_POSITION = 395,
     S_ATTENUATION = 396,
     S_APPEARANCE = 397,
     S_GEOMETRY = 398,
     S_DIRECT_OUTPUT = 399,
     S_MUST_EVALUATE = 400,
     S_MAX_BACK = 401,
     S_MIN_BACK = 402,
     S_MAX_FRONT = 403,
     S_MIN_FRONT = 404,
     S_PRIORITY = 405,
     S_SOURCE = 406,
     S_SPATIALIZE = 407,
     S_BERM_WIDTH = 408,
     S_CHOICE = 409,
     S_WHICHCHOICE = 410,
     S_FONTSTYLE = 411,
     S_LENGTH = 412,
     S_MAX_EXTENT = 413,
     S_ROTATION = 414,
     S_SCALE = 415,
     S_CYCLE_INTERVAL = 416,
     S_FIELD_OF_VIEW = 417,
     S_JUMP = 418,
     S_TITLE = 419,
     S_TEXCOORD_INDEX = 420,
     S_HEADLIGHT = 421,
     S_TOP = 422,
     S_BOTTOMRADIUS = 423,
     S_HEIGHT = 424,
     S_POINT = 425,
     S_STRING = 426,
     S_SPACING = 427,
     S_TYPE = 428,
     S_RADIUS = 429,
     S_ON = 430,
     S_INTENSITY = 431,
     S_COLOR = 432,
     S_DIRECTION = 433,
     S_SIZE = 434,
     S_FAMILY = 435,
     S_STYLE = 436,
     S_RANGE = 437,
     S_CENTER = 438,
     S_TRANSLATION = 439,
     S_LEVEL = 440,
     S_DIFFUSECOLOR = 441,
     S_SPECULARCOLOR = 442,
     S_EMISSIVECOLOR = 443,
     S_SHININESS = 444,
     S_TRANSPARENCY = 445,
     S_VECTOR = 446,
     S_POSITION = 447,
     S_ORIENTATION = 448,
     S_LOCATION = 449,
     S_CUTOFFANGLE = 450,
     S_WHICHCHILD = 451,
     S_IMAGE = 452,
     S_SCALEORIENTATION = 453,
     S_DESCRIPTION = 454
   };
#endif
#define TRUEFALSE 258
#define NUMBER 259
#define AFLOAT 260
#define STRING 261
#define NAME 262
#define ANCHOR 263
#define APPEARANCE 264
#define AUDIOCLIP 265
#define BACKGROUND 266
#define BILLBOARD 267
#define BOX 268
#define COLLISION 269
#define COLOR 270
#define COLOR_INTERP 271
#define COORDINATE 272
#define COORDINATE_INTERP 273
#define CYLINDER_SENSOR 274
#define NULL_STRING 275
#define CONE 276
#define CUBE 277
#define CYLINDER 278
#define DIRECTIONALLIGHT 279
#define FONTSTYLE 280
#define AERROR 281
#define EXTRUSION 282
#define ELEVATION_GRID 283
#define FOG 284
#define INLINE 285
#define MOVIE_TEXTURE 286
#define NAVIGATION_INFO 287
#define PIXEL_TEXTURE 288
#define GROUP_NODE 289
#define INDEXEDFACESET 290
#define INDEXEDLINESET 291
#define S_INFO 292
#define LOD 293
#define MATERIAL 294
#define NORMAL 295
#define POSITION_INTERP 296
#define PROXIMITY_SENSOR 297
#define SCALAR_INTERP 298
#define SCRIPT 299
#define SHAPE 300
#define SOUND 301
#define SPOTLIGHT 302
#define SPHERE_SENSOR 303
#define ATEXT 304
#define TEXTURE_COORDINATE 305
#define TEXTURE_TRANSFORM 306
#define TIME_SENSOR 307
#define SWITCH 308
#define TOUCH_SENSOR 309
#define VIEWPOINT 310
#define VISIBILITY_SENSOR 311
#define WORLD_INFO 312
#define NORMAL_INTERP 313
#define ORIENTATION_INTERP 314
#define POINTLIGHT 315
#define POINTSET 316
#define SPHERE 317
#define PLANE_SENSOR 318
#define TRANSFORM 319
#define DEF 320
#define USE 321
#define PROTO 322
#define ROUTE 323
#define S_CHILDREN 324
#define S_PARAMETER 325
#define S_URL 326
#define S_MATERIAL 327
#define S_TEXTURETRANSFORM 328
#define S_TEXTURE 329
#define S_LOOP 330
#define S_STARTTIME 331
#define S_STOPTIME 332
#define S_GROUNDANGLE 333
#define S_GROUNDCOLOR 334
#define S_SPEED 335
#define S_AVATAR_SIZE 336
#define S_BACKURL 337
#define S_BOTTOMURL 338
#define S_FRONTURL 339
#define S_LEFTURL 340
#define S_RIGHTURL 341
#define S_TOPURL 342
#define S_SKYANGLE 343
#define S_SKYCOLOR 344
#define S_AXIS_OF_ROTATION 345
#define S_COLLIDE 346
#define S_COLLIDETIME 347
#define S_PROXY 348
#define S_SIDE 349
#define S_AUTO_OFFSET 350
#define S_DISK_ANGLE 351
#define S_ENABLED 352
#define S_MAX_ANGLE 353
#define S_MIN_ANGLE 354
#define S_OFFSET 355
#define S_BBOXSIZE 356
#define S_BBOXCENTER 357
#define S_VISIBILITY_LIMIT 358
#define S_AMBIENT_INTENSITY 359
#define AS_NORMAL 360
#define S_TEXCOORD 361
#define S_CCW 362
#define S_COLOR_PER_VERTEX 363
#define S_CREASE_ANGLE 364
#define S_NORMAL_PER_VERTEX 365
#define S_XDIMENSION 366
#define S_XSPACING 367
#define S_ZDIMENSION 368
#define S_ZSPACING 369
#define S_BEGIN_CAP 370
#define S_CROSS_SECTION 371
#define S_END_CAP 372
#define S_SPINE 373
#define S_FOG_TYPE 374
#define S_VISIBILITY_RANGE 375
#define S_HORIZONTAL 376
#define S_JUSTIFY 377
#define S_LANGUAGE 378
#define S_LEFT2RIGHT 379
#define S_TOP2BOTTOM 380
#define IMAGE_TEXTURE 381
#define S_SOLID 382
#define S_KEY 383
#define S_KEYVALUE 384
#define S_REPEAT_S 385
#define S_REPEAT_T 386
#define S_CONVEX 387
#define S_BOTTOM 388
#define S_PICTH 389
#define S_COORD 390
#define S_COLOR_INDEX 391
#define S_COORD_INDEX 392
#define S_NORMAL_INDEX 393
#define S_MAX_POSITION 394
#define S_MIN_POSITION 395
#define S_ATTENUATION 396
#define S_APPEARANCE 397
#define S_GEOMETRY 398
#define S_DIRECT_OUTPUT 399
#define S_MUST_EVALUATE 400
#define S_MAX_BACK 401
#define S_MIN_BACK 402
#define S_MAX_FRONT 403
#define S_MIN_FRONT 404
#define S_PRIORITY 405
#define S_SOURCE 406
#define S_SPATIALIZE 407
#define S_BERM_WIDTH 408
#define S_CHOICE 409
#define S_WHICHCHOICE 410
#define S_FONTSTYLE 411
#define S_LENGTH 412
#define S_MAX_EXTENT 413
#define S_ROTATION 414
#define S_SCALE 415
#define S_CYCLE_INTERVAL 416
#define S_FIELD_OF_VIEW 417
#define S_JUMP 418
#define S_TITLE 419
#define S_TEXCOORD_INDEX 420
#define S_HEADLIGHT 421
#define S_TOP 422
#define S_BOTTOMRADIUS 423
#define S_HEIGHT 424
#define S_POINT 425
#define S_STRING 426
#define S_SPACING 427
#define S_TYPE 428
#define S_RADIUS 429
#define S_ON 430
#define S_INTENSITY 431
#define S_COLOR 432
#define S_DIRECTION 433
#define S_SIZE 434
#define S_FAMILY 435
#define S_STYLE 436
#define S_RANGE 437
#define S_CENTER 438
#define S_TRANSLATION 439
#define S_LEVEL 440
#define S_DIFFUSECOLOR 441
#define S_SPECULARCOLOR 442
#define S_EMISSIVECOLOR 443
#define S_SHININESS 444
#define S_TRANSPARENCY 445
#define S_VECTOR 446
#define S_POSITION 447
#define S_ORIENTATION 448
#define S_LOCATION 449
#define S_CUTOFFANGLE 450
#define S_WHICHCHILD 451
#define S_IMAGE 452
#define S_SCALEORIENTATION 453
#define S_DESCRIPTION 454




/* Copy the first part of user declarations.  */


/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

#if ! defined (YYSTYPE) && ! defined (YYSTYPE_IS_DECLARED)

typedef union YYSTYPE {
bool     bval;
int      ival;
float    fval;
char     *sval;
} YYSTYPE;
/* Line 191 of yacc.c.  */

# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */



#include <iostream>
#include <cstdlib>
#include <cassert>
#include <vector>
using namespace std;

#include <mesh/mesh.h>
#include <mesh/vrml.h>
#include <math/vector3.h>
#include <math/point.h>

#include <glt/color.h>

#ifndef alloca
#define alloca  malloc
#endif

typedef char    *VrmlSFString;
typedef float   VrmlSFFloat;
typedef float   VrmlSFFloat2[2];
typedef float   VrmlSFFloat3[3];
typedef float   VrmlSFFloat4[4];
typedef int     VrmlSFInt32;
typedef float   VrmlSFVec2f[2];
typedef float   VrmlSFVec4f[4];
typedef bool    VrmlSFBool;
typedef float   VrmlSFRotation[4];
typedef double  VrmlSFTime;
typedef float   VrmlSFMatrix[4][4];

VrmlSFVec2f     gVec2f;
Vector          gVec3f;
VrmlSFRotation  gRotation;
int             gWidth;
int             gHeight;
int             gComponents;

static MFInt32 _vectorInt32;
static MFVec3f _vectorVector;

//

static GltColor          _color;
static MaterialPtr       _material;
static IndexedFaceSetPtr _faceSet;

//

void (*VrmlParseMaterial)      (MaterialPtr       &material) = NULL;
void (*VrmlParseIndexedFaceSet)(IndexedFaceSetPtr &faceSet)  = NULL;
void (*VrmlParseShape)         (GltShapePtr           &shape)    = NULL;

//

int yyerror(const char *s);
int yyparseVrml(void);
int Vrmllex(void);

Mesh *yyVrmlMesh = 0;



/* Line 214 of yacc.c.  */


#if ! defined (yyoverflow) || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# if YYSTACK_USE_ALLOCA
#  define YYSTACK_ALLOC alloca
# else
#  ifndef YYSTACK_USE_ALLOCA
#   if defined (alloca) || defined (_ALLOCA_H)
#    define YYSTACK_ALLOC alloca
#   else
#    ifdef __GNUC__
#     define YYSTACK_ALLOC __builtin_alloca
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning. */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
# else
#  if defined (__STDC__) || defined (__cplusplus)
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   define YYSIZE_T size_t
#  endif
#  define YYSTACK_ALLOC malloc
#  define YYSTACK_FREE free
# endif
#endif /* ! defined (yyoverflow) || YYERROR_VERBOSE */


#if (! defined (yyoverflow) \
     && (! defined (__cplusplus) \
     || (YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  short yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (short) + sizeof (YYSTYPE))             \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)      \
      do                    \
    {                   \
      register YYSIZE_T yyi;        \
      for (yyi = 0; yyi < (Count); yyi++)   \
        (To)[yyi] = (From)[yyi];        \
    }                   \
      while (0)
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)                    \
    do                                  \
      {                                 \
    YYSIZE_T yynewbytes;                        \
    YYCOPY (&yyptr->Stack, Stack, yysize);              \
    Stack = &yyptr->Stack;                      \
    yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
    yyptr += yynewbytes / sizeof (*yyptr);              \
      }                                 \
    while (0)

#endif

#if defined (__STDC__) || defined (__cplusplus)
   typedef signed char yysigned_char;
#else
   typedef short yysigned_char;
#endif

/* YYFINAL -- State number of the termination state. */
#define YYFINAL  127
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1685

/* YYNTOKENS -- Number of terminals. */
#define YYNTOKENS  205
/* YYNNTS -- Number of nonterminals. */
#define YYNNTS  305
/* YYNRULES -- Number of rules. */
#define YYNRULES  667
/* YYNRULES -- Number of states. */
#define YYNSTATES  1086

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   454

#define YYTRANSLATE(YYX)                        \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const unsigned char yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,   202,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   200,     2,   201,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   203,     2,   204,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   146,   147,   148,   149,   150,   151,   152,   153,   154,
     155,   156,   157,   158,   159,   160,   161,   162,   163,   164,
     165,   166,   167,   168,   169,   170,   171,   172,   173,   174,
     175,   176,   177,   178,   179,   180,   181,   182,   183,   184,
     185,   186,   187,   188,   189,   190,   191,   192,   193,   194,
     195,   196,   197,   198,   199
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const unsigned short yyprhs[] =
{
       0,     0,     3,     5,     7,     9,    12,    13,    15,    17,
      19,    21,    23,    25,    27,    29,    31,    33,    35,    37,
      39,    41,    43,    45,    47,    49,    51,    53,    55,    57,
      59,    61,    63,    65,    67,    69,    71,    73,    75,    77,
      79,    81,    83,    85,    87,    89,    91,    93,    95,    97,
      99,   101,   103,   105,   107,   109,   111,   113,   115,   117,
     119,   121,   123,   125,   127,   129,   131,   133,   135,   137,
     139,   143,   148,   151,   155,   157,   161,   162,   163,   166,
     171,   174,   179,   181,   185,   187,   191,   193,   197,   199,
     202,   206,   209,   211,   214,   218,   221,   223,   226,   230,
     233,   235,   238,   242,   245,   247,   250,   254,   257,   259,
     262,   266,   269,   271,   274,   278,   281,   283,   286,   290,
     292,   296,   299,   300,   302,   304,   307,   310,   312,   315,
     318,   321,   323,   325,   327,   332,   335,   336,   339,   342,
     345,   348,   351,   354,   357,   360,   362,   367,   370,   371,
     373,   376,   379,   382,   385,   388,   391,   393,   398,   401,
     402,   404,   406,   408,   410,   412,   414,   416,   418,   420,
     422,   425,   428,   431,   434,   437,   440,   443,   446,   449,
     452,   454,   459,   462,   463,   465,   468,   470,   472,   474,
     479,   482,   483,   486,   488,   493,   494,   496,   499,   503,
     505,   510,   513,   516,   517,   519,   521,   524,   526,   528,
     531,   533,   538,   541,   542,   545,   547,   552,   555,   556,
     558,   560,   563,   566,   568,   573,   576,   577,   580,   583,
     586,   589,   591,   596,   599,   600,   603,   604,   607,   612,
     615,   618,   619,   622,   625,   627,   632,   635,   636,   639,
     642,   645,   648,   651,   653,   658,   661,   662,   665,   668,
     671,   674,   677,   680,   682,   687,   690,   691,   694,   697,
     700,   703,   706,   708,   713,   716,   717,   719,   722,   725,
     728,   731,   734,   737,   740,   743,   746,   749,   752,   755,
     758,   761,   764,   767,   769,   774,   777,   778,   780,   782,
     784,   786,   789,   792,   795,   798,   801,   804,   807,   810,
     813,   816,   818,   823,   826,   827,   830,   833,   836,   838,
     843,   846,   847,   849,   852,   855,   858,   861,   864,   867,
     870,   873,   876,   879,   883,   886,   887,   889,   891,   893,
     896,   897,   900,   905,   908,   911,   912,   914,   917,   920,
     923,   925,   930,   933,   934,   937,   940,   943,   946,   949,
     950,   953,   954,   960,   963,   964,   967,   970,   973,   976,
     979,   982,   985,   986,   989,   990,   996,   999,  1001,  1003,
    1005,  1007,  1010,  1011,  1014,  1017,  1020,  1023,  1026,  1029,
    1032,  1035,  1038,  1041,  1044,  1047,  1050,  1053,  1056,  1057,
    1060,  1061,  1067,  1070,  1073,  1074,  1077,  1080,  1083,  1086,
    1089,  1092,  1096,  1099,  1100,  1102,  1105,  1107,  1109,  1111,
    1116,  1119,  1120,  1122,  1124,  1127,  1130,  1133,  1138,  1140,
    1145,  1148,  1149,  1151,  1154,  1157,  1160,  1163,  1166,  1169,
    1172,  1174,  1179,  1182,  1183,  1185,  1187,  1190,  1193,  1196,
    1199,  1202,  1204,  1209,  1212,  1213,  1216,  1218,  1223,  1226,
    1227,  1230,  1233,  1235,  1240,  1243,  1244,  1247,  1250,  1252,
    1257,  1260,  1261,  1266,  1269,  1272,  1275,  1277,  1282,  1285,
    1286,  1289,  1292,  1295,  1298,  1301,  1303,  1308,  1311,  1312,
    1315,  1318,  1321,  1324,  1327,  1330,  1333,  1335,  1340,  1343,
    1344,  1347,  1350,  1353,  1356,  1358,  1363,  1366,  1367,  1370,
    1373,  1375,  1380,  1383,  1384,  1387,  1390,  1393,  1395,  1400,
    1403,  1404,  1407,  1410,  1412,  1417,  1420,  1421,  1423,  1426,
    1429,  1432,  1434,  1439,  1442,  1443,  1446,  1449,  1452,  1455,
    1458,  1461,  1464,  1467,  1470,  1473,  1476,  1479,  1481,  1486,
    1489,  1490,  1493,  1495,  1500,  1503,  1504,  1507,  1510,  1513,
    1515,  1520,  1523,  1524,  1527,  1530,  1533,  1536,  1539,  1542,
    1545,  1548,  1551,  1554,  1556,  1561,  1564,  1565,  1567,  1570,
    1575,  1578,  1581,  1582,  1585,  1590,  1593,  1596,  1597,  1599,
    1601,  1604,  1607,  1610,  1613,  1615,  1620,  1623,  1624,  1627,
    1629,  1634,  1637,  1638,  1641,  1644,  1647,  1650,  1652,  1657,
    1660,  1661,  1664,  1667,  1670,  1673,  1676,  1679,  1680,  1683,
    1688,  1691,  1694,  1695,  1698,  1700,  1705,  1708,  1709,  1711,
    1714,  1717,  1720,  1723,  1726,  1728,  1730,  1732,  1735,  1736,
    1739,  1744,  1747,  1750,  1751,  1754,  1757,  1760,  1763,  1766,
    1769,  1770,  1773,  1778,  1781,  1784,  1785,  1788,  1791,  1794,
    1796,  1801,  1804,  1805,  1807,  1810,  1813,  1815
};

/* YYRHS -- A `-1'-separated list of the rules' RHS. */
static const short yyrhs[] =
{
     206,     0,    -1,   207,    -1,     1,    -1,    26,    -1,   214,
     207,    -1,    -1,   248,    -1,   274,    -1,   286,    -1,   347,
      -1,   383,    -1,   389,    -1,   468,    -1,   496,    -1,   296,
      -1,   308,    -1,   408,    -1,   412,    -1,   433,    -1,   441,
      -1,   316,    -1,   421,    -1,   458,    -1,   437,    -1,   487,
      -1,   491,    -1,   503,    -1,   251,    -1,   342,    -1,   352,
      -1,   364,    -1,   394,    -1,   417,    -1,   482,    -1,   278,
      -1,   300,    -1,   312,    -1,   325,    -1,   333,    -1,   374,
      -1,   378,    -1,   429,    -1,   454,    -1,   474,    -1,   320,
      -1,   462,    -1,   425,    -1,   256,    -1,   270,    -1,   337,
      -1,   342,    -1,   509,    -1,   400,    -1,   501,    -1,   509,
      -1,   446,    -1,   358,    -1,   450,    -1,   209,    -1,   213,
      -1,   210,    -1,   208,    -1,     4,    -1,     3,    -1,     6,
      -1,     5,    -1,     4,    -1,     5,    -1,     4,    -1,   218,
     218,   218,    -1,   218,   218,   218,   218,    -1,   218,   218,
      -1,   218,   218,   218,    -1,   220,    -1,   200,   235,   201,
      -1,    -1,    -1,   225,   215,    -1,   225,   200,   232,   201,
      -1,   226,   223,    -1,   226,   200,   237,   201,    -1,   218,
      -1,   200,   233,   201,    -1,   217,    -1,   200,   234,   201,
      -1,   222,    -1,   200,   236,   201,    -1,   215,    -1,   232,
     215,    -1,   232,   202,   215,    -1,   232,   202,    -1,   218,
      -1,   233,   218,    -1,   233,   202,   218,    -1,   233,   202,
      -1,   217,    -1,   234,   217,    -1,   234,   202,   217,    -1,
     234,   202,    -1,   220,    -1,   235,   220,    -1,   235,   202,
     220,    -1,   235,   202,    -1,   222,    -1,   236,   222,    -1,
     236,   202,   222,    -1,   236,   202,    -1,   223,    -1,   237,
     223,    -1,   237,   202,   223,    -1,   237,   202,    -1,   215,
      -1,   238,   215,    -1,   238,   202,   215,    -1,   238,   202,
      -1,   221,    -1,   221,   202,    -1,   221,   202,   239,    -1,
     221,    -1,   200,   239,   201,    -1,   246,   241,    -1,    -1,
      70,    -1,    71,    -1,   102,   223,    -1,   101,   223,    -1,
     281,    -1,   199,   217,    -1,   242,   230,    -1,   243,   230,
      -1,   244,    -1,   245,    -1,     8,    -1,   247,   203,   241,
     204,    -1,   211,   249,    -1,    -1,    72,    20,    -1,    72,
     364,    -1,    74,    20,    -1,    74,   352,    -1,    74,   394,
      -1,    74,   417,    -1,    73,    20,    -1,    73,   482,    -1,
       9,    -1,   250,   203,   249,   204,    -1,   254,   252,    -1,
      -1,    71,    -1,   199,   217,    -1,    75,   216,    -1,   134,
     218,    -1,    76,   219,    -1,    77,   219,    -1,   253,   230,
      -1,    10,    -1,   255,   203,   252,   204,    -1,   268,   257,
      -1,    -1,    82,    -1,    83,    -1,    84,    -1,    85,    -1,
      86,    -1,    87,    -1,    78,    -1,    79,    -1,    88,    -1,
      89,    -1,   264,   229,    -1,   265,   224,    -1,   258,   230,
      -1,   259,   230,    -1,   260,   230,    -1,   261,   230,    -1,
     262,   230,    -1,   263,   230,    -1,   266,   229,    -1,   267,
     224,    -1,    11,    -1,   269,   203,   257,   204,    -1,   272,
     271,    -1,    -1,   281,    -1,    90,   223,    -1,   244,    -1,
     245,    -1,    12,    -1,   273,   203,   271,   204,    -1,   276,
     275,    -1,    -1,   179,   223,    -1,    13,    -1,   277,   203,
     275,   204,    -1,    -1,   280,    -1,   279,   280,    -1,   279,
     202,   280,    -1,   214,    -1,    69,   200,   279,   201,    -1,
      69,   279,    -1,   284,   282,    -1,    -1,    93,    -1,   281,
      -1,    91,   216,    -1,   244,    -1,   245,    -1,   283,   214,
      -1,    14,    -1,   285,   203,   282,   204,    -1,   288,   287,
      -1,    -1,   177,   224,    -1,    15,    -1,   289,   203,   287,
     204,    -1,   294,   291,    -1,    -1,   128,    -1,   129,    -1,
     292,   229,    -1,   293,   224,    -1,    16,    -1,   295,   203,
     291,   204,    -1,   298,   297,    -1,    -1,    94,   216,    -1,
     133,   216,    -1,   168,   218,    -1,   169,   218,    -1,    21,
      -1,   299,   203,   297,   204,    -1,   170,   228,    -1,    -1,
      65,     7,    -1,    -1,   302,    17,    -1,   303,   203,   301,
     204,    -1,    66,     7,    -1,   306,   305,    -1,    -1,   292,
     229,    -1,   293,   228,    -1,    18,    -1,   307,   203,   305,
     204,    -1,   310,   309,    -1,    -1,    94,   216,    -1,   133,
     216,    -1,   167,   216,    -1,   174,   218,    -1,   169,   218,
      -1,    23,    -1,   311,   203,   309,   204,    -1,   314,   313,
      -1,    -1,    95,   216,    -1,    96,   218,    -1,    97,   216,
      -1,    98,   218,    -1,    99,   218,    -1,   100,   218,    -1,
      19,    -1,   315,   203,   313,   204,    -1,   318,   317,    -1,
      -1,   175,   216,    -1,   176,   218,    -1,   177,   220,    -1,
     178,   223,    -1,   104,   218,    -1,    24,    -1,   319,   203,
     317,   204,    -1,   323,   321,    -1,    -1,   169,    -1,   177,
      20,    -1,   177,   290,    -1,   105,    20,    -1,   105,   404,
      -1,   106,    20,    -1,   106,   478,    -1,   322,   229,    -1,
     107,   216,    -1,   109,   218,    -1,   127,   216,    -1,   108,
     216,    -1,   110,   216,    -1,   111,   215,    -1,   112,   218,
      -1,   113,   215,    -1,   114,   218,    -1,    28,    -1,   324,
     203,   321,   204,    -1,   331,   326,    -1,    -1,   116,    -1,
     193,    -1,   160,    -1,   118,    -1,   115,   216,    -1,   107,
     216,    -1,   132,   216,    -1,   109,   218,    -1,   127,   216,
      -1,   327,   231,    -1,   117,   216,    -1,   328,   240,    -1,
     329,   231,    -1,   330,   228,    -1,    27,    -1,   332,   203,
     326,   204,    -1,   335,   334,    -1,    -1,   177,   220,    -1,
     119,   217,    -1,   120,   218,    -1,    29,    -1,   336,   203,
     334,   204,    -1,   340,   338,    -1,    -1,   122,    -1,   180,
     217,    -1,   121,   216,    -1,   339,   230,    -1,   123,   217,
      -1,   124,   216,    -1,   179,   218,    -1,   172,   218,    -1,
     181,   217,    -1,   125,   216,    -1,    25,   203,    -1,   341,
     338,   204,    -1,   344,   343,    -1,    -1,   281,    -1,   244,
      -1,   245,    -1,    65,     7,    -1,    -1,   345,    34,    -1,
     346,   203,   343,   204,    -1,    66,     7,    -1,   350,   348,
      -1,    -1,    71,    -1,   349,   230,    -1,   130,   216,    -1,
     131,   216,    -1,   126,    -1,   351,   203,   348,   204,    -1,
     353,   354,    -1,    -1,   142,    20,    -1,   142,   211,    -1,
     143,    20,    -1,   143,   212,    -1,    65,     7,    -1,    -1,
     355,    45,    -1,    -1,   356,   203,   353,   204,   357,    -1,
     360,   359,    -1,    -1,   104,   218,    -1,   186,   220,    -1,
     188,   220,    -1,   189,   218,    -1,   187,   220,    -1,   190,
     218,    -1,    65,     7,    -1,    -1,   361,    39,    -1,    -1,
     362,   203,   359,   204,   363,    -1,    66,     7,    -1,   136,
      -1,   137,    -1,   138,    -1,   165,    -1,   370,   369,    -1,
      -1,   177,   290,    -1,   135,   304,    -1,   105,   404,    -1,
     106,   478,    -1,   107,   216,    -1,   132,   216,    -1,   127,
     216,    -1,   109,   218,    -1,   108,   216,    -1,   110,   216,
      -1,   366,   227,    -1,   367,   227,    -1,   365,   227,    -1,
     368,   227,    -1,    65,     7,    -1,    -1,   371,    35,    -1,
      -1,   372,   203,   369,   204,   373,    -1,    66,     7,    -1,
     376,   375,    -1,    -1,   177,   290,    -1,   135,   304,    -1,
     108,   216,    -1,   365,   227,    -1,   366,   227,    -1,    36,
     203,    -1,   377,   375,   204,    -1,   381,   379,    -1,    -1,
      71,    -1,   380,   230,    -1,   244,    -1,   245,    -1,    30,
      -1,   382,   203,   379,   204,    -1,   387,   384,    -1,    -1,
     182,    -1,   185,    -1,   385,   229,    -1,   183,   223,    -1,
     386,   214,    -1,   386,   200,   207,   201,    -1,    38,    -1,
     388,   203,   384,   204,    -1,   392,   390,    -1,    -1,    71,
      -1,    75,   216,    -1,    80,   218,    -1,    76,   219,    -1,
      77,   219,    -1,   391,   230,    -1,   130,   216,    -1,   131,
     216,    -1,    31,    -1,   393,   203,   390,   204,    -1,   398,
     395,    -1,    -1,    81,    -1,   173,    -1,   396,   229,    -1,
     166,   216,    -1,    80,   218,    -1,   397,   230,    -1,   103,
     218,    -1,    32,    -1,   399,   203,   395,   204,    -1,   402,
     401,    -1,    -1,   191,   228,    -1,    40,    -1,   403,   203,
     401,   204,    -1,   406,   405,    -1,    -1,   292,   229,    -1,
     293,   228,    -1,    58,    -1,   407,   203,   405,   204,    -1,
     410,   409,    -1,    -1,   292,   229,    -1,   293,   240,    -1,
      59,    -1,   411,   203,   409,   204,    -1,   415,   413,    -1,
      -1,   197,     4,     4,     4,    -1,   414,   238,    -1,   130,
     216,    -1,   131,   216,    -1,    33,    -1,   416,   203,   413,
     204,    -1,   419,   418,    -1,    -1,    95,   216,    -1,    97,
     216,    -1,   139,   222,    -1,   140,   222,    -1,   100,   223,
      -1,    63,    -1,   420,   203,   418,   204,    -1,   423,   422,
      -1,    -1,   104,   218,    -1,   141,   223,    -1,   177,   220,
      -1,   176,   218,    -1,   194,   223,    -1,   175,   216,    -1,
     174,   218,    -1,    60,    -1,   424,   203,   422,   204,    -1,
     427,   426,    -1,    -1,   177,    20,    -1,   177,   290,    -1,
     135,    20,    -1,   135,   304,    -1,    61,    -1,   428,   203,
     426,   204,    -1,   431,   430,    -1,    -1,   292,   229,    -1,
     293,   228,    -1,    41,    -1,   432,   203,   430,   204,    -1,
     435,   434,    -1,    -1,   183,   223,    -1,   179,   223,    -1,
      97,   216,    -1,    42,    -1,   436,   203,   434,   204,    -1,
     439,   438,    -1,    -1,   292,   229,    -1,   293,   229,    -1,
      43,    -1,   440,   203,   438,   204,    -1,   444,   442,    -1,
      -1,    71,    -1,   443,   230,    -1,   144,   216,    -1,   145,
     216,    -1,    44,    -1,   445,   203,   442,   204,    -1,   448,
     447,    -1,    -1,   178,   223,    -1,   176,   218,    -1,   194,
     223,    -1,   146,   218,    -1,   148,   218,    -1,   147,   218,
      -1,   149,   218,    -1,   150,   218,    -1,   151,    20,    -1,
     151,   256,    -1,   151,   394,    -1,   152,   216,    -1,    46,
      -1,   449,   203,   447,   204,    -1,   452,   451,    -1,    -1,
     174,   218,    -1,    62,    -1,   453,   203,   451,   204,    -1,
     456,   455,    -1,    -1,    95,   216,    -1,    97,   216,    -1,
     100,   221,    -1,    48,    -1,   457,   203,   455,   204,    -1,
     460,   459,    -1,    -1,   104,   218,    -1,   141,   223,    -1,
     153,   218,    -1,   177,   220,    -1,   195,   218,    -1,   178,
     223,    -1,   176,   218,    -1,   194,   223,    -1,   175,   216,
      -1,   174,   218,    -1,    47,    -1,   461,   203,   459,   204,
      -1,   465,   463,    -1,    -1,   154,    -1,   464,   214,    -1,
     464,   200,   207,   201,    -1,   155,   215,    -1,    65,     7,
      -1,    -1,   466,    53,    -1,   467,   203,   463,   204,    -1,
      66,     7,    -1,   472,   469,    -1,    -1,   171,    -1,   157,
      -1,   470,   230,    -1,   156,   342,    -1,   471,   229,    -1,
     158,   218,    -1,    49,    -1,   473,   203,   469,   204,    -1,
     476,   475,    -1,    -1,   170,   231,    -1,    50,    -1,   477,
     203,   475,   204,    -1,   480,   479,    -1,    -1,   183,   222,
      -1,   159,   218,    -1,   160,   222,    -1,   184,   222,    -1,
      51,    -1,   481,   203,   479,   204,    -1,   484,   483,    -1,
      -1,   161,   219,    -1,    97,   216,    -1,    75,   216,    -1,
      76,   219,    -1,    77,   219,    -1,    65,     7,    -1,    -1,
     485,    52,    -1,   486,   203,   483,   204,    -1,    66,     7,
      -1,   489,   488,    -1,    -1,    97,   216,    -1,    54,    -1,
     490,   203,   488,   204,    -1,   493,   492,    -1,    -1,   281,
      -1,   183,   223,    -1,   159,   221,    -1,   160,   223,    -1,
     198,   221,    -1,   184,   223,    -1,   244,    -1,   245,    -1,
     496,    -1,    65,     7,    -1,    -1,   494,    64,    -1,   495,
     203,   492,   204,    -1,    66,     7,    -1,   498,   497,    -1,
      -1,   162,   218,    -1,   163,   216,    -1,   193,   221,    -1,
     192,   223,    -1,   199,   217,    -1,    65,     7,    -1,    -1,
     499,    55,    -1,   500,   203,   497,   204,    -1,    66,     7,
      -1,   503,   502,    -1,    -1,   183,   223,    -1,    97,   216,
      -1,   179,   223,    -1,    56,    -1,   504,   203,   502,   204,
      -1,   507,   505,    -1,    -1,    37,    -1,   506,   230,    -1,
     164,   217,    -1,    57,    -1,   508,   203,   505,   204,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned short yyrline[] =
{
       0,   128,   128,   129,   130,   134,   135,   139,   140,   141,
     142,   143,   144,   145,   146,   150,   151,   152,   153,   154,
     155,   159,   160,   161,   162,   163,   164,   165,   169,   170,
     171,   172,   173,   174,   175,   179,   180,   181,   182,   183,
     184,   185,   186,   187,   188,   192,   193,   194,   198,   199,
     200,   201,   202,   203,   204,   205,   206,   207,   208,   209,
     210,   211,   212,   215,   218,   221,   224,   227,   233,   234,
     237,   245,   266,   273,   276,   277,   281,   282,   285,   286,
     289,   290,   293,   294,   297,   298,   301,   302,   313,   314,
     315,   316,   319,   320,   321,   322,   325,   326,   327,   328,
     331,   332,   333,   334,   337,   338,   339,   340,   343,   344,
     345,   346,   349,   350,   351,   352,   357,   358,   359,   363,
     364,   374,   375,   379,   385,   391,   397,   403,   404,   408,
     411,   414,   415,   419,   425,   437,   438,   442,   443,   444,
     445,   446,   447,   448,   449,   453,   459,   471,   472,   476,
     482,   485,   488,   491,   494,   497,   503,   509,   521,   522,
     526,   532,   538,   544,   550,   556,   562,   568,   574,   580,
     586,   589,   592,   595,   598,   601,   604,   607,   610,   613,
     619,   625,   637,   638,   642,   643,   646,   647,   651,   657,
     669,   670,   674,   680,   686,   698,   699,   700,   701,   704,
     707,   708,   718,   719,   723,   729,   730,   733,   734,   735,
     741,   747,   759,   760,   764,   768,   774,   786,   787,   791,
     797,   803,   806,   812,   818,   830,   831,   835,   838,   841,
     844,   850,   856,   868,   869,   873,   874,   877,   883,   884,
     893,   894,   898,   901,   907,   913,   925,   926,   930,   933,
     936,   939,   942,   948,   954,   966,   967,   971,   974,   977,
     980,   983,   986,   993,   999,  1011,  1012,  1016,  1019,  1022,
    1025,  1028,  1034,  1040,  1052,  1053,  1057,  1064,  1065,  1066,
    1067,  1068,  1069,  1070,  1073,  1076,  1079,  1082,  1085,  1088,
    1091,  1094,  1097,  1103,  1109,  1121,  1122,  1126,  1132,  1138,
    1144,  1150,  1153,  1156,  1159,  1162,  1165,  1168,  1171,  1174,
    1177,  1183,  1189,  1201,  1202,  1206,  1209,  1212,  1218,  1224,
    1236,  1237,  1241,  1247,  1250,  1253,  1256,  1259,  1262,  1265,
    1268,  1271,  1277,  1283,  1295,  1296,  1300,  1301,  1302,  1306,
    1307,  1310,  1313,  1314,  1323,  1324,  1328,  1334,  1337,  1340,
    1346,  1352,  1364,  1365,  1368,  1369,  1370,  1371,  1375,  1376,
    1379,  1391,  1403,  1415,  1416,  1419,  1420,  1421,  1422,  1423,
    1424,  1427,  1428,  1431,  1442,  1448,  1449,  1459,  1462,  1465,
    1468,  1471,  1472,  1475,  1476,  1477,  1478,  1479,  1480,  1481,
    1482,  1483,  1484,  1485,  1486,  1487,  1488,  1491,  1492,  1495,
    1506,  1520,  1521,  1530,  1531,  1535,  1536,  1537,  1540,  1543,
    1549,  1555,  1567,  1568,  1572,  1578,  1581,  1582,  1586,  1592,
    1604,  1605,  1609,  1616,  1622,  1625,  1628,  1631,  1637,  1643,
    1655,  1656,  1660,  1666,  1669,  1672,  1675,  1678,  1681,  1684,
    1690,  1696,  1708,  1709,  1713,  1719,  1725,  1728,  1731,  1734,
    1737,  1743,  1749,  1761,  1762,  1766,  1770,  1776,  1791,  1792,
    1796,  1799,  1805,  1811,  1823,  1824,  1828,  1831,  1837,  1843,
    1855,  1856,  1860,  1866,  1869,  1872,  1878,  1884,  1896,  1897,
    1901,  1904,  1907,  1910,  1913,  1919,  1925,  1938,  1939,  1943,
    1946,  1949,  1952,  1955,  1958,  1961,  1967,  1973,  1985,  1986,
    1990,  1991,  1992,  1993,  1998,  2003,  2014,  2015,  2019,  2022,
    2028,  2034,  2046,  2047,  2051,  2054,  2057,  2063,  2069,  2081,
    2082,  2086,  2089,  2095,  2101,  2113,  2114,  2118,  2124,  2127,
    2130,  2136,  2142,  2154,  2155,  2159,  2162,  2165,  2168,  2171,
    2174,  2177,  2180,  2183,  2184,  2185,  2186,  2192,  2198,  2210,
    2211,  2215,  2221,  2227,  2239,  2240,  2244,  2247,  2250,  2256,
    2262,  2274,  2275,  2279,  2282,  2285,  2288,  2291,  2294,  2297,
    2300,  2303,  2306,  2312,  2318,  2330,  2331,  2335,  2341,  2344,
    2347,  2353,  2354,  2357,  2360,  2361,  2370,  2371,  2375,  2381,
    2387,  2390,  2391,  2392,  2399,  2405,  2417,  2418,  2422,  2427,
    2433,  2445,  2446,  2450,  2453,  2456,  2459,  2466,  2472,  2484,
    2485,  2489,  2492,  2495,  2498,  2501,  2507,  2508,  2511,  2514,
    2515,  2524,  2525,  2529,  2535,  2541,  2553,  2554,  2558,  2559,
    2562,  2565,  2568,  2571,  2574,  2575,  2576,  2580,  2581,  2584,
    2587,  2588,  2597,  2598,  2602,  2603,  2604,  2605,  2606,  2609,
    2610,  2613,  2616,  2617,  2626,  2627,  2631,  2634,  2637,  2643,
    2649,  2661,  2662,  2666,  2672,  2675,  2681,  2687
};
#endif

#if YYDEBUG || YYERROR_VERBOSE
/* YYTNME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals. */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "TRUEFALSE", "NUMBER", "AFLOAT", "STRING",
  "NAME", "ANCHOR", "APPEARANCE", "AUDIOCLIP", "BACKGROUND", "BILLBOARD",
  "BOX", "COLLISION", "COLOR", "COLOR_INTERP", "COORDINATE",
  "COORDINATE_INTERP", "CYLINDER_SENSOR", "NULL_STRING", "CONE", "CUBE",
  "CYLINDER", "DIRECTIONALLIGHT", "FONTSTYLE", "AERROR", "EXTRUSION",
  "ELEVATION_GRID", "FOG", "INLINE", "MOVIE_TEXTURE", "NAVIGATION_INFO",
  "PIXEL_TEXTURE", "GROUP_NODE", "INDEXEDFACESET", "INDEXEDLINESET",
  "S_INFO", "LOD", "MATERIAL", "NORMAL", "POSITION_INTERP",
  "PROXIMITY_SENSOR", "SCALAR_INTERP", "SCRIPT", "SHAPE", "SOUND",
  "SPOTLIGHT", "SPHERE_SENSOR", "ATEXT", "TEXTURE_COORDINATE",
  "TEXTURE_TRANSFORM", "TIME_SENSOR", "SWITCH", "TOUCH_SENSOR",
  "VIEWPOINT", "VISIBILITY_SENSOR", "WORLD_INFO", "NORMAL_INTERP",
  "ORIENTATION_INTERP", "POINTLIGHT", "POINTSET", "SPHERE",
  "PLANE_SENSOR", "TRANSFORM", "DEF", "USE", "PROTO", "ROUTE",
  "S_CHILDREN", "S_PARAMETER", "S_URL", "S_MATERIAL",
  "S_TEXTURETRANSFORM", "S_TEXTURE", "S_LOOP", "S_STARTTIME",
  "S_STOPTIME", "S_GROUNDANGLE", "S_GROUNDCOLOR", "S_SPEED",
  "S_AVATAR_SIZE", "S_BACKURL", "S_BOTTOMURL", "S_FRONTURL", "S_LEFTURL",
  "S_RIGHTURL", "S_TOPURL", "S_SKYANGLE", "S_SKYCOLOR",
  "S_AXIS_OF_ROTATION", "S_COLLIDE", "S_COLLIDETIME", "S_PROXY", "S_SIDE",
  "S_AUTO_OFFSET", "S_DISK_ANGLE", "S_ENABLED", "S_MAX_ANGLE",
  "S_MIN_ANGLE", "S_OFFSET", "S_BBOXSIZE", "S_BBOXCENTER",
  "S_VISIBILITY_LIMIT", "S_AMBIENT_INTENSITY", "AS_NORMAL", "S_TEXCOORD",
  "S_CCW", "S_COLOR_PER_VERTEX", "S_CREASE_ANGLE", "S_NORMAL_PER_VERTEX",
  "S_XDIMENSION", "S_XSPACING", "S_ZDIMENSION", "S_ZSPACING",
  "S_BEGIN_CAP", "S_CROSS_SECTION", "S_END_CAP", "S_SPINE", "S_FOG_TYPE",
  "S_VISIBILITY_RANGE", "S_HORIZONTAL", "S_JUSTIFY", "S_LANGUAGE",
  "S_LEFT2RIGHT", "S_TOP2BOTTOM", "IMAGE_TEXTURE", "S_SOLID", "S_KEY",
  "S_KEYVALUE", "S_REPEAT_S", "S_REPEAT_T", "S_CONVEX", "S_BOTTOM",
  "S_PICTH", "S_COORD", "S_COLOR_INDEX", "S_COORD_INDEX",
  "S_NORMAL_INDEX", "S_MAX_POSITION", "S_MIN_POSITION", "S_ATTENUATION",
  "S_APPEARANCE", "S_GEOMETRY", "S_DIRECT_OUTPUT", "S_MUST_EVALUATE",
  "S_MAX_BACK", "S_MIN_BACK", "S_MAX_FRONT", "S_MIN_FRONT", "S_PRIORITY",
  "S_SOURCE", "S_SPATIALIZE", "S_BERM_WIDTH", "S_CHOICE", "S_WHICHCHOICE",
  "S_FONTSTYLE", "S_LENGTH", "S_MAX_EXTENT", "S_ROTATION", "S_SCALE",
  "S_CYCLE_INTERVAL", "S_FIELD_OF_VIEW", "S_JUMP", "S_TITLE",
  "S_TEXCOORD_INDEX", "S_HEADLIGHT", "S_TOP", "S_BOTTOMRADIUS",
  "S_HEIGHT", "S_POINT", "S_STRING", "S_SPACING", "S_TYPE", "S_RADIUS",
  "S_ON", "S_INTENSITY", "S_COLOR", "S_DIRECTION", "S_SIZE", "S_FAMILY",
  "S_STYLE", "S_RANGE", "S_CENTER", "S_TRANSLATION", "S_LEVEL",
  "S_DIFFUSECOLOR", "S_SPECULARCOLOR", "S_EMISSIVECOLOR", "S_SHININESS",
  "S_TRANSPARENCY", "S_VECTOR", "S_POSITION", "S_ORIENTATION",
  "S_LOCATION", "S_CUTOFFANGLE", "S_WHICHCHILD", "S_IMAGE",
  "S_SCALEORIENTATION", "S_DESCRIPTION", "'['", "']'", "','", "'{'",
  "'}'", "$accept", "Vrml", "VrmlNodes", "GroupingNode",
  "InterpolationNode", "SensorElement", "AppearanceNode", "GeometryNode",
  "LightNode", "SFNode", "SFInt32", "SFBool", "SFString", "SFFloat",
  "SFTime", "SFColor", "SFRotation", "SFVec2f", "SFVec3f", "MFColor",
  "clearIntList", "clearVec3fList", "MFInt32", "MFVec3f", "MFFloat",
  "MFString", "MFVec2f", "SFInt32List", "SFFloatList", "SFStringList",
  "SFColorList", "SFVec2fList", "SFVec3fList", "SFImageList",
  "SFRotationList", "MFRotation", "AnchorElements",
  "AnchorElementParameterBegin", "AnchorElementURLBegin", "bboxCenter",
  "bboxSize", "AnchorElement", "AnchorBegin", "Anchor", "AppearanceNodes",
  "AppearanceBegin", "Appearance", "AudioClipElements", "AudioClipURL",
  "AudioClipElement", "AudioClipBegin", "AudioClip", "BackGroundElements",
  "BackGroundBackURL", "BackGroundBottomURL", "BackGroundFrontURL",
  "BackGroundLeftURL", "BackGroundRightURL", "BackGroundTopURL",
  "BackGroundGroundAngle", "BackGroundGroundColor", "BackGroundSkyAngle",
  "BackGroundSkyColor", "BackGroundElement", "BackgroundBegin",
  "Background", "BillboardElements", "BillboardElement", "BillboardBegin",
  "Billboard", "BoxElements", "BoxElement", "BoxBegin", "Box",
  "childrenElements", "childrenElement", "children", "CollisionElements",
  "CollisionElementProxyBegin", "CollisionElement", "CollisionBegin",
  "Collision", "ColorElements", "ColorElement", "ColorBegin", "Color",
  "ColorInterpElements", "InterpolateKey", "InterporlateKeyValue",
  "ColorInterpElement", "ColorInterpBegin", "ColorInterp", "ConeElements",
  "ConeElement", "ConeBegin", "Cone", "CoordinateElements",
  "CoordinateDef", "CoordinateBegin", "Coordinate",
  "CoordinateInterpElements", "CoordinateInterpElement",
  "CoordinateInterpBegin", "CoordinateInterp", "CylinderElements",
  "CylinderElement", "CylinderBegin", "Cylinder",
  "CylinderSensorElements", "CylinderSensorElement",
  "CylinderSensorBegin", "CylinderSensor", "DirLightElements",
  "DirLightElement", "DirLightBegin", "DirLight", "ElevationGridElements",
  "ElevationGridHeight", "ElevationGridElement", "ElevationGridBegin",
  "ElevationGrid", "ExtrusionElements", "ExtrusionCrossSection",
  "ExtrusionOrientation", "ExtrusionScale", "ExtrusionSpine",
  "ExtrusionElement", "ExtrusionBegin", "Extrusion", "FogElements",
  "FogElement", "FogBegin", "Fog", "FontStyleElements",
  "FontStyleJustify", "FontStyleElement", "FontStyleBegin", "FontStyle",
  "GroupElements", "GroupElement", "GroupDef", "GroupBegin", "Group",
  "ImgTexElements", "ImgTexURL", "ImgTexElement", "ImageTextureBegin",
  "ImageTexture", "ShapeElements", "ShapeElement", "ShapeDef",
  "ShapeBegin", "ShapeEnd", "Shape", "MaterialElements",
  "MaterialElement", "MaterialDef", "MaterialBegin", "MaterialEnd",
  "Material", "ColorIndex", "CoordIndex", "NormalIndex", "TextureIndex",
  "IdxFaceSetElements", "IdxFaceSetElement", "IdxFaceSetDef",
  "IdxFaceSetBegin", "IdxFaceSetEnd", "IdxFaceSet", "IdxLineSetElements",
  "IdxLineSetElement", "IdxLineSetBegin", "IdxLineSet", "InlineElements",
  "InlineURL", "InlineElement", "InlineBegin", "Inline", "LodElements",
  "LodRange", "LodLevel", "LodElement", "LodBegin", "Lod",
  "MovieTextureElements", "MovieTextureURL", "MovieTextureElement",
  "MovieTextureBegin", "MovieTexture", "NavigationInfoElements",
  "NavigationInfoAvatarSize", "NavigationInfoType",
  "NavigationInfoElement", "NavigationInfoBegin", "NavigationInfo",
  "NormalElements", "NormalElement", "NormalBegin", "Normal",
  "NormalInterpElements", "NormalInterpElement", "NormalInterpBegin",
  "NormalInterp", "OrientationInterpElements", "OrientationInterpElement",
  "OrientationInterpBegin", "OrientationInterp", "PixelTextureElements",
  "PixelTextureImage", "PixelTextureElement", "PixelTextureBegin",
  "PixelTexture", "PlaneSensorElements", "PlaneSensorElement",
  "PlaneSensorBegin", "PlaneSensor", "PointLightNodes", "PointLightNode",
  "PointLightBegin", "PointLight", "PointSetElements", "PointSetElement",
  "PointSetBegin", "PointSet", "PositionInterpElements",
  "PositionInterpElement", "PositionInterpBegin", "PositionInterp",
  "ProximitySensorElements", "ProximitySensorElement",
  "ProximitySensorBegin", "ProximitySensor", "ScalarInterpElements",
  "ScalarInterpElement", "ScalarInterpBegin", "ScalarInterp",
  "ScriptElements", "ScriptURL", "ScriptElement", "ScriptBegin", "Script",
  "SoundElements", "SoundElement", "SoundBegin", "Sound",
  "SphereElements", "SphereElement", "SphereBegin", "Sphere",
  "SphereSensorElements", "SphereSensorElement", "SphereSensorBegin",
  "SphereSensor", "SpotLightElements", "SpotLightElement",
  "SpotLightBegin", "SpotLight", "SwitchElements", "SwitchChoice",
  "SwitchElement", "SwitchDef", "SwitchBegin", "Switch", "TextElements",
  "TextString", "TextLength", "TextElement", "TextBegin", "Text",
  "TexCoordElements", "TexCoordElement", "TexCoordBegin", "TexCoordinate",
  "TextureTransformElements", "TextureTransformElement",
  "TexTransformBegin", "TexTransform", "TimeSensorElements",
  "TimeSensorElement", "TimeSensorDef", "TimeSensorBegin", "TimeSensor",
  "TouchSensorElements", "TouchSensorElement", "TouchSensorBegin",
  "TouchSensor", "TransformElements", "TransformElement", "TransformDef",
  "TransformBegin", "Transform", "ViewpointElements", "ViewpointElement",
  "ViewpointDef", "ViewpointBegin", "Viewpoint", "VisibilitySensors",
  "VisibilitySensor", "VisibilitySensorBegine", "WorldInfoElements",
  "WorldInfoInfo", "WorldInfoElement", "WorldInfoBegin", "WorldInfo", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const unsigned short yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,   357,   358,   359,   360,   361,   362,   363,   364,
     365,   366,   367,   368,   369,   370,   371,   372,   373,   374,
     375,   376,   377,   378,   379,   380,   381,   382,   383,   384,
     385,   386,   387,   388,   389,   390,   391,   392,   393,   394,
     395,   396,   397,   398,   399,   400,   401,   402,   403,   404,
     405,   406,   407,   408,   409,   410,   411,   412,   413,   414,
     415,   416,   417,   418,   419,   420,   421,   422,   423,   424,
     425,   426,   427,   428,   429,   430,   431,   432,   433,   434,
     435,   436,   437,   438,   439,   440,   441,   442,   443,   444,
     445,   446,   447,   448,   449,   450,   451,   452,   453,   454,
      91,    93,    44,   123,   125
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const unsigned short yyr1[] =
{
       0,   205,   206,   206,   206,   207,   207,   208,   208,   208,
     208,   208,   208,   208,   208,   209,   209,   209,   209,   209,
     209,   210,   210,   210,   210,   210,   210,   210,   211,   211,
     211,   211,   211,   211,   211,   212,   212,   212,   212,   212,
     212,   212,   212,   212,   212,   213,   213,   213,   214,   214,
     214,   214,   214,   214,   214,   214,   214,   214,   214,   214,
     214,   214,   214,   215,   216,   217,   218,   218,   219,   219,
     220,   221,   222,   223,   224,   224,   225,   226,   227,   227,
     228,   228,   229,   229,   230,   230,   231,   231,   232,   232,
     232,   232,   233,   233,   233,   233,   234,   234,   234,   234,
     235,   235,   235,   235,   236,   236,   236,   236,   237,   237,
     237,   237,   238,   238,   238,   238,   239,   239,   239,   240,
     240,   241,   241,   242,   243,   244,   245,   246,   246,   246,
     246,   246,   246,   247,   248,   249,   249,   211,   211,   211,
     211,   211,   211,   211,   211,   250,   251,   252,   252,   253,
     254,   254,   254,   254,   254,   254,   255,   256,   257,   257,
     258,   259,   260,   261,   262,   263,   264,   265,   266,   267,
     268,   268,   268,   268,   268,   268,   268,   268,   268,   268,
     269,   270,   271,   271,   272,   272,   272,   272,   273,   274,
     275,   275,   276,   277,   278,   279,   279,   279,   279,   280,
     281,   281,   282,   282,   283,   284,   284,   284,   284,   284,
     285,   286,   287,   287,   288,   289,   290,   291,   291,   292,
     293,   294,   294,   295,   296,   297,   297,   298,   298,   298,
     298,   299,   300,   301,   301,   302,   302,   303,   304,   304,
     305,   305,   306,   306,   307,   308,   309,   309,   310,   310,
     310,   310,   310,   311,   312,   313,   313,   314,   314,   314,
     314,   314,   314,   315,   316,   317,   317,   318,   318,   318,
     318,   318,   319,   320,   321,   321,   322,   323,   323,   323,
     323,   323,   323,   323,   323,   323,   323,   323,   323,   323,
     323,   323,   323,   324,   325,   326,   326,   327,   328,   329,
     330,   331,   331,   331,   331,   331,   331,   331,   331,   331,
     331,   332,   333,   334,   334,   335,   335,   335,   336,   337,
     338,   338,   339,   340,   340,   340,   340,   340,   340,   340,
     340,   340,   341,   342,   343,   343,   344,   344,   344,   345,
     345,   346,   347,   347,   348,   348,   349,   350,   350,   350,
     351,   352,   353,   353,   354,   354,   354,   354,   355,   355,
     356,   357,   358,   359,   359,   360,   360,   360,   360,   360,
     360,   361,   361,   362,   363,   364,   364,   365,   366,   367,
     368,   369,   369,   370,   370,   370,   370,   370,   370,   370,
     370,   370,   370,   370,   370,   370,   370,   371,   371,   372,
     373,   374,   374,   375,   375,   376,   376,   376,   376,   376,
     377,   378,   379,   379,   380,   381,   381,   381,   382,   383,
     384,   384,   385,   386,   387,   387,   387,   387,   388,   389,
     390,   390,   391,   392,   392,   392,   392,   392,   392,   392,
     393,   394,   395,   395,   396,   397,   398,   398,   398,   398,
     398,   399,   400,   401,   401,   402,   403,   404,   405,   405,
     406,   406,   407,   408,   409,   409,   410,   410,   411,   412,
     413,   413,   414,   415,   415,   415,   416,   417,   418,   418,
     419,   419,   419,   419,   419,   420,   421,   422,   422,   423,
     423,   423,   423,   423,   423,   423,   424,   425,   426,   426,
     427,   427,   427,   427,   428,   429,   430,   430,   431,   431,
     432,   433,   434,   434,   435,   435,   435,   436,   437,   438,
     438,   439,   439,   440,   441,   442,   442,   443,   444,   444,
     444,   445,   446,   447,   447,   448,   448,   448,   448,   448,
     448,   448,   448,   448,   448,   448,   448,   449,   450,   451,
     451,   452,   453,   454,   455,   455,   456,   456,   456,   457,
     458,   459,   459,   460,   460,   460,   460,   460,   460,   460,
     460,   460,   460,   461,   462,   463,   463,   464,   465,   465,
     465,   466,   466,   467,   468,   468,   469,   469,   470,   471,
     472,   472,   472,   472,   473,   474,   475,   475,   476,   477,
     478,   479,   479,   480,   480,   480,   480,   481,   482,   483,
     483,   484,   484,   484,   484,   484,   485,   485,   486,   487,
     487,   488,   488,   489,   490,   491,   492,   492,   493,   493,
     493,   493,   493,   493,   493,   493,   493,   494,   494,   495,
     496,   496,   497,   497,   498,   498,   498,   498,   498,   499,
     499,   500,   501,   501,   502,   502,   503,   503,   503,   504,
     503,   505,   505,   506,   507,   507,   508,   509
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const unsigned char yyr2[] =
{
       0,     2,     1,     1,     1,     2,     0,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     4,     2,     3,     1,     3,     0,     0,     2,     4,
       2,     4,     1,     3,     1,     3,     1,     3,     1,     2,
       3,     2,     1,     2,     3,     2,     1,     2,     3,     2,
       1,     2,     3,     2,     1,     2,     3,     2,     1,     2,
       3,     2,     1,     2,     3,     2,     1,     2,     3,     1,
       3,     2,     0,     1,     1,     2,     2,     1,     2,     2,
       2,     1,     1,     1,     4,     2,     0,     2,     2,     2,
       2,     2,     2,     2,     2,     1,     4,     2,     0,     1,
       2,     2,     2,     2,     2,     2,     1,     4,     2,     0,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       1,     4,     2,     0,     1,     2,     1,     1,     1,     4,
       2,     0,     2,     1,     4,     0,     1,     2,     3,     1,
       4,     2,     2,     0,     1,     1,     2,     1,     1,     2,
       1,     4,     2,     0,     2,     1,     4,     2,     0,     1,
       1,     2,     2,     1,     4,     2,     0,     2,     2,     2,
       2,     1,     4,     2,     0,     2,     0,     2,     4,     2,
       2,     0,     2,     2,     1,     4,     2,     0,     2,     2,
       2,     2,     2,     1,     4,     2,     0,     2,     2,     2,
       2,     2,     2,     1,     4,     2,     0,     2,     2,     2,
       2,     2,     1,     4,     2,     0,     1,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     1,     4,     2,     0,     1,     1,     1,
       1,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     1,     4,     2,     0,     2,     2,     2,     1,     4,
       2,     0,     1,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     3,     2,     0,     1,     1,     1,     2,
       0,     2,     4,     2,     2,     0,     1,     2,     2,     2,
       1,     4,     2,     0,     2,     2,     2,     2,     2,     0,
       2,     0,     5,     2,     0,     2,     2,     2,     2,     2,
       2,     2,     0,     2,     0,     5,     2,     1,     1,     1,
       1,     2,     0,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     0,     2,
       0,     5,     2,     2,     0,     2,     2,     2,     2,     2,
       2,     3,     2,     0,     1,     2,     1,     1,     1,     4,
       2,     0,     1,     1,     2,     2,     2,     4,     1,     4,
       2,     0,     1,     2,     2,     2,     2,     2,     2,     2,
       1,     4,     2,     0,     1,     1,     2,     2,     2,     2,
       2,     1,     4,     2,     0,     2,     1,     4,     2,     0,
       2,     2,     1,     4,     2,     0,     2,     2,     1,     4,
       2,     0,     4,     2,     2,     2,     1,     4,     2,     0,
       2,     2,     2,     2,     2,     1,     4,     2,     0,     2,
       2,     2,     2,     2,     2,     2,     1,     4,     2,     0,
       2,     2,     2,     2,     1,     4,     2,     0,     2,     2,
       1,     4,     2,     0,     2,     2,     2,     1,     4,     2,
       0,     2,     2,     1,     4,     2,     0,     1,     2,     2,
       2,     1,     4,     2,     0,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     1,     4,     2,
       0,     2,     1,     4,     2,     0,     2,     2,     2,     1,
       4,     2,     0,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     1,     4,     2,     0,     1,     2,     4,
       2,     2,     0,     2,     4,     2,     2,     0,     1,     1,
       2,     2,     2,     2,     1,     4,     2,     0,     2,     1,
       4,     2,     0,     2,     2,     2,     2,     1,     4,     2,
       0,     2,     2,     2,     2,     2,     2,     0,     2,     4,
       2,     2,     0,     2,     1,     4,     2,     0,     1,     2,
       2,     2,     2,     2,     1,     1,     1,     2,     0,     2,
       4,     2,     2,     0,     2,     2,     2,     2,     2,     2,
       0,     2,     4,     2,     2,     0,     2,     2,     2,     1,
       4,     2,     0,     1,     2,     2,     1,     4
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const unsigned short yydefact[] =
{
       0,     3,   133,   156,   180,   188,   210,   223,   244,   263,
     272,     0,     4,   318,   418,   451,   428,   510,   517,   523,
     531,   547,   573,   559,   624,   659,   666,   462,   468,   496,
     485,     0,     0,     0,     0,     0,     0,     2,    62,    59,
      61,    60,     6,     0,     7,     0,    48,     0,    49,     0,
       8,     0,     9,     0,    15,     0,    16,     0,    21,     0,
      45,     0,    50,   321,    51,     0,     0,    10,     0,     0,
      57,     0,    11,     0,    12,     0,    53,     0,    17,     0,
      18,     0,    22,     0,    47,     0,    19,     0,    24,     0,
      20,     0,    56,     0,    58,     0,    23,     0,    46,     0,
       0,    13,     0,     0,    25,     0,    26,     0,     0,    14,
       0,     0,    54,    27,     0,     0,    52,   332,   339,   343,
      64,   657,    67,    66,     0,   658,   656,     1,     5,   122,
     148,   159,   183,   203,   218,   241,   256,   266,   314,     0,
     322,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     321,   341,   335,   360,   353,   413,   421,   443,   459,   465,
     479,   488,   507,   513,   520,   526,   534,   555,   562,   583,
     576,   618,   610,   622,   639,   627,   651,   643,   655,   662,
       0,   195,   123,   124,     0,     0,     0,     0,     0,     0,
     131,   132,   122,   127,   149,     0,     0,     0,     0,     0,
       0,     0,   148,   166,   167,   160,   161,   162,   163,   164,
     165,   168,   169,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   159,     0,   186,   187,     0,   183,
     184,     0,   204,   207,   208,   205,     0,   340,   203,   219,
     220,     0,     0,     0,   218,     0,    77,     0,   241,     0,
       0,     0,     0,     0,     0,     0,   256,     0,     0,     0,
       0,     0,     0,   266,     0,     0,     0,     0,   314,   324,
      65,   326,   327,   331,   329,   328,   323,   330,   333,     0,
      84,   325,   320,   337,   338,   336,     0,   335,     0,   414,
     416,   417,     0,     0,   413,   422,     0,   423,     0,     0,
     340,   421,     0,   444,     0,     0,   445,     0,     0,     0,
     443,     0,    77,     0,   459,     0,     0,     0,   465,     0,
       0,     0,     0,     0,     0,   479,     0,     0,     0,     0,
       0,     0,     0,     0,   488,     0,    77,     0,   507,     0,
       0,     0,     0,   513,     0,     0,     0,   520,   527,     0,
       0,     0,     0,   526,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   534,     0,     0,     0,     0,
     555,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   562,   577,     0,     0,   340,   576,     0,     0,
       0,     0,     0,     0,   610,     0,     0,   622,     0,     0,
       0,     0,     0,     0,     0,   634,   635,   628,     0,   627,
     636,     0,     0,     0,     0,     0,     0,   643,     0,   655,
     663,     0,     0,     0,   662,    73,   195,   199,   201,   196,
     126,   125,   128,   134,   129,   130,   121,   151,    69,    68,
     153,   154,   152,   150,   157,   155,   147,   181,   172,   173,
     174,   175,   176,   177,     0,    82,   170,     0,     0,    74,
     171,   178,   179,   158,   185,   189,   182,   206,   211,   209,
     202,   224,   221,   222,   217,   242,     0,   243,   245,   240,
     257,   258,   259,   260,   261,   262,   264,   255,   271,   267,
     268,   269,   270,   273,   265,   316,   317,   315,   319,   313,
      96,     0,   342,   334,   372,   398,   361,   352,   419,   415,
     412,   425,   429,   424,     6,   426,   420,   448,   450,   447,
     452,   446,   449,   442,   460,   461,   463,   458,   466,     0,
       0,   119,   467,   469,   464,   480,   481,   484,     0,   482,
     483,   486,   478,   489,   490,   495,   494,   492,   491,   493,
     497,   487,   508,   509,   511,   506,   516,   515,   514,   518,
     512,   521,   522,   524,   519,   529,   530,   532,   528,   525,
     538,   540,   539,   541,   542,   543,   440,   544,     0,   545,
     546,   536,   535,   537,   548,   533,   556,   557,   558,   560,
     554,   563,   564,   565,   572,   571,   569,   566,   568,   570,
     567,   574,   561,    63,   580,   584,     6,   578,   575,   613,
     614,   615,   612,   611,   619,   609,   623,   625,   621,   637,
     641,   630,   631,   629,   633,   632,   640,   626,   644,   645,
     647,   646,   648,   652,   642,   660,   654,   665,   667,   664,
     661,   340,   340,   197,    92,     0,   100,     0,     0,     0,
      80,    85,    99,    97,   145,   354,   476,   607,     0,     0,
     372,     0,     0,   350,   355,     0,    28,    29,     0,    30,
       0,     0,    31,    32,     0,    33,     0,    34,   193,   356,
     231,   253,   311,   293,     0,   594,   504,   552,     0,     0,
     357,     0,    35,     0,    36,     0,    37,     0,    38,     0,
      39,     0,     0,    40,   404,    41,     0,    42,     0,    43,
       0,    44,   362,     0,   116,     0,     0,    72,   431,     0,
     200,   198,    83,    95,    93,    75,   103,   101,    70,   108,
       0,    98,   371,   376,   137,   138,   143,   144,   139,   140,
     141,   142,   136,   345,   373,   364,   471,   602,   410,   397,
     402,   191,   226,   247,   275,   296,   399,   382,     0,   236,
     377,   378,     0,    76,    76,     0,   404,   499,   550,   587,
     427,   117,   120,     0,   432,     0,     0,     0,     0,     0,
       0,     0,     0,   431,   579,    94,   102,    81,   111,   109,
     136,     0,   346,     0,     0,     0,     0,   345,     0,     0,
       0,     0,     0,     0,     0,   364,     0,     0,     0,     0,
       0,   471,     0,     0,     0,     0,     0,   602,     0,     0,
     191,     0,     0,     0,     0,     0,   226,     0,     0,     0,
       0,     0,     0,   247,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   276,     0,     0,     0,   275,
       0,     0,     0,   297,     0,   300,     0,     0,   299,   298,
       0,     0,     0,     0,    77,   296,     0,     0,     0,     0,
       0,     0,     0,     0,   236,   379,   380,     0,    76,    76,
      76,    76,     0,   382,   407,     0,     0,     0,     0,   406,
     215,     0,   405,     0,   408,   409,   411,   403,   236,     0,
       0,   499,     0,     0,   550,     0,   589,     0,   588,     0,
       0,     0,   587,   118,    71,   433,   435,   436,   434,   438,
     439,   441,   437,   430,   110,   135,   146,   348,   349,   351,
     347,   344,   365,   366,   369,   367,   368,   370,   374,   363,
     474,   475,     0,   477,   112,   473,   470,   604,   605,   603,
     606,   608,   601,   192,   194,   190,   227,   228,   229,   230,
     232,   225,   248,   249,   250,   252,   251,   254,   246,   279,
     456,     0,   280,   281,   599,     0,   282,   284,   287,   285,
     288,   289,   290,   291,   292,   286,   277,   278,   294,   283,
     274,   302,   304,   301,   307,   305,   303,   312,     0,    86,
     306,   308,   309,   310,   295,   385,   386,   387,   391,   390,
     392,   389,   388,   384,   383,   395,   393,   394,   396,   400,
     381,   235,   239,   237,   234,   213,     0,    78,   502,   503,
     500,   501,   505,   498,   551,   553,   549,   591,   593,   595,
     590,   592,   586,   375,     0,   115,   113,   454,   597,   104,
       0,   401,    77,     0,     0,     0,   213,    88,     0,   472,
     114,    77,     0,   454,     0,     0,   597,    87,   107,   105,
     233,   238,   214,   216,   212,    79,    91,    89,   455,   457,
     453,   598,   600,   596,   106,    90
};

/* YYDEFGOTO[NTERM-NUM]. */
static const short yydefgoto[] =
{
      -1,    36,    37,    38,    39,    40,   790,   690,    41,   427,
     604,   121,   280,   124,   440,   459,   531,   999,   125,   460,
     893,   476,   894,   477,   456,   281,  1000,  1058,   645,   501,
     647,  1050,   730,   945,   715,   532,   187,   188,   189,   190,
     191,   192,    43,    44,   791,   665,   666,   200,   201,   202,
      45,    46,   213,   214,   215,   216,   217,   218,   219,   220,
     221,   222,   223,   224,    47,    48,   228,   229,    49,    50,
     819,   820,   691,   692,   428,   429,   193,   236,   237,   238,
      51,    52,  1055,  1056,   891,   892,   241,   242,   243,   244,
      53,    54,   825,   826,   693,   694,  1053,   887,   888,   889,
     247,   248,    55,    56,   832,   833,   695,   696,   255,   256,
      57,    58,   262,   263,    59,    60,   847,   848,   849,   697,
     698,   860,   861,   862,   863,   864,   865,   699,   700,   267,
     268,    61,    62,   148,   149,   150,    63,    64,   286,   287,
      65,    66,    67,   795,   796,   797,   668,   669,   288,   507,
      68,    69,   712,    70,   804,   805,   670,   671,  1043,   672,
     763,   764,   880,   881,   882,   883,   701,   702,  1051,   703,
     765,   766,   704,   705,   292,   293,   294,    71,    72,   298,
     299,   300,   301,    73,    74,   781,   782,   783,   578,   673,
     307,   308,   309,   310,    75,    76,  1062,  1063,   971,   972,
     313,   314,    77,    78,   317,   318,    79,    80,   809,   810,
     811,   674,   675,   324,   325,    81,    82,   333,   334,    83,
      84,   900,   901,   706,   707,   337,   338,    85,    86,   342,
     343,    87,    88,   346,   347,    89,    90,   351,   352,   353,
      91,    92,   364,   365,    93,    94,   903,   904,   708,   709,
     369,   370,    95,    96,   381,   382,    97,    98,   385,   386,
     387,    99,   100,   101,   909,   910,   911,   912,   710,   711,
    1065,  1066,   975,   976,   816,   817,   676,   677,   393,   394,
     102,   103,   104,   396,   397,   105,   106,   408,   409,   107,
     108,   109,   416,   417,   110,   111,   112,   418,   113,   114,
     422,   423,   424,   115,   116
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -848
static const short yypact[] =
{
    1298,  -848,  -848,  -848,  -848,  -848,  -848,  -848,  -848,  -848,
    -848,  -152,  -848,  -848,  -848,  -848,  -848,  -848,  -848,  -848,
    -848,  -848,  -848,  -848,  -848,  -848,  -848,  -848,  -848,  -848,
    -848,    95,   120,   109,    90,    90,    85,  -848,  -848,  -848,
    -848,  -848,  1368,   -71,  -848,   -69,  -848,   -56,  -848,   -55,
    -848,    -6,  -848,    40,  -848,    58,  -848,    74,  -848,    76,
    -848,    88,  -848,   514,  -848,   145,   106,  -848,   156,   126,
    -848,   128,  -848,   152,  -848,   166,  -848,   186,  -848,   188,
    -848,   199,  -848,   204,  -848,   208,  -848,   219,  -848,   227,
    -848,   229,  -848,   247,  -848,   249,  -848,   256,  -848,   169,
     270,  -848,   246,   273,  -848,   274,  -848,   217,   278,  -848,
     440,   297,  -848,  -848,   301,   302,  -848,  -848,   567,  -848,
    -848,  -848,  -848,  -848,    90,  -848,  -848,  -848,  -848,   -30,
     289,   724,   503,   355,   135,   135,   573,   367,   -76,   109,
    -848,   361,   109,   109,    90,    90,   361,   361,   306,    42,
     514,  -848,   112,  -848,  -848,   269,   167,   -28,   135,   135,
     412,   210,   135,   -40,   135,    13,   648,    70,   292,  -848,
     163,  -848,   323,   416,  -848,   378,  -848,   327,    -7,    -2,
      90,  1191,  -848,  -848,    90,    90,   361,   311,    42,    42,
    -848,  -848,   -30,  -848,  -848,   109,   431,   431,    90,   361,
     318,    42,   289,  -848,  -848,  -848,  -848,  -848,  -848,  -848,
    -848,  -848,  -848,   321,    42,    42,    42,    42,    42,    42,
      60,    72,    60,    72,   724,    90,  -848,  -848,   325,   503,
    -848,   109,  -848,  -848,  -848,  -848,   326,  1442,   355,  -848,
    -848,   328,    60,    72,   135,    60,  -848,   331,   135,   109,
      90,   109,    90,    90,    90,   336,   573,    90,   109,    90,
      90,    90,   342,   367,   361,    90,    90,   346,   -76,  -848,
    -848,  -848,  -848,  -848,  -848,  -848,  -848,  -848,  -848,   361,
    -848,  -848,  -848,  -848,  -848,  -848,   356,   112,   -50,  -848,
    -848,  -848,   359,    42,   269,  -848,    90,  -848,   360,    60,
    1061,   167,    90,  -848,    90,   109,  -848,   362,    60,    42,
     -28,    60,  -848,   364,   135,    60,    78,   366,   135,   109,
     109,    90,    90,    90,   371,   412,    90,    90,    90,   109,
      90,    90,    90,   373,   210,    60,  -848,   374,   135,   109,
      90,    90,   375,   -40,    60,    60,   379,   135,  -848,   109,
     109,   386,    42,    13,    90,    90,    90,    90,    90,   348,
     109,    90,    90,    90,   387,   648,   109,   109,    90,   390,
      70,    90,    90,    90,    90,   109,    90,    90,    90,    90,
      90,   391,   292,  -848,   523,   394,  1121,   163,   109,   431,
     431,   109,   431,   396,   323,   109,   397,   416,   524,   558,
      90,    90,    90,    90,    90,  -848,  -848,  -848,   399,   378,
    -848,    90,   109,    90,    90,   361,   403,   327,   404,    -7,
    -848,   361,   405,    42,    -2,  -848,  1502,  -848,   969,  -848,
    -848,  -848,  -848,  -848,  -848,  -848,  -848,  -848,  -848,  -848,
    -848,  -848,  -848,  -848,  -848,  -848,  -848,  -848,  -848,  -848,
    -848,  -848,  -848,  -848,    90,  -848,  -848,    90,    90,  -848,
    -848,  -848,  -848,  -848,  -848,  -848,  -848,  -848,  -848,  -848,
    -848,  -848,  -848,  -848,  -848,  -848,   105,  -848,  -848,  -848,
    -848,  -848,  -848,  -848,  -848,  -848,  -848,  -848,  -848,  -848,
    -848,  -848,  -848,  -848,  -848,  -848,  -848,  -848,  -848,  -848,
    -848,    24,  -848,  -848,   508,   708,  -848,  -848,  -848,  -848,
    -848,  -848,  -848,  -848,  1368,  -848,  -848,  -848,  -848,  -848,
    -848,  -848,  -848,  -848,  -848,  -848,  -848,  -848,  -848,    90,
      90,  -848,  -848,  -848,  -848,  -848,  -848,  -848,    90,  -848,
    -848,  -848,  -848,  -848,  -848,  -848,  -848,  -848,  -848,  -848,
    -848,  -848,  -848,  -848,  -848,  -848,  -848,  -848,  -848,  -848,
    -848,  -848,  -848,  -848,  -848,  -848,  -848,  -848,  -848,  -848,
    -848,  -848,  -848,  -848,  -848,  -848,  -848,  -848,   410,  -848,
    -848,  -848,  -848,  -848,  -848,  -848,  -848,  -848,  -848,  -848,
    -848,  -848,  -848,  -848,  -848,  -848,  -848,  -848,  -848,  -848,
    -848,  -848,  -848,  -848,  -848,  -848,  1368,  -848,  -848,  -848,
    -848,  -848,  -848,  -848,  -848,  -848,  -848,  -848,  -848,  -848,
    -848,  -848,  -848,  -848,  -848,  -848,  -848,  -848,  -848,  -848,
    -848,  -848,  -848,  -848,  -848,  -848,  -848,  -848,  -848,  -848,
    -848,   909,  1442,  -848,  -848,    14,  -848,    82,    90,    90,
    -848,  -848,   361,  -848,  -848,  -848,  -848,  -848,   564,   611,
     291,    49,   235,  -848,  -848,   418,  -848,  -848,   422,  -848,
     591,   430,  -848,  -848,   438,  -848,   439,  -848,  -848,  -848,
    -848,  -848,  -848,  -848,   442,  -848,  -848,  -848,   636,   639,
    -848,   445,  -848,   447,  -848,   448,  -848,   449,  -848,   452,
    -848,   622,   481,  -848,   238,  -848,   482,  -848,   484,  -848,
     489,  -848,  -848,   495,   496,   500,    90,  -848,   552,   501,
    -848,  -848,  -848,    90,  -848,  -848,    90,  -848,  -848,  -848,
      84,  -848,  -848,  -848,  -848,  -848,  -848,  -848,  -848,  -848,
    -848,  -848,   388,   194,  -848,   368,   -24,   257,  -848,  -848,
    -848,   518,    50,   332,   553,   376,  -848,   479,   109,   398,
    -848,  -848,   688,  -848,  -848,   504,   238,   -99,   530,    32,
    -848,    90,  -848,    90,  -848,   109,   431,   431,    90,   109,
     109,   505,    42,   552,  -848,  -848,  -848,  -848,    90,  -848,
     388,   506,  -848,   109,   109,   507,    42,   194,    90,    90,
      90,    90,    90,    90,   509,   368,   109,   109,   711,   516,
     523,   -24,    90,    90,    90,    90,   519,   257,    90,   521,
     518,   109,   109,    90,    90,   522,    50,   109,   109,   109,
      90,    90,   528,   332,    91,   143,   109,   109,    90,   109,
     523,    90,   523,    90,   109,  -848,   280,   536,    60,   553,
     109,    90,   109,  -848,   109,  -848,   109,   109,  -848,  -848,
     538,   110,    78,   110,  -848,   376,   672,   668,   109,   109,
      90,   109,   109,   109,   398,  -848,  -848,   688,  -848,  -848,
    -848,  -848,   539,   479,  -848,   727,   738,   730,   545,  -848,
    -848,   546,  -848,    51,  -848,  -848,  -848,  -848,   315,   312,
     548,   -99,    90,   549,   530,   731,  -848,    90,  -848,   551,
      42,    60,    32,  -848,  -848,  -848,  -848,  -848,  -848,  -848,
    -848,  -848,  -848,  -848,  -848,  -848,  -848,  -848,  -848,  -848,
    -848,  -848,  -848,  -848,  -848,  -848,  -848,  -848,  -848,  -848,
    -848,  -848,   754,  -848,  -848,    33,  -848,  -848,  -848,  -848,
    -848,  -848,  -848,  -848,  -848,  -848,  -848,  -848,  -848,  -848,
    -848,  -848,  -848,  -848,  -848,  -848,  -848,  -848,  -848,  -848,
    -848,   556,  -848,  -848,  -848,   557,  -848,  -848,  -848,  -848,
    -848,  -848,  -848,  -848,  -848,  -848,  -848,  -848,  -848,  -848,
    -848,  -848,  -848,  -848,  -848,  -848,  -848,  -848,    90,  -848,
    -848,  -848,  -848,  -848,  -848,  -848,  -848,  -848,  -848,  -848,
    -848,  -848,  -848,  -848,  -848,  -848,  -848,  -848,  -848,  -848,
    -848,  -848,  -848,  -848,   592,   584,   523,  -848,  -848,  -848,
    -848,  -848,  -848,  -848,  -848,  -848,  -848,  -848,  -848,  -848,
    -848,  -848,  -848,  -848,   760,   523,  -848,   574,   596,  -848,
     118,  -848,  -848,   563,    72,   568,   584,  -848,    22,  -848,
    -848,  -848,   571,   574,   110,   572,   596,  -848,    90,  -848,
    -848,  -848,  -848,  -848,  -848,  -848,   523,  -848,  -848,  -848,
    -848,  -848,  -848,  -848,  -848,  -848
};

/* YYPGOTO[NTERM-NUM].  */
static const short yypgoto[] =
{
    -848,  -848,   -39,  -848,  -848,  -848,   264,  -848,  -848,     4,
    -737,    43,  -118,  -124,  -180,  -252,  -334,  -317,   -25,  -221,
    -848,  -848,  -537,  -311,  -195,  -156,  -847,  -848,  -848,  -848,
    -848,  -848,  -848,  -848,     0,   -85,   587,  -848,  -848,    19,
     107,  -848,  -848,  -848,   -10,  -848,  -848,   579,  -848,  -848,
    -848,   423,   560,  -848,  -848,  -848,  -848,  -848,  -848,  -848,
    -848,  -848,  -848,  -848,  -848,  -848,   559,  -848,  -848,  -848,
     -35,  -848,  -848,  -848,   363,  -413,  -121,   554,  -848,  -848,
    -848,  -848,  -270,  -848,  -848,  -722,   547,   111,   164,  -848,
    -848,  -848,   -36,  -848,  -848,  -848,  -848,  -848,  -848,  -807,
     566,  -848,  -848,  -848,   -29,  -848,  -848,  -848,   561,  -848,
    -848,  -848,   542,  -848,  -848,  -848,   -34,  -848,  -848,  -848,
    -848,   -49,  -848,  -848,  -848,  -848,  -848,  -848,  -848,   562,
    -848,  -848,  -848,   669,  -848,  -848,  -848,  -497,   533,  -848,
    -848,  -848,  -848,    28,  -848,  -848,  -848,   159,  -848,  -848,
    -848,  -848,  -848,  -848,    23,  -848,  -848,  -848,  -848,   171,
    -719,  -715,  -848,  -848,   -54,  -848,  -848,  -848,  -848,  -848,
      61,  -848,  -848,  -848,   540,  -848,  -848,  -848,  -848,   531,
    -848,  -848,  -848,  -848,  -848,    52,  -848,  -848,  -848,  -350,
     529,  -848,  -848,  -848,  -848,  -848,  -225,  -848,  -848,   -26,
     527,  -848,  -848,  -848,   525,  -848,  -848,  -848,    34,  -848,
    -848,  -848,   182,   526,  -848,  -848,  -848,   512,  -848,  -848,
    -848,   -53,  -848,  -848,  -848,   515,  -848,  -848,  -848,   511,
    -848,  -848,  -848,   510,  -848,  -848,  -848,   494,  -848,  -848,
    -848,  -848,   487,  -848,  -848,  -848,   -48,  -848,  -848,  -848,
     485,  -848,  -848,  -848,   476,  -848,  -848,  -848,   472,  -848,
    -848,  -848,  -848,  -848,   -52,  -848,  -848,  -848,  -848,  -848,
    -205,  -848,  -848,    -5,    46,  -848,  -848,   205,   473,  -848,
    -848,  -848,  -848,   471,  -848,  -848,  -848,   460,  -848,  -848,
    -848,  -151,   456,  -848,  -848,  -848,  -848,   457,  -165,  -848,
     451,  -848,  -848,  -848,  -848
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -651
static const short yytable[] =
{
     180,   525,   462,   128,    42,   539,   540,   667,   491,   579,
     126,   230,   235,   419,   497,   643,  1002,   441,   122,   123,
     274,   275,   473,   271,   410,   553,   603,   461,   276,   277,
     270,   285,   434,   435,   588,   420,   898,   603,   878,   181,
     182,   183,   879,   264,   265,   445,    42,   472,   270,    25,
     475,   117,   302,   303,   407,   603,   425,   339,   448,   449,
     450,   451,   452,   453,   122,   123,   621,  1013,   432,   736,
     625,   184,   185,   944,   442,   304,   122,   123,   899,   548,
     631,   443,   122,   123,   348,   127,   122,   123,   122,   123,
      33,  1029,   504,   505,   122,   123,   455,   458,   455,   458,
     657,   266,   118,   981,   513,   983,   806,   807,   230,   122,
     123,   969,   120,   521,   122,   123,   524,   235,   455,   458,
     528,   455,   122,   123,   987,   597,   481,   119,   483,   484,
     485,   970,   129,   488,   130,   490,   458,   509,   305,   340,
     552,   496,   458,   341,   821,   306,   495,   131,   132,   561,
     562,   226,   233,   522,   506,  1014,  1027,   349,   350,   430,
     431,   500,   421,   973,   878,   366,   285,   367,   879,   186,
     368,   283,    34,   808,   290,   455,    35,  1031,   517,   151,
     518,   181,   269,   822,   455,   272,   273,   455,   905,   906,
     907,   455,   530,   974,   405,   714,   568,   133,   538,   538,
     464,   153,   543,   908,   545,   646,   547,   458,  1046,   610,
     611,   455,   613,   184,   185,   722,   723,  1081,   823,   824,
     455,   455,   169,  1075,  1076,   651,   652,   895,   643,   721,
     570,   571,   572,   573,   574,  1045,   492,   581,   437,   227,
     234,   469,   279,   134,   530,   667,   245,   591,   226,   593,
     594,  1026,   596,   458,   419,   738,   600,   233,   410,   284,
     454,   135,   291,   239,   240,   792,   576,   639,   656,   311,
     315,   511,   457,   335,   467,   344,   530,   136,   529,   137,
     530,   174,   406,   725,   726,   787,   788,   628,   407,  1057,
     530,   138,   480,   667,   482,   890,   537,   632,   171,   246,
     986,   489,   544,   637,   515,   649,   283,   549,  1060,   152,
     998,   734,   740,   290,   326,   557,   558,   383,   384,  1067,
    1068,  1077,   312,   316,   793,   794,   336,   890,   345,   154,
     644,   155,  1030,   458,   648,  1028,   227,   582,   583,  1085,
     289,  1015,  1016,  1017,  1018,   234,   758,   592,   519,   295,
     296,   327,   297,   598,   599,   156,   658,   659,     3,   245,
     194,   663,   535,   536,   195,   196,   197,   270,   575,   157,
     184,   185,   546,   759,   760,   761,   622,   623,   624,   576,
     885,   886,   556,   653,   328,   329,   330,   331,   630,   158,
     607,   159,   565,   566,   284,   727,   371,   654,   388,   389,
     390,   291,   160,   580,   332,   530,   716,   161,  1037,   586,
     587,   162,   246,    11,   717,   762,   812,   813,   595,   576,
     391,   656,   163,   198,   181,   311,   827,  -372,   405,   315,
     164,   609,   165,   372,   612,   438,   439,   714,   616,   657,
     814,   815,  -638,   398,   399,   373,   231,   181,   232,   335,
     166,   650,   167,   658,   659,   629,   184,   185,   344,   168,
     660,   661,   662,   885,   886,   828,   374,   375,   376,   377,
     378,   257,   798,   170,   786,   713,   172,   173,   312,   184,
     185,   175,   316,   850,   392,   851,   379,   380,   199,   411,
     412,   852,   853,   854,   855,   176,   948,   949,   950,   829,
     177,   830,   336,   856,   178,   179,   831,   319,   857,   320,
     278,   345,   321,   395,   663,   433,   406,   654,    42,   413,
     414,   724,   444,   458,   728,   447,   415,   603,   655,   465,
     468,   619,   471,    11,   731,   478,   858,   400,   401,   576,
     486,   656,   258,   259,   260,   261,   493,   933,   934,   935,
     498,   322,   323,  1003,   799,   800,   801,   802,   803,   657,
     502,   402,   403,   508,   512,   620,   520,   719,   526,   859,
     533,   732,   181,   658,   659,   541,   404,   550,   554,   559,
     660,   661,   662,   563,   866,   867,   868,   869,   870,   871,
     567,   584,   773,   225,   589,   601,   916,   917,   605,   785,
     614,   617,   458,   626,   184,   185,   872,   633,   635,   638,
      42,   873,  -358,   718,   874,   760,   761,   875,   733,  -616,
    -581,   742,  -649,   774,   729,   743,   922,   775,   776,   777,
     744,  -637,   778,   745,   663,   139,   140,   141,   142,   143,
     930,   746,   747,   749,   876,   748,   750,   530,   751,   914,
     752,   753,   754,   989,   918,   755,   877,   756,   834,   835,
     836,   837,   838,   839,   840,   841,   842,   843,   249,   250,
     251,   252,   253,   254,   932,   458,   458,   458,   936,   937,
     844,  1049,   779,   780,   757,   767,   144,   768,   947,   538,
     538,   538,   769,   145,   146,   147,   770,   818,   771,   958,
     959,   772,   784,   890,   902,   789,   965,   966,   896,   921,
     926,   929,   970,   938,   979,   942,  1041,   982,   974,   984,
     943,   678,   845,   951,   455,   954,   960,   992,   679,   680,
     846,   681,   967,  1069,  1021,   682,   683,   538,   530,   538,
     988,  1070,   997,  1019,   684,  1022,  1009,  1023,  1024,  1025,
    1078,  1084,  1032,  1035,  1040,  1039,    11,   685,  1044,  1047,
    1048,  1054,  1052,   924,  1059,  1061,  1064,  1071,   664,   686,
     687,   913,  1073,   688,   689,  1079,  1082,  1001,  1034,   436,
     925,   446,   577,  1038,   463,   955,  1074,   455,   466,   641,
     961,   474,   470,   953,   354,   355,   356,   357,   358,   359,
     360,   884,   203,   204,   968,   494,   205,   206,   207,   208,
     209,   210,   211,   212,   479,   990,  1004,   487,   915,   282,
     503,   739,   919,   920,   361,   931,   362,   897,   939,  1020,
     499,   735,   516,  1072,   510,   923,   927,   928,  1080,   523,
    1005,   527,   363,   534,   741,   946,   551,   569,  1033,   940,
     941,   542,   585,   555,   560,   590,  1036,   564,   602,   608,
    1042,  1083,  1006,   952,   956,   957,   737,   615,   618,   627,
     962,   963,   964,   634,   538,   640,   636,     0,     0,   977,
     978,     0,   980,     0,     0,     0,     0,   985,     0,     0,
       0,     0,     0,   991,     0,   993,     0,   994,     0,   995,
     996,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  1007,  1008,     0,  1010,  1011,  1012,     2,     0,     3,
       4,     5,     0,     6,     0,     7,   538,     8,     9,     0,
     458,     0,     0,    10,    11,     0,     0,     0,    13,    14,
     538,    15,     0,     0,   538,     0,     0,    16,     0,     0,
      17,    18,    19,    20,  -359,    21,    22,    23,     0,     0,
       0,  -617,  -582,    24,  -650,    25,    26,    27,    28,    29,
       0,     0,    30,  -638,    31,    32,     0,     2,     0,     3,
       4,     5,     0,     6,     0,     7,     0,     8,     9,     0,
       0,     0,     0,    10,    11,     0,     0,     0,    13,    14,
       0,    15,     0,  -340,     0,     0,    33,    16,     0,     0,
      17,    18,    19,    20,  -359,    21,    22,    23,     0,     0,
       0,  -617,  -582,    24,  -650,    25,    26,    27,    28,    29,
       0,     0,    30,     0,    31,    32,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    33,     0,     0,     2,
       0,     3,     4,     5,     0,     6,     0,     7,     0,     8,
       9,     0,     0,     0,     0,    10,    11,     0,    34,     0,
      13,    14,    35,    15,     0,     0,     0,     0,     0,    16,
       0,     0,    17,    18,    19,    20,  -359,    21,    22,    23,
     720,   642,     0,  -617,  -582,    24,  -650,    25,    26,    27,
      28,    29,     0,     0,    30,  -638,    31,    32,     0,     2,
       0,     3,     4,     5,     0,     6,     0,     7,     0,     8,
       9,     0,     0,     0,     0,    10,    11,     0,    34,     0,
      13,    14,    35,    15,     0,     0,     0,     0,    33,    16,
       0,     0,    17,    18,    19,    20,  -359,    21,    22,    23,
       0,   642,     0,  -617,  -582,    24,  -650,    25,    26,    27,
      28,    29,     0,     0,    30,  -638,    31,    32,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     2,
       0,     3,     4,     5,     0,     6,     0,     7,     0,     8,
       9,     0,     0,     0,     0,    10,    11,     0,    33,     0,
      13,    14,     0,    15,     0,     0,     0,     0,     0,    16,
       0,     0,    17,    18,    19,    20,     0,    21,    22,    23,
      34,     0,     0,     0,    35,    24,     0,    25,    26,    27,
      28,    29,     0,     0,    30,     0,    31,    32,     0,     0,
       0,   514,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    33,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    -6,     1,
      34,     0,     0,     0,    35,     0,     2,     0,     3,     4,
       5,     0,     6,     0,     7,     0,     8,     9,     0,     0,
       0,   606,    10,    11,    12,     0,     0,    13,    14,     0,
      15,     0,  -340,     0,     0,     0,    16,     0,     0,    17,
      18,    19,    20,  -359,    21,    22,    23,     0,     0,     0,
    -617,  -582,    24,  -650,    25,    26,    27,    28,    29,     0,
       0,    30,  -638,    31,    32,     0,     0,     0,     0,     0,
      34,     0,     0,     0,    35,     0,     2,     0,     3,     4,
       5,     0,     6,     0,     7,     0,     8,     9,     0,     0,
       0,   426,    10,    11,     0,    33,     0,    13,    14,     0,
      15,     0,  -340,     0,     0,     0,    16,     0,     0,    17,
      18,    19,    20,  -359,    21,    22,    23,     0,     0,     0,
    -617,  -582,    24,  -650,    25,    26,    27,    28,    29,     0,
       0,    30,  -638,    31,    32,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       2,     0,     3,     4,     5,     0,     6,     0,     7,     0,
       8,     9,     0,     0,     0,    33,    10,    11,     0,     0,
       0,    13,    14,     0,    15,     0,     0,    34,     0,     0,
      16,    35,     0,    17,    18,    19,    20,  -359,    21,    22,
      23,     0,     0,     0,  -617,  -582,    24,  -650,    25,    26,
      27,    28,    29,     0,     0,    30,  -638,    31,    32,     0,
       2,     0,     3,     4,     5,     0,     6,     0,     7,     0,
       8,     9,     0,     0,     0,     0,    10,    11,     0,     0,
       0,    13,    14,     0,    15,     0,     0,     0,     0,    33,
      16,     0,     0,    17,    18,    19,    20,    34,    21,    22,
      23,    35,     0,     0,     0,     0,    24,     0,    25,    26,
      27,    28,    29,     0,     0,    30,     0,    31,    32,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    33,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    34,     0,     0,     0,    35,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    34,     0,     0,     0,    35
};

static const short yycheck[] =
{
     124,   312,   223,    42,     0,   322,   323,   504,   260,   359,
      35,   132,   133,   178,   266,   428,   863,   197,     4,     5,
     144,   145,   243,   141,   175,   336,     4,   222,   146,   147,
       6,   152,   188,   189,   368,    37,   135,     4,   757,    69,
      70,    71,   757,   119,   120,   201,    42,   242,     6,    56,
     245,   203,    80,    81,   175,     4,   180,    97,   214,   215,
     216,   217,   218,   219,     4,     5,   400,   874,   186,    20,
     404,   101,   102,   810,   198,   103,     4,     5,   177,   331,
     414,   199,     4,     5,    71,     0,     4,     5,     4,     5,
      97,   898,   142,   143,     4,     5,   220,   221,   222,   223,
      51,   177,     7,   840,   299,   842,   130,   131,   229,     4,
       5,    20,     3,   308,     4,     5,   311,   238,   242,   243,
     315,   245,     4,     5,   846,   377,   250,     7,   252,   253,
     254,    40,   203,   257,   203,   259,   260,   293,   166,   179,
     335,   265,   266,   183,    94,   173,   264,   203,   203,   344,
     345,   132,   133,   309,   204,   877,   893,   144,   145,   184,
     185,   279,   164,    20,   883,    95,   287,    97,   883,   199,
     100,   152,   179,   197,   155,   299,   183,   899,   302,    34,
     304,    69,   139,   133,   308,   142,   143,   311,   156,   157,
     158,   315,   316,    50,   175,   529,   352,   203,   322,   323,
     225,    45,   326,   171,   328,   457,   330,   331,   945,   389,
     390,   335,   392,   101,   102,   201,   202,  1064,   168,   169,
     344,   345,    53,   201,   202,   201,   202,   764,   641,   642,
     354,   355,   356,   357,   358,   202,   261,   361,   195,   132,
     133,   237,   200,   203,   368,   742,   135,   371,   229,   373,
     374,   200,   376,   377,   419,    20,   380,   238,   409,   152,
     200,   203,   155,   128,   129,    71,    31,   423,    33,   158,
     159,   296,   200,   162,   231,   164,   400,   203,   200,   203,
     404,    64,   175,   201,   202,   201,   202,   411,   409,  1026,
     414,   203,   249,   790,   251,    15,   321,   415,    52,   135,
      20,   258,   327,   421,   300,   200,   287,   332,  1045,   203,
     200,    20,   662,   294,   104,   340,   341,   154,   155,   201,
     202,  1058,   158,   159,   130,   131,   162,    15,   164,   203,
     454,   203,    20,   457,   458,    20,   229,   362,   363,  1076,
      71,   878,   879,   880,   881,   238,   108,   372,   305,   182,
     183,   141,   185,   378,   379,   203,    65,    66,    10,   248,
      71,   126,   319,   320,    75,    76,    77,     6,    20,   203,
     101,   102,   329,   135,   136,   137,   401,   402,   403,    31,
      65,    66,   339,   501,   174,   175,   176,   177,   413,   203,
     386,   203,   349,   350,   287,   647,   104,     9,    75,    76,
      77,   294,   203,   360,   194,   529,   530,   203,   905,   366,
     367,   203,   248,    25,   538,   177,   159,   160,   375,    31,
      97,    33,   203,   134,    69,   314,    94,    39,   409,   318,
     203,   388,   203,   141,   391,     4,     5,   771,   395,    51,
     183,   184,    64,    65,    66,   153,    91,    69,    93,   338,
     203,   476,   203,    65,    66,   412,   101,   102,   347,   203,
      72,    73,    74,    65,    66,   133,   174,   175,   176,   177,
     178,   104,   104,   203,   726,   514,   203,   203,   314,   101,
     102,   203,   318,   107,   161,   109,   194,   195,   199,   162,
     163,   115,   116,   117,   118,    55,   813,   814,   815,   167,
     203,   169,   338,   127,   203,   203,   174,    95,   132,    97,
     204,   347,   100,    97,   126,   204,   409,     9,   514,   192,
     193,   645,   204,   647,   648,   204,   199,     4,    20,   204,
     204,     7,   204,    25,   652,   204,   160,   159,   160,    31,
     204,    33,   175,   176,   177,   178,   204,   799,   800,   801,
     204,   139,   140,   864,   186,   187,   188,   189,   190,    51,
     204,   183,   184,   204,   204,     7,   204,   606,   204,   193,
     204,     7,    69,    65,    66,   204,   198,   204,   204,   204,
      72,    73,    74,   204,   105,   106,   107,   108,   109,   110,
     204,   204,   716,    90,   204,   204,   776,   777,   204,   723,
     204,   204,   726,   204,   101,   102,   127,   204,   204,   204,
     606,   132,    45,   203,   135,   136,   137,   138,     7,    52,
      53,   203,    55,    71,   649,   203,   782,    75,    76,    77,
      39,    64,    80,   203,   126,   121,   122,   123,   124,   125,
     796,   203,   203,     7,   165,   203,     7,   771,   203,   773,
     203,   203,   203,   848,   778,   203,   177,    35,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,    95,    96,
      97,    98,    99,   100,   798,   799,   800,   801,   802,   803,
     127,   998,   130,   131,   203,   203,   172,   203,   812,   813,
     814,   815,   203,   179,   180,   181,   201,   179,   202,   823,
     824,   201,   201,    15,   174,   730,   830,   831,   204,   204,
     204,   204,    40,   204,   838,     4,   911,   841,    50,   843,
     204,    13,   169,   204,   848,   204,   204,   851,    20,    21,
     177,    23,   204,  1050,     7,    27,    28,   861,   862,   863,
     204,  1052,   204,   204,    36,     7,   870,    17,   203,   203,
    1061,  1068,   204,   204,   910,   204,    25,    49,     4,   203,
     203,   177,   170,   788,     4,   191,   170,   204,   504,    61,
      62,   771,   204,    65,    66,   204,   204,   862,   902,   192,
     790,   202,   359,   907,   224,   820,  1056,   911,   229,   426,
     826,   244,   238,   818,   146,   147,   148,   149,   150,   151,
     152,   758,    78,    79,   833,   263,    82,    83,    84,    85,
      86,    87,    88,    89,   248,   849,   865,   256,   775,   150,
     287,   662,   779,   780,   176,   797,   178,   766,   805,   883,
     268,   660,   301,  1054,   294,   783,   793,   794,  1063,   310,
     866,   314,   194,   318,   662,   811,   334,   353,   901,   806,
     807,   325,   365,   338,   343,   370,   904,   347,   382,   387,
     912,  1066,   867,   817,   821,   822,   661,   394,   397,   409,
     827,   828,   829,   417,   998,   424,   419,    -1,    -1,   836,
     837,    -1,   839,    -1,    -1,    -1,    -1,   844,    -1,    -1,
      -1,    -1,    -1,   850,    -1,   852,    -1,   854,    -1,   856,
     857,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   868,   869,    -1,   871,   872,   873,     8,    -1,    10,
      11,    12,    -1,    14,    -1,    16,  1050,    18,    19,    -1,
    1054,    -1,    -1,    24,    25,    -1,    -1,    -1,    29,    30,
    1064,    32,    -1,    -1,  1068,    -1,    -1,    38,    -1,    -1,
      41,    42,    43,    44,    45,    46,    47,    48,    -1,    -1,
      -1,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      -1,    -1,    63,    64,    65,    66,    -1,     8,    -1,    10,
      11,    12,    -1,    14,    -1,    16,    -1,    18,    19,    -1,
      -1,    -1,    -1,    24,    25,    -1,    -1,    -1,    29,    30,
      -1,    32,    -1,    34,    -1,    -1,    97,    38,    -1,    -1,
      41,    42,    43,    44,    45,    46,    47,    48,    -1,    -1,
      -1,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      -1,    -1,    63,    -1,    65,    66,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    97,    -1,    -1,     8,
      -1,    10,    11,    12,    -1,    14,    -1,    16,    -1,    18,
      19,    -1,    -1,    -1,    -1,    24,    25,    -1,   179,    -1,
      29,    30,   183,    32,    -1,    -1,    -1,    -1,    -1,    38,
      -1,    -1,    41,    42,    43,    44,    45,    46,    47,    48,
     201,   202,    -1,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    -1,    -1,    63,    64,    65,    66,    -1,     8,
      -1,    10,    11,    12,    -1,    14,    -1,    16,    -1,    18,
      19,    -1,    -1,    -1,    -1,    24,    25,    -1,   179,    -1,
      29,    30,   183,    32,    -1,    -1,    -1,    -1,    97,    38,
      -1,    -1,    41,    42,    43,    44,    45,    46,    47,    48,
      -1,   202,    -1,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    -1,    -1,    63,    64,    65,    66,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     8,
      -1,    10,    11,    12,    -1,    14,    -1,    16,    -1,    18,
      19,    -1,    -1,    -1,    -1,    24,    25,    -1,    97,    -1,
      29,    30,    -1,    32,    -1,    -1,    -1,    -1,    -1,    38,
      -1,    -1,    41,    42,    43,    44,    -1,    46,    47,    48,
     179,    -1,    -1,    -1,   183,    54,    -1,    56,    57,    58,
      59,    60,    -1,    -1,    63,    -1,    65,    66,    -1,    -1,
      -1,   200,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    97,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     0,     1,
     179,    -1,    -1,    -1,   183,    -1,     8,    -1,    10,    11,
      12,    -1,    14,    -1,    16,    -1,    18,    19,    -1,    -1,
      -1,   200,    24,    25,    26,    -1,    -1,    29,    30,    -1,
      32,    -1,    34,    -1,    -1,    -1,    38,    -1,    -1,    41,
      42,    43,    44,    45,    46,    47,    48,    -1,    -1,    -1,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    -1,
      -1,    63,    64,    65,    66,    -1,    -1,    -1,    -1,    -1,
     179,    -1,    -1,    -1,   183,    -1,     8,    -1,    10,    11,
      12,    -1,    14,    -1,    16,    -1,    18,    19,    -1,    -1,
      -1,   200,    24,    25,    -1,    97,    -1,    29,    30,    -1,
      32,    -1,    34,    -1,    -1,    -1,    38,    -1,    -1,    41,
      42,    43,    44,    45,    46,    47,    48,    -1,    -1,    -1,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    -1,
      -1,    63,    64,    65,    66,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       8,    -1,    10,    11,    12,    -1,    14,    -1,    16,    -1,
      18,    19,    -1,    -1,    -1,    97,    24,    25,    -1,    -1,
      -1,    29,    30,    -1,    32,    -1,    -1,   179,    -1,    -1,
      38,   183,    -1,    41,    42,    43,    44,    45,    46,    47,
      48,    -1,    -1,    -1,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    -1,    -1,    63,    64,    65,    66,    -1,
       8,    -1,    10,    11,    12,    -1,    14,    -1,    16,    -1,
      18,    19,    -1,    -1,    -1,    -1,    24,    25,    -1,    -1,
      -1,    29,    30,    -1,    32,    -1,    -1,    -1,    -1,    97,
      38,    -1,    -1,    41,    42,    43,    44,   179,    46,    47,
      48,   183,    -1,    -1,    -1,    -1,    54,    -1,    56,    57,
      58,    59,    60,    -1,    -1,    63,    -1,    65,    66,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    97,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   179,    -1,    -1,    -1,   183,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   179,    -1,    -1,    -1,   183
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const unsigned short yystos[] =
{
       0,     1,     8,    10,    11,    12,    14,    16,    18,    19,
      24,    25,    26,    29,    30,    32,    38,    41,    42,    43,
      44,    46,    47,    48,    54,    56,    57,    58,    59,    60,
      63,    65,    66,    97,   179,   183,   206,   207,   208,   209,
     210,   213,   214,   247,   248,   255,   256,   269,   270,   273,
     274,   285,   286,   295,   296,   307,   308,   315,   316,   319,
     320,   336,   337,   341,   342,   345,   346,   347,   355,   356,
     358,   382,   383,   388,   389,   399,   400,   407,   408,   411,
     412,   420,   421,   424,   425,   432,   433,   436,   437,   440,
     441,   445,   446,   449,   450,   457,   458,   461,   462,   466,
     467,   468,   485,   486,   487,   490,   491,   494,   495,   496,
     499,   500,   501,   503,   504,   508,   509,   203,     7,     7,
       3,   216,     4,     5,   218,   223,   223,     0,   207,   203,
     203,   203,   203,   203,   203,   203,   203,   203,   203,   121,
     122,   123,   124,   125,   172,   179,   180,   181,   338,   339,
     340,    34,   203,    45,   203,   203,   203,   203,   203,   203,
     203,   203,   203,   203,   203,   203,   203,   203,   203,    53,
     203,    52,   203,   203,    64,   203,    55,   203,   203,   203,
     218,    69,    70,    71,   101,   102,   199,   241,   242,   243,
     244,   245,   246,   281,    71,    75,    76,    77,   134,   199,
     252,   253,   254,    78,    79,    82,    83,    84,    85,    86,
      87,    88,    89,   257,   258,   259,   260,   261,   262,   263,
     264,   265,   266,   267,   268,    90,   244,   245,   271,   272,
     281,    91,    93,   244,   245,   281,   282,   283,   284,   128,
     129,   291,   292,   293,   294,   292,   293,   305,   306,    95,
      96,    97,    98,    99,   100,   313,   314,   104,   175,   176,
     177,   178,   317,   318,   119,   120,   177,   334,   335,   216,
       6,   217,   216,   216,   218,   218,   217,   217,   204,   200,
     217,   230,   338,   244,   245,   281,   343,   344,   353,    71,
     244,   245,   379,   380,   381,   182,   183,   185,   384,   385,
     386,   387,    80,    81,   103,   166,   173,   395,   396,   397,
     398,   292,   293,   405,   406,   292,   293,   409,   410,    95,
      97,   100,   139,   140,   418,   419,   104,   141,   174,   175,
     176,   177,   194,   422,   423,   292,   293,   430,   431,    97,
     179,   183,   434,   435,   292,   293,   438,   439,    71,   144,
     145,   442,   443,   444,   146,   147,   148,   149,   150,   151,
     152,   176,   178,   194,   447,   448,    95,    97,   100,   455,
     456,   104,   141,   153,   174,   175,   176,   177,   178,   194,
     195,   459,   460,   154,   155,   463,   464,   465,    75,    76,
      77,    97,   161,   483,   484,    97,   488,   489,    65,    66,
     159,   160,   183,   184,   198,   244,   245,   281,   492,   493,
     496,   162,   163,   192,   193,   199,   497,   498,   502,   503,
      37,   164,   505,   506,   507,   218,   200,   214,   279,   280,
     223,   223,   217,   204,   230,   230,   241,   216,     4,     5,
     219,   219,   218,   217,   204,   230,   252,   204,   230,   230,
     230,   230,   230,   230,   200,   218,   229,   200,   218,   220,
     224,   229,   224,   257,   223,   204,   271,   216,   204,   214,
     282,   204,   229,   224,   291,   229,   226,   228,   204,   305,
     216,   218,   216,   218,   218,   218,   204,   313,   218,   216,
     218,   220,   223,   204,   317,   217,   218,   220,   204,   334,
     217,   234,   204,   343,   142,   143,   204,   354,   204,   230,
     379,   223,   204,   229,   200,   214,   384,   218,   218,   216,
     204,   229,   230,   395,   229,   228,   204,   405,   229,   200,
     218,   221,   240,   204,   409,   216,   216,   223,   218,   222,
     222,   204,   418,   218,   223,   218,   216,   218,   220,   223,
     204,   422,   229,   228,   204,   430,   216,   223,   223,   204,
     434,   229,   229,   204,   438,   216,   216,   204,   230,   442,
     218,   218,   218,   218,   218,    20,    31,   256,   393,   394,
     216,   218,   223,   223,   204,   447,   216,   216,   221,   204,
     455,   218,   223,   218,   218,   216,   218,   220,   223,   223,
     218,   204,   459,     4,   215,   204,   200,   214,   463,   216,
     219,   219,   216,   219,   204,   483,   216,   204,   488,     7,
       7,   221,   223,   223,   223,   221,   204,   492,   218,   216,
     223,   221,   217,   204,   497,   204,   502,   217,   204,   230,
     505,   279,   202,   280,   218,   233,   220,   235,   218,   200,
     223,   201,   202,   217,     9,    20,    33,    51,    65,    66,
      72,    73,    74,   126,   211,   250,   251,   342,   351,   352,
     361,   362,   364,   394,   416,   417,   481,   482,    13,    20,
      21,    23,    27,    28,    36,    49,    61,    62,    65,    66,
     212,   277,   278,   299,   300,   311,   312,   324,   325,   332,
     333,   371,   372,   374,   377,   378,   428,   429,   453,   454,
     473,   474,   357,   207,   221,   239,   218,   218,   203,   207,
     201,   280,   201,   202,   218,   201,   202,   220,   218,   223,
     237,   217,     7,     7,    20,   364,    20,   482,    20,   352,
     394,   417,   203,   203,    39,   203,   203,   203,   203,     7,
       7,   203,   203,   203,   203,   203,    35,   203,   108,   135,
     136,   137,   177,   365,   366,   375,   376,   203,   203,   203,
     201,   202,   201,   218,    71,    75,    76,    77,    80,   130,
     131,   390,   391,   392,   201,   218,   220,   201,   202,   223,
     211,   249,    71,   130,   131,   348,   349,   350,   104,   186,
     187,   188,   189,   190,   359,   360,   130,   131,   197,   413,
     414,   415,   159,   160,   183,   184,   479,   480,   179,   275,
     276,    94,   133,   168,   169,   297,   298,    94,   133,   167,
     169,   174,   309,   310,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   127,   169,   177,   321,   322,   323,
     107,   109,   115,   116,   117,   118,   127,   132,   160,   193,
     326,   327,   328,   329,   330,   331,   105,   106,   107,   108,
     109,   110,   127,   132,   135,   138,   165,   177,   365,   366,
     367,   368,   369,   370,   216,    65,    66,   302,   303,   304,
      15,   289,   290,   225,   227,   227,   204,   375,   135,   177,
     426,   427,   174,   451,   452,   156,   157,   158,   171,   469,
     470,   471,   472,   239,   218,   216,   219,   219,   218,   216,
     216,   204,   230,   390,   223,   249,   204,   216,   216,   204,
     230,   348,   218,   220,   220,   220,   218,   218,   204,   359,
     216,   216,     4,   204,   215,   238,   413,   218,   222,   222,
     222,   204,   479,   223,   204,   275,   216,   216,   218,   218,
     204,   297,   216,   216,   216,   218,   218,   204,   309,    20,
      40,   403,   404,    20,    50,   477,   478,   216,   216,   218,
     216,   215,   218,   215,   218,   216,    20,   290,   204,   229,
     321,   216,   218,   216,   216,   216,   216,   204,   200,   222,
     231,   240,   231,   228,   326,   404,   478,   216,   216,   218,
     216,   216,   216,   304,   290,   227,   227,   227,   227,   204,
     369,     7,     7,    17,   203,   203,   200,   215,    20,   304,
      20,   290,   204,   426,   218,   204,   451,   342,   218,   204,
     230,   229,   469,   363,     4,   202,   215,   203,   203,   222,
     236,   373,   170,   301,   177,   287,   288,   215,   232,     4,
     215,   191,   401,   402,   170,   475,   476,   201,   202,   222,
     228,   204,   224,   204,   287,   201,   202,   215,   228,   204,
     401,   231,   204,   475,   222,   215
};

#if ! defined (YYSIZE_T) && defined (__SIZE_TYPE__)
# define YYSIZE_T __SIZE_TYPE__
#endif
#if ! defined (YYSIZE_T) && defined (size_t)
# define YYSIZE_T size_t
#endif
#if ! defined (YYSIZE_T)
# if defined (__STDC__) || defined (__cplusplus)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# endif
#endif
#if ! defined (YYSIZE_T)
# define YYSIZE_T unsigned int
#endif

#define yyerrok     (yyerrstatus = 0)
#define yyclearin   (yychar = YYEMPTY)
#define YYEMPTY     (-2)
#define YYEOF       0

#define YYACCEPT    goto yyacceptlab
#define YYABORT     goto yyabortlab
#define YYERROR     goto yyerrlab1

/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL      goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                  \
do                              \
  if (yychar == YYEMPTY && yylen == 1)              \
    {                               \
      yychar = (Token);                     \
      yylval = (Value);                     \
      yytoken = YYTRANSLATE (yychar);               \
      YYPOPSTACK;                       \
      goto yybackup;                        \
    }                               \
  else                              \
    {                               \
      yyerror ("syntax error: cannot back up");\
      YYERROR;                          \
    }                               \
while (0)

#define YYTERROR    1
#define YYERRCODE   256

/* YYLLOC_DEFAULT -- Compute the default location (before the actions
   are run).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)         \
  Current.first_line   = Rhs[1].first_line;      \
  Current.first_column = Rhs[1].first_column;    \
  Current.last_line    = Rhs[N].last_line;       \
  Current.last_column  = Rhs[N].last_column;
#endif

/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)            \
do {                        \
  if (yydebug)                  \
    YYFPRINTF Args;             \
} while (0)

# define YYDSYMPRINT(Args)          \
do {                        \
  if (yydebug)                  \
    yysymprint Args;                \
} while (0)

# define YYDSYMPRINTF(Title, Token, Value, Location)        \
do {                                \
  if (yydebug)                          \
    {                               \
      YYFPRINTF (stderr, "%s ", Title);             \
      yysymprint (stderr,                   \
                  Token, Value);    \
      YYFPRINTF (stderr, "\n");                 \
    }                               \
} while (0)

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (cinluded).                                                   |
`------------------------------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yy_stack_print (short *bottom, short *top)
#else
static void
yy_stack_print (bottom, top)
    short *bottom;
    short *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (/* Nothing. */; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                \
do {                                \
  if (yydebug)                          \
    yy_stack_print ((Bottom), (Top));               \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yy_reduce_print (int yyrule)
#else
static void
yy_reduce_print (yyrule)
    int yyrule;
#endif
{
  int yyi;
  unsigned int yylineno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %u), ",
             yyrule - 1, yylineno);
  /* Print the symbols being reduced, and their result.  */
  for (yyi = yyprhs[yyrule]; 0 <= yyrhs[yyi]; yyi++)
    YYFPRINTF (stderr, "%s ", yytname [yyrhs[yyi]]);
  YYFPRINTF (stderr, "-> %s\n", yytname [yyr1[yyrule]]);
}

# define YY_REDUCE_PRINT(Rule)      \
do {                    \
  if (yydebug)              \
    yy_reduce_print (Rule);     \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YYDSYMPRINT(Args)
# define YYDSYMPRINTF(Title, Token, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   SIZE_MAX < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#if YYMAXDEPTH == 0
# undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined (__GLIBC__) && defined (_STRING_H)
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
#   if defined (__STDC__) || defined (__cplusplus)
yystrlen (const char *yystr)
#   else
yystrlen (yystr)
     const char *yystr;
#   endif
{
  register const char *yys = yystr;

  while (*yys++ != '\0')
    continue;

  return yys - yystr - 1;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined (__GLIBC__) && defined (_STRING_H) && defined (_GNU_SOURCE)
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
#   if defined (__STDC__) || defined (__cplusplus)
yystpcpy (char *yydest, const char *yysrc)
#   else
yystpcpy (yydest, yysrc)
     char *yydest;
     const char *yysrc;
#   endif
{
  register char *yyd = yydest;
  register const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

#endif /* !YYERROR_VERBOSE */



#if YYDEBUG
/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yysymprint (FILE *yyoutput, int yytype, YYSTYPE *yyvaluep)
#else
static void
yysymprint (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvaluep;

  if (yytype < YYNTOKENS)
    {
      YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
# ifdef YYPRINT
      YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
    }
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  switch (yytype)
    {
      default:
        break;
    }
  YYFPRINTF (yyoutput, ")");
}

#endif /* ! YYDEBUG */
/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yydestruct (int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yytype, yyvaluep)
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvaluep;

  switch (yytype)
    {

      default:
        break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
# if defined (__STDC__) || defined (__cplusplus)
int yyparse (void *YYPARSE_PARAM);
# else
int yyparse ();
# endif
#else /* ! YYPARSE_PARAM */
#if defined (__STDC__) || defined (__cplusplus)
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
# if defined (__STDC__) || defined (__cplusplus)
int yyparse (void *YYPARSE_PARAM)
# else
int yyparse (YYPARSE_PARAM)
  void *YYPARSE_PARAM;
# endif
#else /* ! YYPARSE_PARAM */
#if defined (__STDC__) || defined (__cplusplus)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{

  register int yystate;
  register int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  short yyssa[YYINITDEPTH];
  short *yyss = yyssa;
  register short *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  register YYSTYPE *yyvsp;



#define YYPOPSTACK   (yyvsp--, yyssp--)

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* When reducing, the number of symbols on the RHS of the reduced
     rule.  */
  int yylen;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;     /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed. so pushing a state here evens the stacks.
     */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
    /* Give user a chance to reallocate the stack. Use copies of
       these so that the &'s don't force the real ones into
       memory.  */
    YYSTYPE *yyvs1 = yyvs;
    short *yyss1 = yyss;


    /* Each stack pointer address is followed by the size of the
       data in use in that stack, in bytes.  This used to be a
       conditional around just the two extra args, but that might
       be undefined if yyoverflow is a macro.  */
    yyoverflow ("parser stack overflow",
            &yyss1, yysize * sizeof (*yyssp),
            &yyvs1, yysize * sizeof (*yyvsp),

            &yystacksize);

    yyss = yyss1;
    yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyoverflowlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
    goto yyoverflowlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
    yystacksize = YYMAXDEPTH;

      {
    short *yyss1 = yyss;
    union yyalloc *yyptr =
      (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
    if (! yyptr)
      goto yyoverflowlab;
    YYSTACK_RELOCATE (yyss);
    YYSTACK_RELOCATE (yyvs);

#  undef YYSTACK_RELOCATE
    if (yyss1 != yyssa)
      YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;


      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
          (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
    YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to lookahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YYDSYMPRINTF ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
    goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the lookahead token.  */
  YYDPRINTF ((stderr, "Shifting token %s, ", yytname[yytoken]));

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;


  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  yystate = yyn;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 3:

    {YYABORT;;}
    break;

  case 4:

    {YYABORT;;}
    break;

  case 63:

    { _vectorInt32.push_back(yyvsp[0].ival); ;}
    break;

  case 64:

    { yyval.bval = yyvsp[0].bval; ;}
    break;

  case 65:

    {;}
    break;

  case 66:

    {
        ;}
    break;

  case 67:

    {
            yyval.fval = (float)yyvsp[0].ival;
        ;}
    break;

  case 69:

    {yyval.fval = (float)yyvsp[0].ival;;}
    break;

  case 70:

    {
            _color[0] = yyvsp[-2].fval;
            _color[1] = yyvsp[-1].fval;
            _color[2] = yyvsp[0].fval;
        ;}
    break;

  case 71:

    {
            gRotation[0] = yyvsp[-3].fval;
            gRotation[1] = yyvsp[-2].fval;
            gRotation[2] = yyvsp[-1].fval;
            gRotation[3] = yyvsp[0].fval;
        ;}
    break;

  case 72:

    {
            gVec2f[0] = yyvsp[-1].fval;
            gVec2f[1] = yyvsp[0].fval;
        ;}
    break;

  case 73:

    { _vectorVector.push_back(Vector(yyvsp[-2].fval,yyvsp[-1].fval,yyvsp[0].fval)); ;}
    break;

  case 74:

    {;}
    break;

  case 75:

    {;}
    break;

  case 76:

    { _vectorInt32.clear(); ;}
    break;

  case 77:

    { _vectorVector.clear(); ;}
    break;

  case 78:

    {;}
    break;

  case 79:

    {;}
    break;

  case 82:

    {;}
    break;

  case 83:

    {;}
    break;

  case 84:

    {;}
    break;

  case 85:

    {;}
    break;

  case 86:

    {;}
    break;

  case 87:

    {;}
    break;

  case 88:

    {;}
    break;

  case 89:

    {;}
    break;

  case 90:

    {;}
    break;

  case 91:

    {;}
    break;

  case 92:

    {;}
    break;

  case 93:

    {;}
    break;

  case 94:

    {;}
    break;

  case 95:

    {;}
    break;

  case 96:

    {;}
    break;

  case 97:

    {;}
    break;

  case 98:

    {;}
    break;

  case 99:

    {;}
    break;

  case 100:

    {;}
    break;

  case 101:

    {;}
    break;

  case 102:

    {;}
    break;

  case 103:

    {;}
    break;

  case 104:

    {;}
    break;

  case 105:

    {;}
    break;

  case 106:

    {;}
    break;

  case 107:

    {;}
    break;

  case 108:

    {;}
    break;

  case 109:

    {;}
    break;

  case 110:

    {;}
    break;

  case 111:

    {;}
    break;

  case 112:

    {;}
    break;

  case 113:

    {;}
    break;

  case 114:

    {;}
    break;

  case 115:

    {;}
    break;

  case 123:

    {
        ;}
    break;

  case 124:

    {
        ;}
    break;

  case 125:

    {
        ;}
    break;

  case 126:

    {
        ;}
    break;

  case 128:

    {
        ;}
    break;

  case 129:

    {
        ;}
    break;

  case 130:

    {
        ;}
    break;

  case 133:

    {
        ;}
    break;

  case 134:

    {
        ;}
    break;

  case 145:

    {
        ;}
    break;

  case 146:

    {
        ;}
    break;

  case 149:

    {
        ;}
    break;

  case 150:

    {
        ;}
    break;

  case 151:

    {
        ;}
    break;

  case 152:

    {
        ;}
    break;

  case 153:

    {
        ;}
    break;

  case 154:

    {
        ;}
    break;

  case 155:

    {
        ;}
    break;

  case 156:

    {
        ;}
    break;

  case 157:

    {
        ;}
    break;

  case 160:

    {
        ;}
    break;

  case 161:

    {
        ;}
    break;

  case 162:

    {
        ;}
    break;

  case 163:

    {
        ;}
    break;

  case 164:

    {
        ;}
    break;

  case 165:

    {
        ;}
    break;

  case 166:

    {
        ;}
    break;

  case 167:

    {
        ;}
    break;

  case 168:

    {
        ;}
    break;

  case 169:

    {
        ;}
    break;

  case 170:

    {
        ;}
    break;

  case 171:

    {
        ;}
    break;

  case 172:

    {
        ;}
    break;

  case 173:

    {
        ;}
    break;

  case 174:

    {
        ;}
    break;

  case 175:

    {
        ;}
    break;

  case 176:

    {
        ;}
    break;

  case 177:

    {
        ;}
    break;

  case 178:

    {
        ;}
    break;

  case 179:

    {
        ;}
    break;

  case 180:

    {
        ;}
    break;

  case 181:

    {
        ;}
    break;

  case 185:

    {
        ;}
    break;

  case 188:

    {
        ;}
    break;

  case 189:

    {
        ;}
    break;

  case 192:

    {
        ;}
    break;

  case 193:

    {
        ;}
    break;

  case 194:

    {
        ;}
    break;

  case 195:

    {;}
    break;

  case 196:

    {;}
    break;

  case 197:

    {;}
    break;

  case 198:

    {;}
    break;

  case 199:

    {;}
    break;

  case 204:

    {
        ;}
    break;

  case 206:

    {
        ;}
    break;

  case 209:

    {
        ;}
    break;

  case 210:

    {
        ;}
    break;

  case 211:

    {
        ;}
    break;

  case 215:

    {
        ;}
    break;

  case 216:

    {
        ;}
    break;

  case 219:

    {
        ;}
    break;

  case 220:

    {
        ;}
    break;

  case 221:

    {
        ;}
    break;

  case 222:

    {
        ;}
    break;

  case 223:

    {
        ;}
    break;

  case 224:

    {
        ;}
    break;

  case 227:

    {
        ;}
    break;

  case 228:

    {
        ;}
    break;

  case 229:

    {
        ;}
    break;

  case 230:

    {
        ;}
    break;

  case 231:

    {
        ;}
    break;

  case 232:

    {
        ;}
    break;

  case 235:

    {;}
    break;

  case 236:

    {;}
    break;

  case 237:

    {
        ;}
    break;

  case 238:

    {;}
    break;

  case 239:

    {;}
    break;

  case 242:

    {
        ;}
    break;

  case 243:

    {
        ;}
    break;

  case 244:

    {
        ;}
    break;

  case 245:

    {
        ;}
    break;

  case 248:

    {
        ;}
    break;

  case 249:

    {
        ;}
    break;

  case 250:

    {
        ;}
    break;

  case 251:

    {
        ;}
    break;

  case 252:

    {
        ;}
    break;

  case 253:

    {
        ;}
    break;

  case 254:

    {
        ;}
    break;

  case 257:

    {
        ;}
    break;

  case 258:

    {
        ;}
    break;

  case 259:

    {
        ;}
    break;

  case 260:

    {
        ;}
    break;

  case 261:

    {
        ;}
    break;

  case 262:

    {
        ;}
    break;

  case 263:

    {
        ;}
    break;

  case 264:

    {
        ;}
    break;

  case 267:

    {
        ;}
    break;

  case 268:

    {
        ;}
    break;

  case 269:

    {
        ;}
    break;

  case 270:

    {
        ;}
    break;

  case 271:

    {
        ;}
    break;

  case 272:

    {
        ;}
    break;

  case 273:

    {
        ;}
    break;

  case 276:

    {
        ;}
    break;

  case 283:

    {
        ;}
    break;

  case 284:

    {
        ;}
    break;

  case 285:

    {
        ;}
    break;

  case 286:

    {
        ;}
    break;

  case 287:

    {
        ;}
    break;

  case 288:

    {
        ;}
    break;

  case 289:

    {
        ;}
    break;

  case 290:

    {
        ;}
    break;

  case 291:

    {
        ;}
    break;

  case 292:

    {
        ;}
    break;

  case 293:

    {
        ;}
    break;

  case 294:

    {
        ;}
    break;

  case 297:

    {
        ;}
    break;

  case 298:

    {
        ;}
    break;

  case 299:

    {
        ;}
    break;

  case 300:

    {
        ;}
    break;

  case 301:

    {
        ;}
    break;

  case 302:

    {
        ;}
    break;

  case 303:

    {
        ;}
    break;

  case 304:

    {
        ;}
    break;

  case 305:

    {
        ;}
    break;

  case 306:

    {
        ;}
    break;

  case 307:

    {
        ;}
    break;

  case 308:

    {
        ;}
    break;

  case 309:

    {
        ;}
    break;

  case 310:

    {
        ;}
    break;

  case 311:

    {
        ;}
    break;

  case 312:

    {
        ;}
    break;

  case 315:

    {
        ;}
    break;

  case 316:

    {
        ;}
    break;

  case 317:

    {
        ;}
    break;

  case 318:

    {
        ;}
    break;

  case 319:

    {
        ;}
    break;

  case 322:

    {
        ;}
    break;

  case 323:

    {
        ;}
    break;

  case 324:

    {
        ;}
    break;

  case 325:

    {
        ;}
    break;

  case 326:

    {
        ;}
    break;

  case 327:

    {
        ;}
    break;

  case 328:

    {
        ;}
    break;

  case 329:

    {
        ;}
    break;

  case 330:

    {
        ;}
    break;

  case 331:

    {
        ;}
    break;

  case 332:

    {
        ;}
    break;

  case 333:

    {
        ;}
    break;

  case 339:

    {;}
    break;

  case 340:

    {;}
    break;

  case 341:

    {;}
    break;

  case 342:

    {;}
    break;

  case 343:

    {;}
    break;

  case 346:

    {
        ;}
    break;

  case 347:

    {
        ;}
    break;

  case 348:

    {
        ;}
    break;

  case 349:

    {
        ;}
    break;

  case 350:

    {
        ;}
    break;

  case 351:

    {
        ;}
    break;

  case 352:

    {;}
    break;

  case 353:

    {;}
    break;

  case 358:

    {;}
    break;

  case 359:

    {;}
    break;

  case 360:

    {
            #ifdef YYDEBUG
            cout << "Shape" << endl;
            #endif

            _faceSet.clear();
            _material.clear();
        ;}
    break;

  case 361:

    {
            if (VrmlParseShape)
            {
                Shape *shape = new Shape();
                shape->faces    = _faceSet;
                shape->material = _material;
                GltShapePtr ptr(shape);
                VrmlParseShape(ptr);
            }
        ;}
    break;

  case 362:

    {
        ;}
    break;

  case 363:

    {;}
    break;

  case 364:

    {;}
    break;

  case 365:

    { assert(_material.get()); _material->ambientIntensity = yyvsp[0].fval;     ;}
    break;

  case 366:

    { assert(_material.get()); _material->diffuseColor     = _color; ;}
    break;

  case 367:

    { assert(_material.get()); _material->emissiveColor    = _color; ;}
    break;

  case 368:

    { assert(_material.get()); _material->shininess        = yyvsp[0].fval;     ;}
    break;

  case 369:

    { assert(_material.get()); _material->specularColor    = _color; ;}
    break;

  case 370:

    { assert(_material.get()); _material->transparency     = yyvsp[0].fval;     ;}
    break;

  case 371:

    {;}
    break;

  case 372:

    {;}
    break;

  case 373:

    {
            #ifdef YYDEBUG
            cout << "Material" << endl;
            #endif

            _material = new Material();
        ;}
    break;

  case 374:

    {
            if (VrmlParseMaterial)
                VrmlParseMaterial(_material);
        ;}
    break;

  case 375:

    {;}
    break;

  case 376:

    {;}
    break;

  case 377:

    {;}
    break;

  case 378:

    {;}
    break;

  case 379:

    {;}
    break;

  case 380:

    {;}
    break;

  case 381:

    {;}
    break;

  case 382:

    {;}
    break;

  case 383:

    {;}
    break;

  case 384:

    { assert(_faceSet.get()); _faceSet->coord  = _vectorVector; ;}
    break;

  case 385:

    { assert(_faceSet.get()); _faceSet->normal = _vectorVector; ;}
    break;

  case 386:

    {;}
    break;

  case 387:

    { assert(_faceSet.get()); _faceSet->ccw             = yyvsp[0].bval; ;}
    break;

  case 388:

    { assert(_faceSet.get()); _faceSet->convex          = yyvsp[0].bval; ;}
    break;

  case 389:

    { assert(_faceSet.get()); _faceSet->solid           = yyvsp[0].bval; ;}
    break;

  case 390:

    { assert(_faceSet.get()); _faceSet->creaseAngle     = yyvsp[0].fval; ;}
    break;

  case 391:

    { assert(_faceSet.get()); _faceSet->colorPerVertex  = yyvsp[0].bval; ;}
    break;

  case 392:

    { assert(_faceSet.get()); _faceSet->normalPerVertex = yyvsp[0].bval; ;}
    break;

  case 393:

    { assert(_faceSet.get()); _faceSet->coordIndex    = _vectorInt32; ;}
    break;

  case 394:

    { assert(_faceSet.get()); _faceSet->normalIndex   = _vectorInt32; ;}
    break;

  case 395:

    { assert(_faceSet.get()); _faceSet->colorIndex    = _vectorInt32; ;}
    break;

  case 396:

    { assert(_faceSet.get()); _faceSet->texCoordIndex = _vectorInt32; ;}
    break;

  case 397:

    {;}
    break;

  case 398:

    {;}
    break;

  case 399:

    {
            #ifdef YYDEBUG
            cout << "Indexed Face Set" << endl;
            #endif

            _faceSet = new IndexedFaceSet();
        ;}
    break;

  case 400:

    {
            assert(_faceSet.get());

            #ifdef YYDEBUG
            cout << _faceSet->coord.size()      << " points."       << endl;
            cout << _faceSet->normal.size()     << " normals."      << endl;
            cout << _faceSet->coordIndex.size() << " face entries." << endl;
            #endif

            if (VrmlParseIndexedFaceSet)
                VrmlParseIndexedFaceSet(_faceSet);
        ;}
    break;

  case 401:

    {;}
    break;

  case 402:

    {;}
    break;

  case 407:

    {
        ;}
    break;

  case 408:

    {
        ;}
    break;

  case 409:

    {
        ;}
    break;

  case 410:

    {
        ;}
    break;

  case 411:

    {
        ;}
    break;

  case 414:

    {
        ;}
    break;

  case 415:

    {
        ;}
    break;

  case 418:

    {
        ;}
    break;

  case 419:

    {
        ;}
    break;

  case 422:

    {
        ;}
    break;

  case 423:

    {
        ;}
    break;

  case 424:

    {
        ;}
    break;

  case 425:

    {
        ;}
    break;

  case 426:

    {
        ;}
    break;

  case 427:

    {
        ;}
    break;

  case 428:

    {
        ;}
    break;

  case 429:

    {
        ;}
    break;

  case 432:

    {
        ;}
    break;

  case 433:

    {
        ;}
    break;

  case 434:

    {
        ;}
    break;

  case 435:

    {
        ;}
    break;

  case 436:

    {
        ;}
    break;

  case 437:

    {
        ;}
    break;

  case 438:

    {
        ;}
    break;

  case 439:

    {
        ;}
    break;

  case 440:

    {
        ;}
    break;

  case 441:

    {
        ;}
    break;

  case 444:

    {
        ;}
    break;

  case 445:

    {
        ;}
    break;

  case 446:

    {
        ;}
    break;

  case 447:

    {
        ;}
    break;

  case 448:

    {
        ;}
    break;

  case 449:

    {
        ;}
    break;

  case 450:

    {
        ;}
    break;

  case 451:

    {
        ;}
    break;

  case 452:

    {
        ;}
    break;

  case 456:

    {
        ;}
    break;

  case 457:

    {
            #ifdef YYDEBUG
            cout << _vectorVector.size() << " normals." << endl;
            #endif
        ;}
    break;

  case 460:

    {
        ;}
    break;

  case 461:

    {
        ;}
    break;

  case 462:

    {
        ;}
    break;

  case 463:

    {
        ;}
    break;

  case 466:

    {
        ;}
    break;

  case 467:

    {
        ;}
    break;

  case 468:

    {
        ;}
    break;

  case 469:

    {
        ;}
    break;

  case 472:

    {
        ;}
    break;

  case 473:

    {
        ;}
    break;

  case 474:

    {
        ;}
    break;

  case 475:

    {
        ;}
    break;

  case 476:

    {
        ;}
    break;

  case 477:

    {
        ;}
    break;

  case 480:

    {
        ;}
    break;

  case 481:

    {
        ;}
    break;

  case 482:

    {
        ;}
    break;

  case 483:

    {
        ;}
    break;

  case 484:

    {
        ;}
    break;

  case 485:

    {
        ;}
    break;

  case 486:

    {
        ;}
    break;

  case 489:

    {
        ;}
    break;

  case 490:

    {
        ;}
    break;

  case 491:

    {
        ;}
    break;

  case 492:

    {
        ;}
    break;

  case 493:

    {
        ;}
    break;

  case 494:

    {
        ;}
    break;

  case 495:

    {
        ;}
    break;

  case 496:

    {
        ;}
    break;

  case 497:

    {
        ;}
    break;

  case 504:

    {
        ;}
    break;

  case 505:

    {
        ;}
    break;

  case 508:

    {
        ;}
    break;

  case 509:

    {
        ;}
    break;

  case 510:

    {
        ;}
    break;

  case 511:

    {
        ;}
    break;

  case 514:

    {
        ;}
    break;

  case 515:

    {
        ;}
    break;

  case 516:

    {
        ;}
    break;

  case 517:

    {
        ;}
    break;

  case 518:

    {
        ;}
    break;

  case 521:

    {
        ;}
    break;

  case 522:

    {
        ;}
    break;

  case 523:

    {
        ;}
    break;

  case 524:

    {
        ;}
    break;

  case 527:

    {
        ;}
    break;

  case 528:

    {
        ;}
    break;

  case 529:

    {
        ;}
    break;

  case 530:

    {
        ;}
    break;

  case 531:

    {
        ;}
    break;

  case 532:

    {
        ;}
    break;

  case 535:

    {
        ;}
    break;

  case 536:

    {
        ;}
    break;

  case 537:

    {
        ;}
    break;

  case 538:

    {
        ;}
    break;

  case 539:

    {
        ;}
    break;

  case 540:

    {
        ;}
    break;

  case 541:

    {
        ;}
    break;

  case 542:

    {
        ;}
    break;

  case 546:

    {
        ;}
    break;

  case 547:

    {
        ;}
    break;

  case 548:

    {
        ;}
    break;

  case 551:

    {
        ;}
    break;

  case 552:

    {
        ;}
    break;

  case 553:

    {
        ;}
    break;

  case 556:

    {
        ;}
    break;

  case 557:

    {
        ;}
    break;

  case 558:

    {
        ;}
    break;

  case 559:

    {
        ;}
    break;

  case 560:

    {
        ;}
    break;

  case 563:

    {
        ;}
    break;

  case 564:

    {
        ;}
    break;

  case 565:

    {
        ;}
    break;

  case 566:

    {
        ;}
    break;

  case 567:

    {
        ;}
    break;

  case 568:

    {
        ;}
    break;

  case 569:

    {
        ;}
    break;

  case 570:

    {
        ;}
    break;

  case 571:

    {
        ;}
    break;

  case 572:

    {
        ;}
    break;

  case 573:

    {
        ;}
    break;

  case 574:

    {
        ;}
    break;

  case 577:

    {
        ;}
    break;

  case 578:

    {
        ;}
    break;

  case 579:

    {
        ;}
    break;

  case 580:

    {
        ;}
    break;

  case 581:

    {;}
    break;

  case 582:

    {;}
    break;

  case 583:

    {;}
    break;

  case 584:

    {;}
    break;

  case 585:

    {;}
    break;

  case 588:

    {
        ;}
    break;

  case 589:

    {
        ;}
    break;

  case 590:

    {
        ;}
    break;

  case 593:

    {
        ;}
    break;

  case 594:

    {
        ;}
    break;

  case 595:

    {
        ;}
    break;

  case 599:

    {
        ;}
    break;

  case 600:

    {
        ;}
    break;

  case 603:

    {
        ;}
    break;

  case 604:

    {
        ;}
    break;

  case 605:

    {
        ;}
    break;

  case 606:

    {
        ;}
    break;

  case 607:

    {
        ;}
    break;

  case 608:

    {
        ;}
    break;

  case 611:

    {
        ;}
    break;

  case 612:

    {
        ;}
    break;

  case 613:

    {
        ;}
    break;

  case 614:

    {
        ;}
    break;

  case 615:

    {
        ;}
    break;

  case 616:

    {;}
    break;

  case 617:

    {;}
    break;

  case 618:

    {;}
    break;

  case 619:

    {;}
    break;

  case 620:

    {;}
    break;

  case 623:

    {
        ;}
    break;

  case 624:

    {
        ;}
    break;

  case 625:

    {
        ;}
    break;

  case 629:

    {
        ;}
    break;

  case 630:

    {
        ;}
    break;

  case 631:

    {
        ;}
    break;

  case 632:

    {
        ;}
    break;

  case 633:

    {
        ;}
    break;

  case 637:

    {;}
    break;

  case 638:

    {;}
    break;

  case 639:

    {;}
    break;

  case 640:

    {;}
    break;

  case 641:

    {;}
    break;

  case 644:

    {;}
    break;

  case 645:

    {;}
    break;

  case 646:

    {;}
    break;

  case 647:

    {;}
    break;

  case 648:

    {;}
    break;

  case 649:

    {;}
    break;

  case 650:

    {;}
    break;

  case 651:

    {;}
    break;

  case 652:

    {;}
    break;

  case 653:

    {;}
    break;

  case 656:

    {
        ;}
    break;

  case 657:

    {
        ;}
    break;

  case 658:

    {
        ;}
    break;

  case 659:

    {
        ;}
    break;

  case 660:

    {
        ;}
    break;

  case 663:

    {
        ;}
    break;

  case 664:

    {
        ;}
    break;

  case 665:

    {
        ;}
    break;

  case 666:

    {
        ;}
    break;

  case 667:

    {
        ;}
    break;


    }

/* Line 991 of yacc.c.  */


  yyvsp -= yylen;
  yyssp -= yylen;


  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (YYPACT_NINF < yyn && yyn < YYLAST)
    {
      YYSIZE_T yysize = 0;
      int yytype = YYTRANSLATE (yychar);
      char *yymsg;
      int yyx, yycount;

      yycount = 0;
      /* Start YYX at -YYN if negative to avoid negative indexes in
         YYCHECK.  */
      for (yyx = yyn < 0 ? -yyn : 0;
           yyx < (int) (sizeof (yytname) / sizeof (char *)); yyx++)
        if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
          yysize += yystrlen (yytname[yyx]) + 15, yycount++;
      yysize += yystrlen ("syntax error, unexpected ") + 1;
      yysize += yystrlen (yytname[yytype]);
      yymsg = (char *) YYSTACK_ALLOC (yysize);
      if (yymsg != 0)
        {
          char *yyp = yystpcpy (yymsg, "syntax error, unexpected ");
          yyp = yystpcpy (yyp, yytname[yytype]);

          if (yycount < 5)
        {
          yycount = 0;
          for (yyx = yyn < 0 ? -yyn : 0;
               yyx < (int) (sizeof (yytname) / sizeof (char *));
               yyx++)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
              {
            const char *yyq = ! yycount ? ", expecting " : " or ";
            yyp = yystpcpy (yyp, yyq);
            yyp = yystpcpy (yyp, yytname[yyx]);
            yycount++;
              }
        }
          yyerror (yymsg);
          YYSTACK_FREE (yymsg);
        }
      else
        yyerror ("syntax error; also virtual memory exhausted");
    }
      else
#endif /* YYERROR_VERBOSE */
    yyerror ("syntax error");
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
     error, discard it.  */

      /* Return failure if at end of input.  */
      if (yychar == YYEOF)
        {
      /* Pop the error token.  */
          YYPOPSTACK;
      /* Pop the rest of the stack.  */
      while (yyss < yyssp)
        {
          YYDSYMPRINTF ("Error: popping", yystos[*yyssp], yyvsp, yylsp);
          yydestruct (yystos[*yyssp], yyvsp);
          YYPOPSTACK;
        }
      YYABORT;
        }

      YYDSYMPRINTF ("Error: discarding", yytoken, &yylval, &yylloc);
      yydestruct (yytoken, &yylval);
      yychar = YYEMPTY;

    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab2;


/*----------------------------------------------------.
| yyerrlab1 -- error raised explicitly by an action.  |
`----------------------------------------------------*/
yyerrlab1:

  /* Suppress GCC warning that yyerrlab1 is unused when no action
     invokes YYERROR.  */

#if !defined(__MINGW32__) && !defined(__CYGWIN__) && !defined(linux) && !defined(__APPLE__)
#if defined (__GNUC_MINOR__) && 2093 <= (__GNUC__ * 1000 + __GNUC_MINOR__)
  __attribute__ ((__unused__))
#endif
#endif

  goto yyerrlab2;

/*---------------------------------------------------------------.
| yyerrlab2 -- pop states until the error token can be shifted.  |
`---------------------------------------------------------------*/
yyerrlab2:
  yyerrstatus = 3;  /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
    {
      yyn += YYTERROR;
      if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
        {
          yyn = yytable[yyn];
          if (0 < yyn)
        break;
        }
    }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
    YYABORT;

      YYDSYMPRINTF ("Error: popping", yystos[*yyssp], yyvsp, yylsp);
      yydestruct (yystos[yystate], yyvsp);
      yyvsp--;
      yystate = *--yyssp;

      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  YYDPRINTF ((stderr, "Shifting error token, "));

  *++yyvsp = yylval;


  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#ifndef yyoverflow
/*----------------------------------------------.
| yyoverflowlab -- parser overflow comes here.  |
`----------------------------------------------*/
yyoverflowlab:
  yyerror ("parser stack overflow");
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  return yyresult;
}





#include <iostream>
using namespace std;

extern  char    *Vrmltext;
extern  int      VrmlCurrentLine;

int yyerror(const char *s)
{
    cerr << "VRML " << s << " in line " << VrmlCurrentLine << " near " << Vrmltext << endl;
    return 0;
}

