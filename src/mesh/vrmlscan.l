%{
/******************************************************************
*
*	VrmlScan.l
*
*   Lexer for VRML V2.0
*
*	Copyright (C) Satoshi Konno 1996
*	Copyright (C) ANCA Pty Ltd
*
*   NOTES:
*
*   PROTO, USE, DEF, ROUTE, protoName functionality has
*   been disabled.
*
******************************************************************/

#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

#include <mesh/vrmlscan.h>

int VrmlCurrentLine = 1;
static char	buffer[1024];

#define YY_NEVER_INTERACTIVE 1

#define input	yyinput
#define output	yyoutput

#define YY_DECL int Vrmllex YY_PROTO(( void ))
#define yylval  Vrmllval

#if 0
#define DEBUG(message) cerr << (message); 
#else
#define DEBUG(mesage)  
#endif

%}

%%

-?[0-9]+							{ yylval.ival = atoi(yytext);           return NUMBER; }
-?[0-9]*\.?[0-9]*([eE][+-]?[0-9]+)?	{ yylval.fval = (float) atof(yytext);   return AFLOAT; }
0x[0-9A-Fa-f]+						{ sscanf(yytext, "0x%x", &yylval.ival); return NUMBER; }

","									{ return ','; }
"}"									{ return '}'; }
"{"									{ return '{'; }
"["									{ return '['; }
"]"									{ return ']'; }

[ \t]+								;
#.*\n								{ VrmlCurrentLine++; }
\n									{ VrmlCurrentLine++; }
\"[^\"]*\"							{ yytext[yyleng-1] = '\0'; yylval.sval = yytext+1;  return STRING; }

TRUE					{ DEBUG("TRUE ");  yylval.bval = true;  return TRUEFALSE; }
FALSE					{ DEBUG("FALSE "); yylval.bval = false; return TRUEFALSE; }
ON						{ DEBUG("ON ");    yylval.bval = true;  return TRUEFALSE; }
OFF						{ DEBUG("FALSE "); yylval.bval = false; return TRUEFALSE; }

Anchor					{ return ANCHOR; }
Appearance				{ return APPEARANCE; }
AudioClip				{ return AUDIOCLIP; }
Background				{ return BACKGROUND; }
Billboard				{ return BILLBOARD; }
Box						{ return BOX; }
Collision				{ return COLLISION; }
Color					{ return COLOR; }
ColorInterpolator		{ return COLOR_INTERP; }
Cone					{ return CONE; }
Coordinate				{ return COORDINATE; }
CoordinateInterpolator	{ return COORDINATE_INTERP; }
Cylinder				{ return CYLINDER; }
CylinderSensor			{ return CYLINDER_SENSOR; }
DirectionalLight		{ return DIRECTIONALLIGHT; }
ElevationGrid			{ return ELEVATION_GRID; }
Extrusion				{ return EXTRUSION; }
Fog						{ return FOG; }
FontStyle				{ return FONTSTYLE; }
Group					{ return GROUP_NODE; }
ImageTexture			{ return IMAGE_TEXTURE; }
IndexedFaceSet			{ return INDEXEDFACESET; }
IndexedLineSet			{ return INDEXEDLINESET; }
Inline					{ return INLINE; }
LOD						{ return LOD; }
Material				{ return MATERIAL; }
MovieTexture			{ return MOVIE_TEXTURE; }
NULL					{ return NULL_STRING; }
NavigationInfo			{ return NAVIGATION_INFO; }
Normal					{ return NORMAL; }
NormalInterpolator		{ return NORMAL_INTERP; }
OrientationInterpolator	{ return ORIENTATION_INTERP; }
PixelTexture			{ return PIXEL_TEXTURE; }
PlaneSensor				{ return PLANE_SENSOR; }
PointLight				{ return POINTLIGHT; }
PointSet				{ return POINTSET; }
PositionInterpolator	{ return POSITION_INTERP; }
ProximitySensor			{ return PROXIMITY_SENSOR; }
ScalarInterpolator		{ return SCALAR_INTERP; }
Script					{ return SCRIPT; }
Shape					{ return SHAPE; }
Sound					{ return SOUND; }
Sphere					{ return SPHERE; }
SphereSensor			{ return SPHERE_SENSOR; }
SpotLight				{ return SPOTLIGHT; }
Switch					{ return SWITCH; }
Text					{ return ATEXT; }
TextureCoordinate		{ return TEXTURE_COORDINATE; }
TextureTransform		{ return TEXTURE_TRANSFORM; }
TimeSensor				{ return TIME_SENSOR; }
TouchSensor				{ return TOUCH_SENSOR; }
Transform				{ return TRANSFORM; }
Viewpoint				{ return VIEWPOINT; }
VisibilitySensor		{ return VISIBILITY_SENSOR; }
WorldInfo				{ return WORLD_INFO; }

ambientIntensity		{ return S_AMBIENT_INTENSITY; }
appearance				{ return S_APPEARANCE; }
attenuation				{ return S_ATTENUATION; }
autoOffset				{ return S_AUTO_OFFSET; }
avatarSize				{ return S_AVATAR_SIZE; }
axisOfRotation			{ return S_AXIS_OF_ROTATION;}
backUrl					{ return S_BACKURL; }
bboxCenter				{ return S_BBOXCENTER; }
bboxSize				{ return S_BBOXSIZE; }
beamWidth				{ return S_BERM_WIDTH; }
beginCap				{ return S_BEGIN_CAP; }
bottom					{ return S_BOTTOM; }
bottomRadius			{ return S_BOTTOMRADIUS; }
bottomUrl				{ return S_BOTTOMURL; }
ccw						{ DEBUG("ccw "); return S_CCW; }
center					{ return S_CENTER; }
children				{ return S_CHILDREN; }
choice					{ return S_CHOICE; }
collide					{ return S_COLLIDE; }
collideTime				{ return S_COLLIDETIME;}
color					{ return S_COLOR; }
colorIndex				{ return S_COLOR_INDEX; }
colorPerVertex			{ return S_COLOR_PER_VERTEX; }
convex					{ return S_CONVEX; }
coord					{ return S_COORD; }
coordIndex				{ return S_COORD_INDEX; }
creaseAngle				{ return S_CREASE_ANGLE;}
crossSection			{ return S_CROSS_SECTION; }
cutOffAngle				{ return S_CUTOFFANGLE; }
cycleInterval			{ return S_CYCLE_INTERVAL; }
description				{ return S_DESCRIPTION; }
diffuseColor			{ return S_DIFFUSECOLOR; }
directOutput			{ return S_DIRECT_OUTPUT; }
direction				{ return S_DIRECTION; }
diskAngle				{ return S_DISK_ANGLE; }
emissiveColor			{ return S_EMISSIVECOLOR; }
enabled					{ return S_ENABLED; }
endCap					{ return S_END_CAP; }
family					{ return S_FAMILY; }
fieldOfView				{ return S_FIELD_OF_VIEW; }
fogType					{ return S_FOG_TYPE; }
fontStyle				{ return S_FONTSTYLE; }
frontUrl				{ return S_FRONTURL; }
geometry				{ return S_GEOMETRY; }
groundAngle				{ return S_GROUNDANGLE; }
groundColor				{ return S_GROUNDCOLOR; }
headlight				{ return S_HEADLIGHT; }
height					{ return S_HEIGHT; }
horizontal				{ return S_HORIZONTAL; }
image					{ return S_IMAGE; }
info					{ return S_INFO; }
intensity				{ return S_INTENSITY; }
jump					{ return S_JUMP; }
justify					{ return S_JUSTIFY; }
key						{ return S_KEY; }
keyValue				{ return S_KEYVALUE; }
language				{ return S_LANGUAGE; }
leftToRight				{ return S_LEFT2RIGHT; }
leftUrl					{ return S_LEFTURL; }
length					{ return S_LENGTH; }
level					{ return S_LEVEL; }
location				{ return S_LOCATION; }
loop					{ return S_LOOP; }
material				{ return S_MATERIAL; }
maxAngle				{ return S_MAX_ANGLE; }
maxBack					{ return S_MAX_BACK; }
maxExtent				{ return S_MAX_EXTENT; }
maxFront				{ return S_MAX_FRONT; }
maxPosition				{ return S_MAX_POSITION; }
minAngle				{ return S_MIN_ANGLE; }
minBack					{ return S_MIN_BACK; }
minFront				{ return S_MIN_FRONT; }
minPosition				{ return S_MIN_POSITION; }
mustEvaluate			{ return S_MUST_EVALUATE; }
normal					{ return AS_NORMAL; }
normalIndex				{ return S_NORMAL_INDEX; }
normalPerVertex			{ return S_NORMAL_PER_VERTEX; }
offset					{ return S_OFFSET;}
on						{ return S_ON; }
orientation				{ return S_ORIENTATION; }
parameter				{ return S_PARAMETER; }
pitch					{ return S_PICTH; }
point					{ return S_POINT; }
position				{ return S_POSITION; }
priority				{ return S_PRIORITY; }
proxy					{ return S_PROXY; }
radius					{ return S_RADIUS; }
range					{ return S_RANGE; }
repeatS					{ return S_REPEAT_S; }
repeatT					{ return S_REPEAT_T; }
rightUrl				{ return S_RIGHTURL; }
rotation				{ return S_ROTATION; }
scale					{ return S_SCALE; }
scaleOrientation		{ return S_SCALEORIENTATION; }
shininess				{ return S_SHININESS; }
side					{ return S_SIDE; }
size					{ return S_SIZE; }
skyAngle				{ return S_SKYANGLE; }
skyColor				{ return S_SKYCOLOR; }
solid					{ return S_SOLID;}
source					{ return S_SOURCE; }
spacing					{ return S_SPACING; }
spatialize				{ return S_SPATIALIZE; }
specularColor			{ return S_SPECULARCOLOR; }
speed					{ return S_SPEED; }
spine					{ return S_SPINE; }
startTime				{ return S_STARTTIME; }
stopTime				{ return S_STOPTIME; }
string					{ return S_STRING; }
style					{ return S_STYLE; }
texCoord				{ return S_TEXCOORD; }
texCoordIndex			{ return S_TEXCOORD_INDEX;}
texture					{ return S_TEXTURE; }
textureTransform		{ return S_TEXTURETRANSFORM; }
title					{ return S_TITLE; }
top						{ return S_TOP; }
topToBottom				{ return S_TOP2BOTTOM; }
topUrl					{ return S_TOPURL; }
translation				{ return S_TRANSLATION; }
transparency			{ return S_TRANSPARENCY; }
type					{ return S_TYPE; }
url						{ return S_URL; }
vector					{ return S_VECTOR; }
visibilityLimit			{ return S_VISIBILITY_LIMIT; }
visibilityRange			{ return S_VISIBILITY_RANGE; }
whichChild				{ return S_WHICHCHILD; }
whichChoice				{ return S_WHICHCHOICE; }
xDimension				{ return S_XDIMENSION; }
xSpacing				{ return S_XSPACING; }
zDimension				{ return S_ZDIMENSION; }
zSpacing				{ return S_ZSPACING; }

DEF				{ return DEF;   }
USE				{ return USE;   }
PROTO			{ return PROTO; }
ROUTE			{ return ROUTE; }

[a-zA-Z_][a-zA-Z0-9_%\-]* { yytext[yyleng] = '\0'; yylval.sval = yytext; DEBUG("name "); return NAME; }

%%

int yywrap()
{
  return 1;
} 

