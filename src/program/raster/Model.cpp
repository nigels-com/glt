#include "Model.h"

#include <glt/gl.h>
#include <misc/string.h>

#include <cstdio>
#include <string>
using namespace std;

//-----------------------------------------------------------------------------

// edge flags
#define EDGE_MASK   0x00E0
#define EDGE_AB     0x0020
#define EDGE_BC     0x0040
#define EDGE_CA     0x0080

//-----------------------------------------------------------------------------

Model::Model()
{
    Reset();
}

Model::~Model()
{
    Reset();
}

void Model::Draw() const
{
    if (_list[0].defined())
    {
        // draw from display list if available
        _list[0].draw();
    }
    else
        if (_face.size())
        {
            // first time, we build display list
            _list[0].newList(GL_COMPILE_AND_EXECUTE);
                glBegin(GL_TRIANGLES);
                for (uint32 n=0; n<_norm.size(); n++)
                {
                    const int *f=&_face[n<<2];
                    _norm[n].glNormal();
                    _vert[f[0]].glVertex();
                    _vert[f[1]].glVertex();
                    _vert[f[2]].glVertex();
                }
                glEnd();
            _list[0].endList();
        }
}

void Model::DrawWire() const
{
    if (_face.size()==0)
        return;

    if (_list[1].defined())
    {
        // draw from display list if available
        _list[1].draw();
    }
    else
        if (_face.size())
        {
            // first time, we build display list
            _list[1].newList(GL_COMPILE_AND_EXECUTE);
                glBegin(GL_LINES);
                    for (uint32 n=0; n<_face.size(); n+=4)
                    {
                        const int *f=&_face[n];

                        const Vector &a = _vert[f[0]];
                        const Vector &b = _vert[f[1]];
                        const Vector &c = _vert[f[2]];
                        const int flags = f[3];

                        if (flags & EDGE_AB)
                        {
                            a.glVertex();
                            b.glVertex();
                        }
                        if (flags & EDGE_BC)
                        {
                            b.glVertex();
                            c.glVertex();
                        }
                        if (flags & EDGE_CA)
                        {
                            c.glVertex();
                            a.glVertex();
                        }
                    }
                glEnd();
            _list[1].endList();
        }
}

bool Model::Load(const string &file)
{
    // supports only ASE format so far
    return LoadASE(file);
}

void Model::Reset()
{
    _vert.clear();
    _norm.clear();
    _face.clear();
    _list[0].reset();
    _list[1].reset();
}

bool Model::LoadASE(const string &file)
{
    Reset();

    int
        nVertex=0,
        nFaces =0;

    int   a,b,c, idx;
    float x,y,z;

    vector<string> lines;
    stringSplit(lines,file,"\n");

    for (uint32 i=0; i<lines.size(); i++)
    {
        char token[1024];
        sscanf(lines[i].c_str(),"%s",token);

        if (i>=lines.size())
            break;

        if (!strcmp(token,"*MESH_NUMVERTEX"))
        {
            //-- read no.of vertices
            if (sscanf(lines[i].c_str(),"%*s %d",&nVertex)==1)
                _vert.resize(nVertex);
        }
        else
        if (!strcmp(token,"*MESH_NUMFACES"))
        {
            //-- read no.of faces
            if (sscanf(lines[i].c_str(),"%*s %d",&nFaces)==1)
            {
                _face.resize(nFaces*4);
                _norm.resize(nFaces);
            }
        }
        else
        if (!strcmp(token,"*MESH_VERTEX"))
        {
            //-- read mesh vertex
            if
            (
                (sscanf(lines[i].c_str(), "%*s %d %f %f %f", &idx, &x,&y,&z) == 4) &&
                (idx >= 0) && (idx < nVertex)
            )
            {
                Vector &v = _vert[idx];
                v.x() = x;
                v.y() = y;
                v.z() = z;
            }
        }
        else
        if (!strcmp(token,"*MESH_FACENORMAL"))
        {
            //-- read face normal
            if
            (
                (sscanf(lines[i].c_str(), "%*s %d %f %f %f", &idx, &x,&y,&z) == 4) &&
                (idx >= 0) && (idx < nFaces)
            )
            {
                Vector &n = _norm[idx];
                n.x() = x;
                n.y() = y;
                n.z() = z;
            }
        }
        else
        if (!strcmp(token,"*MESH_FACE"))
        {
           //-- read mesh face
            if
            (
                (sscanf(lines[i].c_str(),"%*s %d: A: %d B: %d C: %d", &idx, &a,&b,&c) == 4) &&
                (idx >= 0) && (idx < nFaces)
            )
            {
                // store the face (3 vertex indices)
                int *f = &_face[idx*4];
                f[0]=a; f[1]=b; f[2]=c;

                // check visible edges
                int ab,bc,ca;
                if (sscanf(strstr(lines[i].c_str(),"AB:"), "%*s %d %*s %d %*s %d", &ab,&bc,&ca)==3) {
                    // ignored: smoothing group ID
                    // ignored: mesh mtlid
                    // store edge flags
                    f[3]= (ab?EDGE_AB:0) | (bc?EDGE_BC:0) | (ca?EDGE_CA:0);
                } else
                    f[3]=0;
            }
        }
        else
        {
            // unknown / unhandled token type - ignore
        }
    }

    return _vert.size()>0;
}
