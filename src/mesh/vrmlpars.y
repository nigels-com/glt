/******************************************************************
*
*	VrmlPars.y
*
*	Copyright (C) Satoshi Konno 1996
*
* TODO:
*   Use left-recursion only!
*
******************************************************************/

%union {
bool     bval;
int		 ival;
float	 fval;
char	 *sval;
}

%token <bval> TRUEFALSE
%token <ival> NUMBER
%token <fval> AFLOAT
%token <sval> STRING NAME

%token ANCHOR APPEARANCE AUDIOCLIP BACKGROUND BILLBOARD BOX COLLISION COLOR
%token COLOR_INTERP COORDINATE COORDINATE_INTERP CYLINDER_SENSOR NULL_STRING
%token CONE CUBE CYLINDER DIRECTIONALLIGHT FONTSTYLE AERROR EXTRUSION
%token ELEVATION_GRID FOG INLINE MOVIE_TEXTURE NAVIGATION_INFO PIXEL_TEXTURE
%token GROUP_NODE INDEXEDFACESET INDEXEDLINESET S_INFO LOD MATERIAL NORMAL
%token POSITION_INTERP PROXIMITY_SENSOR SCALAR_INTERP SCRIPT SHAPE SOUND SPOTLIGHT
%token SPHERE_SENSOR ATEXT TEXTURE_COORDINATE TEXTURE_TRANSFORM TIME_SENSOR SWITCH
%token TOUCH_SENSOR VIEWPOINT VISIBILITY_SENSOR WORLD_INFO NORMAL_INTERP ORIENTATION_INTERP
%token POINTLIGHT POINTSET SPHERE PLANE_SENSOR TRANSFORM
%token DEF USE PROTO ROUTE

%token S_CHILDREN S_PARAMETER S_URL S_MATERIAL S_TEXTURETRANSFORM S_TEXTURE S_LOOP
%token S_STARTTIME S_STOPTIME S_GROUNDANGLE S_GROUNDCOLOR S_SPEED S_AVATAR_SIZE
%token S_BACKURL S_BOTTOMURL S_FRONTURL S_LEFTURL S_RIGHTURL S_TOPURL S_SKYANGLE S_SKYCOLOR 
%token S_AXIS_OF_ROTATION S_COLLIDE S_COLLIDETIME S_PROXY S_SIDE S_AUTO_OFFSET S_DISK_ANGLE
%token S_ENABLED S_MAX_ANGLE S_MIN_ANGLE S_OFFSET S_BBOXSIZE S_BBOXCENTER S_VISIBILITY_LIMIT
%token S_AMBIENT_INTENSITY AS_NORMAL S_TEXCOORD S_CCW S_COLOR_PER_VERTEX S_CREASE_ANGLE
%token S_NORMAL_PER_VERTEX S_XDIMENSION S_XSPACING S_ZDIMENSION S_ZSPACING S_BEGIN_CAP
%token S_CROSS_SECTION S_END_CAP S_SPINE S_FOG_TYPE S_VISIBILITY_RANGE S_HORIZONTAL S_JUSTIFY 
%token S_LANGUAGE S_LEFT2RIGHT S_TOP2BOTTOM IMAGE_TEXTURE S_SOLID S_KEY S_KEYVALUE 
%token S_REPEAT_S S_REPEAT_T S_CONVEX S_BOTTOM S_PICTH S_COORD S_COLOR_INDEX S_COORD_INDEX S_NORMAL_INDEX
%token S_MAX_POSITION S_MIN_POSITION S_ATTENUATION S_APPEARANCE S_GEOMETRY S_DIRECT_OUTPUT
%token S_MUST_EVALUATE S_MAX_BACK S_MIN_BACK S_MAX_FRONT S_MIN_FRONT S_PRIORITY S_SOURCE S_SPATIALIZE
%token S_BERM_WIDTH S_CHOICE S_WHICHCHOICE S_FONTSTYLE S_LENGTH S_MAX_EXTENT S_ROTATION S_SCALE
%token S_CYCLE_INTERVAL S_FIELD_OF_VIEW S_JUMP S_TITLE S_TEXCOORD_INDEX S_HEADLIGHT
%token S_TOP S_BOTTOMRADIUS S_HEIGHT S_POINT S_STRING S_SPACING S_SCALE S_HEADLIGHT S_TYPE
%token S_RADIUS S_ON S_INTENSITY S_COLOR S_DIRECTION S_SIZE S_FAMILY S_STYLE S_RANGE
%token S_CENTER S_TRANSLATION S_LEVEL S_DIFFUSECOLOR S_SPECULARCOLOR S_EMISSIVECOLOR S_SHININESS
%token S_TRANSPARENCY S_VECTOR S_POSITION S_ORIENTATION S_LOCATION S_ROTATION 
%token S_CUTOFFANGLE S_WHICHCHILD S_IMAGE S_SCALEORIENTATION S_DESCRIPTION  
 
%type <bval> SFBool
%type <fval> SFFloat SFTime
%type <ival> SFInt32
%type <sval> SFString  

%start Vrml

%{

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
#define alloca	malloc
#endif

typedef char 	*VrmlSFString;
typedef float	VrmlSFFloat;
typedef float	VrmlSFFloat2[2];
typedef float	VrmlSFFloat3[3];
typedef float	VrmlSFFloat4[4];
typedef int		VrmlSFInt32;
typedef float	VrmlSFVec2f[2];		
typedef float	VrmlSFVec4f[4];		
typedef bool	VrmlSFBool;
typedef float	VrmlSFRotation[4];		
typedef double	VrmlSFTime;		
typedef float	VrmlSFMatrix[4][4];		

VrmlSFVec2f		gVec2f;
Vector			gVec3f;
VrmlSFRotation	gRotation;
int				gWidth;
int				gHeight;
int				gComponents;

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

int yyerror(char *s);
int yyparseVrml(void);
int Vrmllex(void);

Mesh *yyVrmlMesh = 0;

%} 

%%

Vrml
	: VrmlNodes
	| error		{YYABORT;}
	| AERROR		{YYABORT;}
	;

VrmlNodes
	: SFNode VrmlNodes
	|
	;

GroupingNode
	: Anchor
	| Billboard
	| Collision
	| Group
	| Inline
	| Lod
	| Switch
	| Transform
	;

InterpolationNode
	: ColorInterp
	| CoordinateInterp
	| NormalInterp
	| OrientationInterp
	| PositionInterp
	| ScalarInterp
	;

SensorElement
	: CylinderSensor
	| PlaneSensor
	| SphereSensor
	| ProximitySensor
	| TimeSensor
	| TouchSensor
	| VisibilitySensor
	;

AppearanceNode
	: Appearance
	| FontStyle
	| ImageTexture
	| Material
	| MovieTexture
	| PixelTexture
	| TexTransform
	;

GeometryNode
	: Box
	| Cone
	| Cylinder
	| ElevationGrid
	| Extrusion
	| IdxFaceSet
	| IdxLineSet
	| PointSet
	| Sphere
	| Text
	;

LightNode
	: DirLight
	| SpotLight
	| PointLight
	;

SFNode
	: AudioClip
	| Background
	| Fog
	| FontStyle
	| WorldInfo
	| NavigationInfo
	| Viewpoint
	| WorldInfo
	| Script
	| Shape
	| Sound
	| InterpolationNode
	| LightNode
	| SensorElement
	| GroupingNode;

SFInt32
	: NUMBER { _vectorInt32.push_back($1); };

SFBool
	: TRUEFALSE { $$ = $1; };

SFString
	: STRING	{};

SFFloat
	: AFLOAT
		{
		}
	| NUMBER
		{
			$$ = (float)$1;
		};

SFTime
	: AFLOAT
	| NUMBER {$$ = (float)$1;};

SFColor
	: SFFloat SFFloat SFFloat 
	    {
			_color[0] = $1;
			_color[1] = $2;
			_color[2] = $3;
	    };

SFRotation
	: SFFloat SFFloat SFFloat SFFloat 
	    {
			gRotation[0] = $1;
			gRotation[1] = $2;
			gRotation[2] = $3;
			gRotation[3] = $4;
		};

SFImageHeader
	: NUMBER NUMBER NUMBER
	    {
			gWidth = $1;
			gHeight = $2;
			gComponents = $3;
	    };

SFImage
	: SFImageHeader SFImageList 
	;

SFVec2f
	: SFFloat SFFloat 
	    {
			gVec2f[0] = $1;
			gVec2f[1] = $2;
		};

SFVec3f
	: SFFloat SFFloat SFFloat { _vectorVector.push_back(Vector($1,$2,$3)); };

MFColor
	: SFColor					{}
	| '[' SFColorList ']'		{};

////////////////////////////////////////////////////////////

clearIntList:    { _vectorInt32.clear(); };	
clearVec3fList : { _vectorVector.clear(); };	
		
MFInt32
	: clearIntList SFInt32				{}
	| clearIntList '[' SFInt32List ']'	{}; 

MFVec3f
	: clearVec3fList SFVec3f
	| clearVec3fList '[' SFVec3fList ']'; 

MFFloat
	: SFFloat					{}
	| '[' SFFloatList ']'		{}; 

MFString
	: SFString					{}
	| '[' SFStringList ']'		{}; 

MFVec2f
	: SFVec2f					{}
	| '[' SFVec2fList ']'		{};

//////////////////////////////////////////////
// Notes:
//   Here we use left-recursion in order not
//   to exhaust the parser stack.  We've relaxed
//   the VRML rules that all items should be
//   comma seperated.
//

SFInt32List
	: SFInt32 					{}
	| SFInt32List     SFInt32	{}
	| SFInt32List ',' SFInt32	{}
	| SFInt32List ','           {};

SFFloatList
	: SFFloat					{}
	| SFFloatList     SFFloat	{}
	| SFFloatList ',' SFFloat	{}
	| SFFloatList ','			{};

SFStringList
	: SFString					{}
	| SFStringList     SFString	{}
	| SFStringList ',' SFString	{}
	| SFStringList ','			{};

SFColorList
	: SFColor					{}
	| SFColorList     SFColor	{}
	| SFColorList ',' SFColor	{}
	| SFColorList ','			{};

SFVec2fList
	: SFVec2f					{}
	| SFVec2fList     SFVec2f	{}
	| SFVec2fList ',' SFVec2f	{}
	| SFVec2fList ','			{};

SFVec3fList
	: SFVec3f					{}
	| SFVec3fList     SFVec3f	{}
	| SFVec3fList ',' SFVec3f	{}
	| SFVec3fList ','			{};

SFImageList
	: SFInt32					{}
	| SFImageList     SFInt32	{}
	| SFImageList ',' SFInt32	{}
	| SFImageList ','			{};

//////////////////////////////////////////////

SFRotationList
	: SFRotation
	| SFRotation ','
	| SFRotation ',' SFRotationList
	;

MFRotation
	: SFRotation
	| '[' SFRotationList ']'
	; 

/******************************************************************
*
*	Anchor
*
******************************************************************/

AnchorElements	
	: AnchorElement AnchorElements
	|
	;

AnchorElementParameterBegin 
	: S_PARAMETER
		{
		}
	;

AnchorElementURLBegin 
	: S_URL	
		{
		}
	;

bboxCenter
	: S_BBOXCENTER	SFVec3f
		{
		}
	;

bboxSize
	: S_BBOXSIZE	SFVec3f
		{
		}
	;

AnchorElement 
	: children
	| S_DESCRIPTION	SFString
		{
		}

	| AnchorElementParameterBegin MFString 
		{
		}
	| AnchorElementURLBegin MFString
		{
		}
	| bboxCenter
	| bboxSize
	;

AnchorBegin
	: ANCHOR 
		{   
		}	
	;

Anchor
	: AnchorBegin '{' AnchorElements '}'
		{
		}
	;

/******************************************************************
*
*	Appearance
*
******************************************************************/

AppearanceNodes
	: AppearanceNode AppearanceNodes
	|
	;

AppearanceNode
	: S_MATERIAL NULL_STRING
	| S_MATERIAL Material
	| S_TEXTURE NULL_STRING
	| S_TEXTURE ImageTexture
	| S_TEXTURE MovieTexture
	| S_TEXTURE PixelTexture
	| S_TEXTURETRANSFORM NULL_STRING
	| S_TEXTURETRANSFORM TexTransform
	;
	
AppearanceBegin
	: APPEARANCE  
		{
		}
		;

Appearance
	:  AppearanceBegin '{' AppearanceNodes '}'
		{
		}
	;

/******************************************************************
*
*	Audio Clip
*
******************************************************************/

AudioClipElements
	: AudioClipElement AudioClipElements
	|
	;

AudioClipURL
	: S_URL
		{
		}
	;

AudioClipElement
	: S_DESCRIPTION			SFString
		{
		}
	| S_LOOP					SFBool
		{
		}
	| S_PICTH					SFFloat
		{
		}
	| S_STARTTIME				SFTime
		{
		}
	| S_STOPTIME				SFTime
		{
		}
	| AudioClipURL	MFString
		{
		}
	;

AudioClipBegin
	: AUDIOCLIP 
		{
		}
	;

AudioClip
	: AudioClipBegin '{' AudioClipElements '}'
		{
		}
	;

/******************************************************************
*
*	Background
*
******************************************************************/

BackGroundElements
	: BackGroundElement BackGroundElements
	|
	;

BackGroundBackURL
	: S_BACKURL
		{
		}
	;

BackGroundBottomURL
	: S_BOTTOMURL
		{
		}
	;

BackGroundFrontURL
	: S_FRONTURL
		{
		}
	;

BackGroundLeftURL
	: S_LEFTURL	
		{
		}
	;

BackGroundRightURL
	: S_RIGHTURL
		{
		}
	;

BackGroundTopURL
	: S_TOPURL
		{
		}
	;

BackGroundGroundAngle
	: S_GROUNDANGLE
		{
		}
	;

BackGroundGroundColor
	: S_GROUNDCOLOR
		{
		}
	;

BackGroundSkyAngle
	: S_SKYANGLE
		{
		}
	;

BackGroundSkyColor
	: S_SKYCOLOR
		{
		}
	;

BackGroundElement
	: BackGroundGroundAngle	MFFloat
		{
		}
	| BackGroundGroundColor	MFColor
		{
		}
	| BackGroundBackURL	MFString
		{
		}
	| BackGroundBottomURL	MFString
		{
		}
	| BackGroundFrontURL	MFString
		{
		}
	| BackGroundLeftURL	MFString
		{
		}
	| BackGroundRightURL	MFString
		{
		}
	| BackGroundTopURL		MFString
		{
		}
	| BackGroundSkyAngle	MFFloat
		{
		}
	| BackGroundSkyColor	MFColor
		{
		}
	;

BackgroundBegin
	: BACKGROUND 
		{
		}
	;

Background
	: BackgroundBegin '{' BackGroundElements '}'
		{
		}
	;

/******************************************************************
*
*	Billboard
*
******************************************************************/

BillboardElements
	: BillboardElement BillboardElements
	|
	;

BillboardElement
	: children
	| S_AXIS_OF_ROTATION	SFVec3f
		{
		}
	| bboxCenter
	| bboxSize
	;

BillboardBegin
	: BILLBOARD 
		{   
		}	
	;

Billboard
	: BillboardBegin '{' BillboardElements '}'
		{
		}
	;

/******************************************************************
*
*	Box
*
******************************************************************/

BoxElements
	: BoxElement BoxElements
	|
	;

BoxElement
	: S_SIZE SFVec3f
		{
		}
	;

BoxBegin
	: BOX 
		{
		}
	;

Box					
	: BoxBegin '{' BoxElements '}'
		{
		}
	;

/******************************************************************
*
*	Children
*
******************************************************************/

childrenElements
	:										{}
	| childrenElement						{}
	| childrenElements childrenElement		{}
	| childrenElements ',' childrenElement	{};

childrenElement
	: SFNode			{};

children
	: S_CHILDREN '[' childrenElements ']'
	| S_CHILDREN childrenElements
	;

/******************************************************************
*
*	Collision
*
******************************************************************/

CollisionElements
	: CollisionElement CollisionElements
	|
	;

CollisionElementProxyBegin
	: S_PROXY
		{
		}
	;

CollisionElement
	: children
	| S_COLLIDE					SFBool
		{
		}
	| bboxCenter
	| bboxSize
	| CollisionElementProxyBegin	SFNode
		{
		}
	;

CollisionBegin
	: COLLISION 
		{   
		}	
	;

Collision
	: CollisionBegin '{' CollisionElements '}'
		{
		}
	;

/******************************************************************
*
*	Color
*
******************************************************************/

ColorElements
	: ColorElement ColorElements
	|
	;

ColorElement
	: S_COLOR MFColor 				
	;

ColorBegin
	: COLOR  
		{
		}
	;

Color
	: ColorBegin '{' ColorElements '}'
		{
		}
	;
		                                                                                                                                                                                                                                                                                          
/******************************************************************
*
*	ColorInterpolator
*
******************************************************************/

ColorInterpElements
	: ColorInterpElement ColorInterpElements
	|
	;

InterpolateKey
	: S_KEY
		{
		}
	;

InterporlateKeyValue
	: S_KEYVALUE
		{
		}
	;

ColorInterpElement
	: InterpolateKey		MFFloat
		{
		}
	| InterporlateKeyValue	MFColor
		{
		}
	;

ColorInterpBegin
	: COLOR_INTERP  
		{
		}
	;

ColorInterp
	: ColorInterpBegin '{' ColorInterpElements '}'
		{
		}
	;

/******************************************************************
*
*   Cone
*
******************************************************************/

ConeElements
	: ConeElement ConeElements
	|
	;

ConeElement
	: S_SIDE			SFBool
		{
		}
	| S_BOTTOM		SFBool
		{
		}
	| S_BOTTOMRADIUS	SFFloat
		{
		}
	| S_HEIGHT		SFFloat
		{
		}
	;

ConeBegin
	: CONE 
		{
		}
	;

Cone
	: ConeBegin '{' ConeElements '}'
		{
		}
	;

/******************************************************************
*
*   Coordinate
*
******************************************************************/

CoordinateElements
	:  S_POINT	MFVec3f
	|
	;

CoordinateDef
	: DEF NAME	{}
	|		{};

CoordinateBegin
	: CoordinateDef COORDINATE 
		{
		}
	;

Coordinate
	: CoordinateBegin '{' CoordinateElements '}' 	{}
	| USE NAME					{};

/******************************************************************
*
*	ColorInterpolator
*
******************************************************************/

CoordinateInterpElements
	: CoordinateInterpElement CoordinateInterpElements
	|
	;

CoordinateInterpElement
	: InterpolateKey		MFFloat
		{
		}
	| InterporlateKeyValue	MFVec3f
		{
		}
	;

CoordinateInterpBegin
	: COORDINATE_INTERP  
		{
		}
	;

CoordinateInterp
	: CoordinateInterpBegin '{' CoordinateInterpElements '}'
		{
		}
	;

/******************************************************************
*
*   Cylinder
*
******************************************************************/

CylinderElements		
	: CylinderElement CylinderElements
	|
	;

CylinderElement
	: S_SIDE		SFBool
		{
		}
	| S_BOTTOM		SFBool
		{
		}
	| S_TOP		SFBool
		{
		}
	| S_RADIUS		SFFloat
		{
		}
	| S_HEIGHT		SFFloat
		{
		}
	;

CylinderBegin
	: CYLINDER  
		{
		}
	;

Cylinder
	: CylinderBegin '{' CylinderElements '}'
		{
		}
	;

/******************************************************************
*
*   CylinderSensor
*
******************************************************************/

CylinderSensorElements
	: CylinderSensorElement CylinderSensorElements
	|
	;

CylinderSensorElement
	: S_AUTO_OFFSET			SFBool
		{
		}
	| S_DISK_ANGLE			SFFloat
		{
		}
	| S_ENABLED				SFBool
		{
		}
	| S_MAX_ANGLE				SFFloat
		{
		}
	| S_MIN_ANGLE				SFFloat
		{
		}
	| S_OFFSET				SFFloat
		{
		}
	;


CylinderSensorBegin
	: CYLINDER_SENSOR 
		{
		}
	;

CylinderSensor
	: CylinderSensorBegin '{' CylinderSensorElements '}'
		{
		}
	;

/******************************************************************
*
*   Directional Light
*
******************************************************************/

DirLightElements		
	: DirLightElement DirLightElements
	|
	;

DirLightElement
	: S_ON				SFBool
		{
		}
	| S_INTENSITY			SFFloat
		{
		}
	| S_COLOR		SFColor
		{
		}
	| S_DIRECTION			SFVec3f
		{
		}
	| S_AMBIENT_INTENSITY	SFFloat
		{
		}
	;

DirLightBegin			
	: DIRECTIONALLIGHT 
		{
		}
	;

DirLight
	: DirLightBegin '{' DirLightElements '}'
		{
		}
	;

/******************************************************************
*
*   ElevationGrid
*
******************************************************************/

ElevationGridElements
	: ElevationGridElement ElevationGridElements
	|
	;

ElevationGridHeight
	: S_HEIGHT
		{
		}
	;


ElevationGridElement
	: S_COLOR		NULL_STRING
	| S_COLOR		Color
	| AS_NORMAL		NULL_STRING
	| AS_NORMAL		Normal
	| S_TEXCOORD		NULL_STRING
	| S_TEXCOORD		TexCoordinate
	| ElevationGridHeight	MFFloat
		{
		}
	| S_CCW			SFBool
		{
		}
	| S_CREASE_ANGLE	SFFloat
		{
		}
	| S_SOLID		SFBool
		{
		}
	| S_COLOR_PER_VERTEX	SFBool
		{
		}
	| S_NORMAL_PER_VERTEX	SFBool
		{
		}
	| S_XDIMENSION		SFInt32
		{
		}
	| S_XSPACING		SFFloat
		{
		}
	| S_ZDIMENSION		SFInt32
		{
		}
	| S_ZSPACING		SFFloat
		{
		}
	;

ElevationGridBegin
	: ELEVATION_GRID 
		{
		}
	;

ElevationGrid
	: ElevationGridBegin '{' ElevationGridElements '}'
		{
		}
	;

/******************************************************************
*
*   Extrusion
*
******************************************************************/

ExtrusionElements
	: ExtrusionElement ExtrusionElements
	|
	;

ExtrusionCrossSection
	: S_CROSS_SECTION
		{
		}
	;

ExtrusionOrientation
	: S_ORIENTATION
		{
		}
	;

ExtrusionScale
	: S_SCALE
		{
		}
	;

ExtrusionSpine
	: S_SPINE
		{
		}
	;

ExtrusionElement
	: S_BEGIN_CAP			SFBool
		{
		}
	| S_CCW					SFBool 
		{
		}
	| S_CONVEX				SFBool
		{
		}
	| S_CREASE_ANGLE		SFFloat
		{
		}
	| S_SOLID				SFBool
		{
		}
	| ExtrusionCrossSection MFVec2f
		{
		}
	| S_END_CAP			SFBool
		{
		}
	| ExtrusionOrientation	MFRotation
		{
		}
	| ExtrusionScale MFVec2f
		{
		}
	| ExtrusionSpine MFVec3f
		{
		}
	;

ExtrusionBegin
	: EXTRUSION  
		{
		}
	;

Extrusion
	: ExtrusionBegin '{' ExtrusionElements '}'
		{
		}
	;

/******************************************************************
*
*   Fog
*
******************************************************************/

FogElements
	: FogElement FogElements
	|
	;

FogElement
	: S_COLOR		SFColor
		{
		}
	| S_FOG_TYPE			SFString
		{
		}
	| S_VISIBILITY_RANGE			SFFloat
		{
		}
	;

FogBegin
	: FOG  
		{
		}
	;

Fog
	: FogBegin '{' FogElements '}'
		{
		}
	;

/******************************************************************
*
*   Font Style 
*
******************************************************************/

FontStyleElements
	: FontStyleElement FontStyleElements
	|
	;

FontStyleJustify
	: S_JUSTIFY 
		{
		}
	;

FontStyleElement
	: S_FAMILY		SFString
		{
		}
	| S_HORIZONTAL	SFBool
		{
		}
	| FontStyleJustify		MFString
		{
		}
	| S_LANGUAGE	SFString
		{
		}
	| S_LEFT2RIGHT	SFBool
		{
		}
	| S_SIZE		SFFloat
		{
		}
	| S_SPACING		SFFloat
		{
		}
	| S_STYLE			SFString
		{
		}
	| S_TOP2BOTTOM	SFBool
		{
		}
	;

FontStyleBegin	
	: FONTSTYLE '{'
		{
		}
	;

FontStyle		
	: FontStyleBegin FontStyleElements '}'
		{
		}
	;

/******************************************************************
*
*   Group
*
******************************************************************/

GroupElements
	: GroupElement GroupElements
	|
	;

GroupElement
	: children
	| bboxCenter
	| bboxSize
	;

GroupDef
	: DEF NAME	{}
	|		{};

GroupBegin
	: GroupDef GROUP_NODE	{};

Group
	: GroupBegin '{' GroupElements '}'	{}
	| USE NAME				{};

/******************************************************************
*
*   ImageTexture
*
******************************************************************/

ImgTexElements
	: ImgTexElement ImgTexElements
	|
	;

ImgTexURL
	: S_URL
		{
		}
	;

ImgTexElement
	: ImgTexURL	MFString
		{
		}
	| S_REPEAT_S			SFBool
		{
		}
	| S_REPEAT_T			SFBool
		{
		}
	;

ImageTextureBegin
	: IMAGE_TEXTURE 
		{
		}
	;

ImageTexture
	: ImageTextureBegin '{' ImgTexElements '}'
		{
		} 
	;

/******************************************************************
*
*	Shape
*
******************************************************************/

ShapeElements
	: ShapeElements ShapeElement			{}
	|										{};

ShapeElement
	: S_APPEARANCE		NULL_STRING
	| S_APPEARANCE		AppearanceNode
	| S_GEOMETRY		NULL_STRING
	| S_GEOMETRY		GeometryNode
	;

ShapeDef
	: DEF NAME	{}
	|		    {};

ShapeBegin
	: ShapeDef SHAPE  
		{
			#ifdef YYDEBUG
			cout << "Shape" << endl;
			#endif

			_faceSet.clear();
			_material.clear();
		};

ShapeEnd
	:
		{
			if (VrmlParseShape)
			{
				Shape *shape = new Shape();
				shape->faces    = _faceSet;
				shape->material = _material;
				GltShapePtr ptr(shape);
				VrmlParseShape(ptr);
			}
		};

Shape
	: ShapeBegin '{' ShapeElements '}' ShapeEnd
		{
		};


/******************************************************************
*
*   Material
*
******************************************************************/

MaterialElements	
	: MaterialElement MaterialElements		{}
	|										{};

MaterialElement	
	: S_AMBIENT_INTENSITY	SFFloat	{ assert(_material.get()); _material->ambientIntensity = $2;     }
	| S_DIFFUSECOLOR		SFColor { assert(_material.get()); _material->diffuseColor     = _color; }
	| S_EMISSIVECOLOR		SFColor { assert(_material.get()); _material->emissiveColor    = _color; }
	| S_SHININESS			SFFloat { assert(_material.get()); _material->shininess        = $2;     }
	| S_SPECULARCOLOR		SFColor { assert(_material.get()); _material->specularColor    = _color; }
	| S_TRANSPARENCY		SFFloat { assert(_material.get()); _material->transparency     = $2;     };

MaterialDef
	: DEF NAME	{}
	|		    {};

MaterialBegin	
	: MaterialDef MATERIAL
		{
			#ifdef YYDEBUG
			cout << "Material" << endl;
			#endif

			_material = new Material();
		};

MaterialEnd
	:
		{
			if (VrmlParseMaterial)
				VrmlParseMaterial(_material);
		};

Material
	: MaterialBegin '{' MaterialElements '}' MaterialEnd {}
	| USE NAME								             {};


/******************************************************************
*
*   Indexed Face Set
*
******************************************************************/

ColorIndex	
	: S_COLOR_INDEX				{};

CoordIndex	
	: S_COORD_INDEX				{};

NormalIndex
	: S_NORMAL_INDEX			{};

TextureIndex
	: S_TEXCOORD_INDEX			{};

IdxFaceSetElements
	: IdxFaceSetElement IdxFaceSetElements		{}
	|											{};

IdxFaceSetElement
	: S_COLOR				Color			{}
	| S_COORD				Coordinate		{ assert(_faceSet.get()); _faceSet->coord  = _vectorVector; }
	| AS_NORMAL				Normal			{ assert(_faceSet.get()); _faceSet->normal = _vectorVector; }
	| S_TEXCOORD			TexCoordinate	{}
	| S_CCW					SFBool			{ assert(_faceSet.get()); _faceSet->ccw             = $2; }
	| S_CONVEX				SFBool			{ assert(_faceSet.get()); _faceSet->convex          = $2; }
	| S_SOLID				SFBool			{ assert(_faceSet.get()); _faceSet->solid           = $2; }
	| S_CREASE_ANGLE		SFFloat			{ assert(_faceSet.get()); _faceSet->creaseAngle     = $2; }
	| S_COLOR_PER_VERTEX	SFBool			{ assert(_faceSet.get()); _faceSet->colorPerVertex  = $2; }
	| S_NORMAL_PER_VERTEX	SFBool			{ assert(_faceSet.get()); _faceSet->normalPerVertex = $2; }
	| CoordIndex			MFInt32			{ assert(_faceSet.get()); _faceSet->coordIndex    = _vectorInt32; }
	| NormalIndex			MFInt32			{ assert(_faceSet.get()); _faceSet->normalIndex   = _vectorInt32; }
	| ColorIndex			MFInt32			{ assert(_faceSet.get()); _faceSet->colorIndex    = _vectorInt32; }
	| TextureIndex			MFInt32			{ assert(_faceSet.get()); _faceSet->texCoordIndex = _vectorInt32; };

IdxFaceSetDef
	: DEF NAME 	{}
	|			{};

IdxFaceSetBegin
	: IdxFaceSetDef INDEXEDFACESET  
		{
			#ifdef YYDEBUG
			cout << "Indexed Face Set" << endl;
			#endif

			_faceSet = new IndexedFaceSet();
		};

IdxFaceSetEnd
	:
		{
			assert(_faceSet.get());

			#ifdef YYDEBUG
			cout << _faceSet->coord.size()      << " points."       << endl;
			cout << _faceSet->normal.size()     << " normals."      << endl;
			cout << _faceSet->coordIndex.size() << " face entries." << endl;
			#endif

			if (VrmlParseIndexedFaceSet)
				VrmlParseIndexedFaceSet(_faceSet);
		};

IdxFaceSet
	: IdxFaceSetBegin '{' IdxFaceSetElements '}' IdxFaceSetEnd	{}
	| USE NAME													{};

/******************************************************************
*
*   Indexed Line Set
*
******************************************************************/

IdxLineSetElements
	: IdxLineSetElement IdxLineSetElements
	|
	;

IdxLineSetElement
	: S_COLOR				Color
	| S_COORD				Coordinate
	| S_COLOR_PER_VERTEX	SFBool
		{
		}
	| ColorIndex		MFInt32
		{
		}
	| CoordIndex		MFInt32
		{
		}
	;

IdxLineSetBegin	
	: INDEXEDLINESET '{' 
		{
		}
	;

IdxLineSet		
	: IdxLineSetBegin IdxLineSetElements '}'
		{
		}
	;

/******************************************************************
*
*   Inline
*
******************************************************************/

InlineElements		
	: InlineElement InlineElements
	|
	;

InlineURL 
	: S_URL	
		{
		}
	;

InlineElement
	: InlineURL	MFString
		{
		}
	| bboxCenter
	| bboxSize
	;

InlineBegin
	: INLINE
		{   
		}	
	;

Inline
	: InlineBegin '{' InlineElements '}'
		{
		}
	;

/************************************************************
*
*   LOD
*
************************************************************/

LodElements		
	: LodElement LodElements
	|
	;

LodRange
	:  S_RANGE
		{
		}
	;


LodLevel
	: S_LEVEL
		{
		}
	;

LodElement
	: LodRange	    MFFloat
		{
		}
	| S_CENTER			SFVec3f
		{
		}
	| LodLevel	SFNode
		{
		}
	| LodLevel		'[' VrmlNodes ']'
		{
		}
	;

LodBegin
	: LOD
		{   
		}	
	;

Lod				
	: LodBegin '{' LodElements '}'
		{
		}
	;

/******************************************************************
*
*	MovieTexture
*
******************************************************************/

MovieTextureElements
	: MovieTextureElement MovieTextureElements
	|
	;

MovieTextureURL
	: S_URL
		{
		}
	;

MovieTextureElement	
	: S_LOOP				SFBool
		{
		}
	| S_SPEED				SFFloat
		{
		}
	| S_STARTTIME			SFTime
		{
		}
	| S_STOPTIME			SFTime
		{
		}
	| MovieTextureURL MFString
		{
		}
	| S_REPEAT_S			SFBool
		{
		}
	| S_REPEAT_T			SFBool
		{
		}
	;

MovieTextureBegin
	: MOVIE_TEXTURE  
		{
		}
	;

MovieTexture
	: MovieTextureBegin '{' MovieTextureElements '}'
		{
		}
	;

/******************************************************************
*
*	Navigation Info
*
******************************************************************/

NavigationInfoElements
	: NavigationInfoElement NavigationInfoElements
	|
	;

NavigationInfoAvatarSize
	: S_AVATAR_SIZE
		{
		}
	;

NavigationInfoType
	: S_TYPE
		{
		}
	;

NavigationInfoElement
	: NavigationInfoAvatarSize	MFFloat
		{
		}
	| S_HEADLIGHT						SFBool
		{
		}
	| S_SPEED							SFFloat
		{
		}
	| NavigationInfoType		MFString
		{
		}
	| S_VISIBILITY_LIMIT				SFFloat
		{
		}
	;

NavigationInfoBegin
	: NAVIGATION_INFO
		{
		}
	;

NavigationInfo		
	: NavigationInfoBegin '{' NavigationInfoElements '}'
		{
		}
	;

/******************************************************************
*
*   Normal
*
******************************************************************/

NormalElements	
	: NormalElement NormalElements
	|
	;

NormalElement
	: S_VECTOR	MFVec3f
	;

NormalBegin
	: NORMAL  
		{
		}
	;

Normal
	: NormalBegin '{' NormalElements '}'
		{
			#ifdef YYDEBUG
			cout << _vectorVector.size() << " normals." << endl;
			#endif
		}
	;

/******************************************************************
*
*	Normal Interpolator
*
******************************************************************/

NormalInterpElements	
	: NormalInterpElement NormalInterpElements
	|
	;

NormalInterpElement
	: InterpolateKey			MFFloat
		{
		}
	| InterporlateKeyValue		MFVec3f
		{
		}
	;

NormalInterpBegin
	: NORMAL_INTERP
		{
		}
	;

NormalInterp
	: NormalInterpBegin '{'	NormalInterpElements '}'
		{
		}
	;

/******************************************************************
*
*	Orientation Interpolator
*
******************************************************************/

OrientationInterpElements
	: OrientationInterpElement OrientationInterpElements
	|
	;

OrientationInterpElement
	: InterpolateKey			MFFloat
		{
		}
	| InterporlateKeyValue		MFRotation
		{
		}
	;

OrientationInterpBegin
	: ORIENTATION_INTERP
		{
		}
	;

OrientationInterp
	: OrientationInterpBegin '{' OrientationInterpElements '}'
		{
		}
	;

/******************************************************************
*
*	Pixel Texture
*
******************************************************************/

PixelTextureElements
	: PixelTextureElement PixelTextureElements
	|
	;

PixelTextureImage
	: S_IMAGE NUMBER NUMBER NUMBER  
		{
		}
	;

PixelTextureElement
	: PixelTextureImage SFImageList
		{
		}
	| S_REPEAT_S		SFBool
		{
		}
	| S_REPEAT_T		SFBool
		{
		}
	;

PixelTextureBegin
	: PIXEL_TEXTURE 
		{
		}
	;

PixelTexture		
	: PixelTextureBegin '{' PixelTextureElements '}'
		{
		}
	;

/******************************************************************
*
*	Plane Sensor
*
******************************************************************/

PlaneSensorElements
	: PlaneSensorElement PlaneSensorElements
	|
	;

PlaneSensorElement
	: S_AUTO_OFFSET	SFBool
		{
		}
	| S_ENABLED		SFBool
		{
		}
	| S_MAX_POSITION	SFVec2f
		{
		}
	| S_MIN_POSITION	SFVec2f
		{
		}
	| S_OFFSET		SFVec3f
		{
		}
	;

PlaneSensorBegin
	: PLANE_SENSOR
		{
		}
	;

PlaneSensor
	: PlaneSensorBegin '{' PlaneSensorElements '}'
		{
		}
	;


/******************************************************************
*
*   Point Light
*
******************************************************************/

PointLightNodes
	: PointLightNode PointLightNodes
	|
	;

PointLightNode
	: S_AMBIENT_INTENSITY	SFFloat
		{
		}
	| S_ATTENUATION		SFVec3f
		{
		}
	| S_COLOR		SFColor
		{
		}
	| S_INTENSITY	SFFloat
		{
		}
	| S_LOCATION	SFVec3f
		{
		}
	| S_ON		SFBool
		{
		}
	| S_RADIUS	SFFloat
		{
		}
	;

PointLightBegin	
	: POINTLIGHT  
		{
		}
	;

PointLight
	: PointLightBegin '{' PointLightNodes '}'
		{
		}
	;

/******************************************************************
*
*   Point Set
*
******************************************************************/

PointSetElements		
	: PointSetElement PointSetElements
	|
	;

PointSetElement
	: S_COLOR	NULL_STRING
	| S_COLOR	Color
	| S_COORD	NULL_STRING
	| S_COORD	Coordinate
	;


PointSetBegin
	: POINTSET
		{
		};

PointSet	
	: PointSetBegin '{' PointSetElements '}'
		{
		};

/******************************************************************
*
*	Position Interpolator
*
******************************************************************/

PositionInterpElements
	: PositionInterpElement PositionInterpElements
	|
	;

PositionInterpElement
	: InterpolateKey			MFFloat
		{
		}
	| InterporlateKeyValue		MFVec3f
		{
		}
	;

PositionInterpBegin
	: POSITION_INTERP
		{
		}
	;

PositionInterp
	: PositionInterpBegin '{' PositionInterpElements '}'
		{
		}
	;

/******************************************************************
*
*	Proximity Sensor
*
******************************************************************/

ProximitySensorElements
	: ProximitySensorElement ProximitySensorElements
	|
	;

ProximitySensorElement
	: S_CENTER		SFVec3f
		{
		}
	| S_SIZE		SFVec3f
		{
		}
	| S_ENABLED		SFBool
		{
		}
	;

ProximitySensorBegin
	: PROXIMITY_SENSOR
		{
		}
	;

ProximitySensor		
	: ProximitySensorBegin '{' ProximitySensorElements '}'
		{
		}
	;

/******************************************************************
*
*	Scalar Interpolator
*
******************************************************************/

ScalarInterpElements	
	: ScalarInterpElement ScalarInterpElements
	|
	;

ScalarInterpElement
	: InterpolateKey			MFFloat
		{
		}
	| InterporlateKeyValue		MFFloat
		{
		}
	;

ScalarInterpBegin
	: SCALAR_INTERP
		{
		}
	;

ScalarInterp
	: ScalarInterpBegin '{' ScalarInterpElements '}'
		{
		}
	;

/******************************************************************
*
*	Script
*
******************************************************************/

ScriptElements
	: ScriptElement ScriptElements
	|
	;

ScriptURL
	: S_URL
		{
		}
	;

ScriptElement
	: ScriptURL	MFString
		{
		}
	| S_DIRECT_OUTPUT		SFBool
		{
		}
	| S_MUST_EVALUATE		SFBool
		{
		}
	;

ScriptBegin
	: SCRIPT
		{
		}
	;

Script
	: ScriptBegin '{' ScriptElements '}'
		{
		}
	;

/******************************************************************
*
*	Sound
*
******************************************************************/

SoundElements
	: SoundElement SoundElements
	|
	;

SoundElement
	: S_DIRECTION			SFVec3f
		{
		}
	| S_INTENSITY			SFFloat
		{
		}
	| S_LOCATION			SFVec3f
		{
		}
	| S_MAX_BACK			SFFloat
		{
		}
	| S_MAX_FRONT			SFFloat
		{
		}
	| S_MIN_BACK			SFFloat
		{
		}
	| S_MIN_FRONT			SFFloat
		{
		}
	| S_PRIORITY			SFFloat
		{
		}
	| S_SOURCE			NULL_STRING
	| S_SOURCE			AudioClip
	| S_SOURCE			MovieTexture
	| S_SPATIALIZE		SFBool
		{
		}
	;

SoundBegin
	: SOUND
		{
		}
	;

Sound
	: SoundBegin '{' SoundElements '}'
		{
		}
	;

/******************************************************************
*
*   Sphere
*
******************************************************************/

SphereElements
	: SphereElement SphereElements
	|
	;

SphereElement
	: S_RADIUS	SFFloat
		{
		}
	;

SphereBegin	
	: SPHERE  
		{
		}
	;

Sphere
	: SphereBegin '{' SphereElements '}'
		{
		}
	;

/******************************************************************
*
*	Spehere Sensor
*
******************************************************************/

SphereSensorElements
	: SphereSensorElement SphereSensorElements
	|
	;

SphereSensorElement
	: S_AUTO_OFFSET	SFBool
		{
		}
	| S_ENABLED		SFBool
		{
		}
	| S_OFFSET		SFRotation
		{
		}
	;

SphereSensorBegin
	: SPHERE_SENSOR
		{
		}
	;

SphereSensor
	: SphereSensorBegin '{' SphereSensorElements '}'
		{
		}
	;

/******************************************************************
*
*   Spot Light
*
******************************************************************/

SpotLightElements	
	: SpotLightElement SpotLightElements
	|
	;

SpotLightElement	
	: S_AMBIENT_INTENSITY	SFFloat
		{
		}
	| S_ATTENUATION		SFVec3f
		{
		}
	| S_BERM_WIDTH		SFFloat
		{
		}
	| S_COLOR		SFColor
		{
		}
	| S_CUTOFFANGLE		SFFloat
		{
		}
	| S_DIRECTION			SFVec3f
		{
		}
	| S_INTENSITY			SFFloat
		{
		}
	| S_LOCATION			SFVec3f
		{
		}
	| S_ON				SFBool
		{
		}
	| S_RADIUS			SFFloat
		{
		}
	;

SpotLightBegin
	: SPOTLIGHT 
		{
		}
	;

SpotLight		
	: SpotLightBegin '{' SpotLightElements '}'
		{
		}
	;

/******************************************************************
*
*   Switch
*
******************************************************************/

SwitchElements	
	: SwitchElement SwitchElements
	|
	;

SwitchChoice
	: S_CHOICE
		{
		}
	;

SwitchElement
	: SwitchChoice	SFNode
		{
		}
	| SwitchChoice '[' VrmlNodes ']'
		{
		}
	| S_WHICHCHOICE	SFInt32
		{
		}
	;

SwitchDef
	: DEF NAME 	{}
	|		{};

SwitchBegin
	: SwitchDef SWITCH	{};

Switch			
	: SwitchBegin '{' SwitchElements '}'	{}
	| USE NAME				{};

/******************************************************************
*
*   Text
*
******************************************************************/

TextElements
	: TextElement TextElements
	|
	;

TextString
	: S_STRING
		{
		}
	;

TextLength
	: S_LENGTH
		{
		}
	;

TextElement
	: TextString	MFString
		{
		}
	| S_FONTSTYLE	FontStyle
	| TextLength	MFFloat
	| S_MAX_EXTENT	SFFloat
		{
		}
	;


TextBegin
	: ATEXT
		{
		}
	;

Text
	: TextBegin '{' TextElements '}'
		{
		}
	;

/******************************************************************
*
*   TexCoordinate
*
******************************************************************/

TexCoordElements	
	: TexCoordElement TexCoordElements
	|
	;

TexCoordElement
	: S_POINT			MFVec2f
	;


TexCoordBegin
	: TEXTURE_COORDINATE  
		{
		}
	;

TexCoordinate
	: TexCoordBegin '{' TexCoordElements '}'
		{
		}
	;

/******************************************************************
*
*   TextureTransform
*
******************************************************************/

TextureTransformElements
	: TextureTransformElement TextureTransformElements
	|
	;

TextureTransformElement
	: S_CENTER			SFVec2f
		{
		}
	| S_ROTATION		SFFloat
		{
		}
	| S_SCALE			SFVec2f
		{
		}
	| S_TRANSLATION		SFVec2f
		{
		}
	;


TexTransformBegin
	: TEXTURE_TRANSFORM 
		{
		}
	;

TexTransform
	: TexTransformBegin '{' TextureTransformElements '}'
		{
		}
	;

/******************************************************************
*
*   TimeSensor
*
******************************************************************/

TimeSensorElements	
	: TimeSensorElement TimeSensorElements
	|
	;

TimeSensorElement
	: S_CYCLE_INTERVAL	SFTime
		{
		}
	| S_ENABLED			SFBool
		{
		}
	| S_LOOP			SFBool
		{
		}
	| S_STARTTIME		SFTime
		{
		}
	| S_STOPTIME		SFTime
		{
		}
	;

TimeSensorDef
	: DEF NAME	{}
	|		    {};

TimeSensorBegin
	: TimeSensorDef TIME_SENSOR {};

TimeSensor
	: TimeSensorBegin '{' TimeSensorElements '}'	{}
	| USE NAME					{};

/******************************************************************
*
*   TouchSensor
*
******************************************************************/

TouchSensorElements	
	: TouchSensorElement TouchSensorElements
	|
	;

TouchSensorElement
	: S_ENABLED			SFBool
		{
		}
	;

TouchSensorBegin
	: TOUCH_SENSOR
		{
		}
	;

TouchSensor
	: TouchSensorBegin '{' TouchSensorElements '}'
		{
		}
	;

/******************************************************************
*
*  Transform
*
******************************************************************/

TransformElements	
	: TransformElement TransformElements
	|
	;

TransformElement 
	: children
	| S_CENTER			SFVec3f
		{
		}
	| S_ROTATION		SFRotation
		{
		}
	| S_SCALE			SFVec3f
		{
		}
	| S_SCALEORIENTATION	SFRotation
	    {
		}
	| S_TRANSLATION		SFVec3f
		{
		}
	| bboxCenter
	| bboxSize
	| Transform
	;

TransformDef
	: DEF NAME 	{}
	|		{};

TransformBegin
	: TransformDef TRANSFORM {}; 

Transform
	: TransformBegin '{' TransformElements '}' 	{}
	| USE NAME					{};

/******************************************************************
*
*	Viewpoint
*
******************************************************************/

ViewpointElements		
	: ViewpointElement ViewpointElements
	|
	;

ViewpointElement
	: S_FIELD_OF_VIEW	SFFloat		{}
	| S_JUMP		SFBool		{}
	| S_ORIENTATION		SFRotation	{}
	| S_POSITION		SFVec3f		{}
	| S_DESCRIPTION		SFString	{};

ViewpointDef
	: DEF NAME	{}
	|		{};

ViewpointBegin
	: ViewpointDef VIEWPOINT {};

Viewpoint 	
	: ViewpointBegin '{' ViewpointElements '}'	{}
	| USE NAME					{};

/******************************************************************
*
*	VisibilitySensor
*
******************************************************************/

VisibilitySensors
	: VisibilitySensor VisibilitySensors
	|
	;

VisibilitySensor		
	: S_CENTER				SFVec3f
		{
		}
	| S_ENABLED				SFBool
		{
		}
	| S_SIZE				SFVec3f
		{
		}
	;

VisibilitySensorBegine
	: VISIBILITY_SENSOR
		{
		}
	;

VisibilitySensor	
	: VisibilitySensorBegine '{' VisibilitySensors '}'
		{
		}
	;

/******************************************************************
*
*	WorldInfo
*
******************************************************************/

WorldInfoElements		
	: WorldInfoElement WorldInfoElements
	|
	;

WorldInfoInfo
	: S_INFO
		{
		}
	;

WorldInfoElement		
	: WorldInfoInfo	MFString
		{
		}
	| S_TITLE					SFString
		{
		}
	;

WorldInfoBegin
	: WORLD_INFO 
		{
		}
	;

WorldInfo			
	: WorldInfoBegin '{' WorldInfoElements '}'
		{
		}
	;

%%

#include <iostream>
using namespace std;

extern  char    *Vrmltext;
extern  int      VrmlCurrentLine;

int yyerror(char *s) 
{ 
	cerr << "VRML " << s << " in line " << VrmlCurrentLine << " near " << Vrmltext << endl;
	return 0;
}
