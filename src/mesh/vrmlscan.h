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




#if ! defined (YYSTYPE) && ! defined (YYSTYPE_IS_DECLARED)

typedef union YYSTYPE {
bool     bval;
int      ival;
float    fval;
char     *sval;
} YYSTYPE;
/* Line 1248 of yacc.c.  */

# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE Vrmllval;



