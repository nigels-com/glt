#include "read3dsb.h"

/*! \file
    \ingroup Mesh

    \todo Migrate to 3ds.cpp/.h
    \todo Smooth lighting support
    \todo Texture support

    Sample 3DS files:
    - http://www.3dcafe.com/asp/aircraft.asp

    Other 3DS loaders and information:
    - http://www.levp.de/3d/3ds.html
    - http://www.the-labs.com/Blender/3DS-details.html

    $Id: read3dsb.cpp,v 2.1 2004/02/16 14:22:01 nigels Exp $

    $Log: read3dsb.cpp,v $
    Revision 2.1  2004/02/16 14:22:01  nigels
    Added debug diagnostics

    Revision 1.17  2003/12/11 23:52:07  nigels
    Added debug diagnostics

    Revision 1.16  2003/11/12 06:46:12  nigels
    Expand

    Revision 1.15  2003/10/08 05:22:31  nigels
    *** empty log message ***

    Revision 1.13  2003/08/21 04:29:06  nigels
    *** empty log message ***

    Revision 1.12  2003/06/02 03:15:56  nigels
    MD3 Tweaks

    Revision 1.11  2003/05/31 13:27:58  nigels
    *** empty log message ***

    Revision 1.10  2003/05/31 13:14:44  nigels
    Tested with several 3DS files from the net

    Revision 1.9  2003/05/31 12:53:41  nigels
    Cleanup of Binary 3DS Reader

    Revision 1.8  2003/05/31 11:38:02  nigels
    Some changes to 3DS support

    Revision 1.6  2003/03/06 12:31:14  nigels
    *** empty log message ***

*/

#ifdef MSCVER
#pragma warning(disable : 4786)     // Lengthy STL symbols
#endif

#ifndef NDEBUG
#include <iostream>
#include <iomanip>
#endif

#include <map>
using namespace std;

#include <mesh/mesh.h>

#include <glt/material.h>

/////////////////////////////////////////////////////////////////////////////////////

typedef uint16 chunkID;
typedef uint32 chunkSize;

typedef std::map<std::string,GltMaterial> Materials;

/////////////////////////////////////////////////////////////////////////////////////

bool readPrimary (const byte *i, const byte *end, GltShapes &shapes);
bool readEditor  (const byte *i, const byte *end, GltShapes &shapes);
bool readObject       (const byte *i, const byte *end, const Materials &mat, GltShapes &shapes);
bool readMesh         (const byte *i, const byte *end, const Materials &mat, Mesh &mesh);
bool readMaterial     (const byte *i, const byte *end, string &name, GltMaterial &material);
bool readMaterialGroup(const byte *i, const byte *end, string &name);
bool readColor        (const byte *i, const byte *end, GltColor &color);
bool readPercentage   (const byte *i, const byte *end, real &percent);

bool readChunk (const byte **i, const byte *end, chunkID &id, chunkSize &size);
bool readString(const byte **i, const byte *end, string &string);

//////////////////////////////////////////////////////////////////////////////////////

bool
readChunk(const byte **i, const byte *end, chunkID &id, chunkSize &size)
{
    if (end-(*i)<6)
        return false;

    id   = * reinterpret_cast<const chunkID *>(*i);
    size = * reinterpret_cast<const chunkSize *>(*i+2);

    #ifndef NDEBUG
    cout << "Chunk 0x" << hex << id << " (" << dec << size << " bytes.)" << endl;
    #endif

    *i   += 6;
    size -= 6;

    if (*i+size>end)
    {
        #ifndef NDEBUG
        cout << "Trouble with chunk size." << endl;
        #endif

        return false;
    }

    return true;
}

bool
readString(const byte **i, const byte *end, string &str)
{
    str = string();

    while (*i<end && **i!='\0')
    {
        str += **i;
        (*i)++;
    }

    if (*i<end)
        (*i)++;

    return true;
}

bool
readColor(const byte *i, const byte *end, GltColor &color)
{
    chunkID   id   = 0;
    chunkSize size = 0;

    color = GltColor();

    if (i<end && readChunk(&i,end,id,size))
    {
        switch (id)
        {
            case 0x0010:
            case 0x0013:
                if (size==sizeof(float)*3)
                {
                    const float *rgb = reinterpret_cast<const float *>(i);
                    color.red()   = rgb[0];
                    color.green() = rgb[1];
                    color.blue()  = rgb[2];
                    return true;
                }
                return false;

            case 0x0011:
            case 0x0012:
                if (size==sizeof(byte)*3)
                {
                    const byte *rgb = reinterpret_cast<const byte *>(i);
                    color.red()   = rgb[0]/255.0;
                    color.green() = rgb[1]/255.0;
                    color.blue()  = rgb[2]/255.0;
                    return true;
                }
                return false;
        }
    }

    return false;
}

bool readPercentage(const byte *i, const byte *end, real &percent)
{
    chunkID   id   = 0;
    chunkSize size = 0;

    percent = 0.0;

    if (i<end && readChunk(&i,end,id,size))
    {
        switch (id)
        {
            case 0x0030:
                if (size==sizeof(uint16))
                {
                    percent = (* reinterpret_cast<const uint16 *>(i))*0.01;
                    return true;
                }
                return false;

            case 0x0031:
                if (size==sizeof(float))
                {
                    percent = * reinterpret_cast<const float *>(i);
                    return true;
                }
                return false;
        }
    }

    return false;
}

bool
readMaterialGroup(const byte *i, const byte *end, string &name)
{
    if (!readString(&i,end,name))
        return false;

    if (i+2>end)
        return false;

    const uint16 &n = * reinterpret_cast<const uint16 *>(i);
    i += 2;

    #ifndef NDEBUG
    cout << "MaterialGroup " << name << ", " << n << " faces." << endl;
    #endif

    if (i+2*n>end)
    {
        #ifndef NDEBUG
        cout << "Problem with MaterialGroup faces." << endl;
        #endif

        return false;
    }

    const uint16 *faces = reinterpret_cast<const uint16 *>(i);
    i += 2*n;

    return true;
}

bool
readMaterial(const byte *i, const byte *end, string &name, GltMaterial &material)
{
    chunkID   id   = 0;
    chunkSize size = 0;

    while (i<end && readChunk(&i,end,id,size))
    {
        switch (id)
        {
            case 0xA000:
                readString(&i,end,name);
                break;

            case 0xA010: readColor(i,end,material.ambient());  i+= size; break;
            case 0xA020: readColor(i,end,material.diffuse());  i+= size; break;
            case 0xA030: readColor(i,end,material.specular()); i+= size; break;

            case 0xA050:
                readPercentage(i,end,material.diffuse().alpha());
                material.diffuse().alpha() = 1.0 - material.diffuse().alpha();
                i+= size;
                break;

            case 0xA040:        // Shininess
            case 0xA041:        // Shininess2
            case 0xA042:        // Shininess3
                i+= size;
                break;

            default:
            {
                #ifndef NDEBUG
                cout << "Unrecognised chunk in readMaterial: 0x" << hex << id << " (" << dec << size << " bytes)" << endl;
                #endif
                i += size;
                break;
            }
        }

    }

    return true;
}

bool
readMesh(const byte *i, const byte *end, const Materials &mat, Mesh &mesh)
{
    chunkID   id   = 0;
    chunkSize size = 0;

    #ifndef NDEBUG
    cout << "readMesh {" << endl;
    #endif

    while (i<end && readChunk(&i,end,id,size))
    {
        switch (id)
        {
            case 0x4110:            // Vertex List
                {
                    const uint16 &n = * reinterpret_cast<const uint16 *>(i);
                    i += 2;

                    #ifndef NDEBUG
                    cout << "vertex list: " << n << " points." << endl;
                    #endif

                    mesh.point().resize(n);

                    for (uint16 j=0; j<n && i<end; j++, i+=12)
                        mesh.point()[j] =
                            Point
                            (
                                Vector
                                (
                                    * reinterpret_cast<const float *>(i),
                                    * reinterpret_cast<const float *>(i+4),
                                    * reinterpret_cast<const float *>(i+8)
                                ),
                                Vector0
                            );

                    break;
                }

            case 0x4120:            // Faces
                {
                    const uint16 &n = * reinterpret_cast<const uint16 *>(i);
                    i += 2;

                    #ifndef NDEBUG
                    cout << "face list: " << n << " faces." << endl;
                    #endif

                    mesh.triangle().resize(n);

                    const uint16 maxIndex = mesh.point().size();

                    for (uint16 j=0; j<n && i<end; j++, i+=8)
                    {
                        const uint16 &a = * reinterpret_cast<const uint16 *>(i);
                        const uint16 &b = * reinterpret_cast<const uint16 *>(i+2);
                        const uint16 &c = * reinterpret_cast<const uint16 *>(i+4);

                        if (a<maxIndex && b<maxIndex && c<maxIndex)
                            mesh.triangle()[j] =
                                Triangle
                                (
                                    &mesh.point()[a],
                                    &mesh.point()[b],
                                    &mesh.point()[c]
                                );
                    }

                    break;
                }

            case 0x4130:        // Material group
                {
                    string name;
                    if (readMaterialGroup(i,end,name))
                    {
                        Materials::const_iterator i = mat.find(name);
                        if (i!=mat.end())
                            mesh.color() = i->second.diffuse();
                    }
                break;
                }

            case 0x4140:        // Texture co-ordinates
                {
                    const uint16 &n = * reinterpret_cast<const uint16 *>(i);
                    i += 2;

                    #ifndef NDEBUG
                    cout << "Texture co-ordinates: " << n << endl;
                    #endif

                    // In pairs of x,y

                    i += n*2*4;
                    break;
                }

            case 0x4111:        // Point flag array, TODO
            case 0x4160:        // Translation Matrix, TODO
                i += size;
                break;

            default:
                {
                    #ifndef NDEBUG
                    cout << "Unrecognised chunk: 0x" << hex << id << " (" << dec << size << " bytes)" << endl;
                    #endif
                    i += size;
                    break;
                }
        }
    }

    #ifndef NDEBUG
    cout << "}" << endl;
    #endif

    return true;
}

bool
readObject(const byte *i, const byte *end, const Materials &mat, GltShapes &shapes)
{
    chunkID   id   = 0;
    chunkSize size = 0;

    string name;
    if (!readString(&i,end,name))
        return false;

    #ifndef NDEBUG
    cout << "Object: " << name << endl;
    #endif

    while (i<end && readChunk(&i,end,id,size))
    {
        switch (id)
        {
            case 0x4100:        // Triangular Polygon Object
                {
                    Mesh *mesh = new Mesh();
//                    mesh->inheritColor() = true;
                    if (readMesh(i,end,mat,*mesh))
                        shapes.push_back(mesh);
                    break;
                }

            case 0x4600:            // Direct light data, not yet implemented
            case 0x4700:            // Camera data, not yet implemented
                break;

            default:
                {
                    #ifndef NDEBUG
                    cout << "Unrecognised chunk in readObject: 0x" << hex << id << " (" << dec << size << " bytes)" << endl;
                    #endif
                    break;
                }
        }

        i += size;
    }

    return true;
}

bool
readEditor(const byte *i, const byte *end, GltShapes &shapes)
{
    chunkID   id   = 0;
    chunkSize size = 0;

    Materials mat;

    while (i<end && readChunk(&i,end,id,size))
    {
        switch (id)
        {
            case 0x4000:
                readObject(i,i+size,mat,shapes);
                break;

            case 0xafff:
                {
                    string      name;
                    GltMaterial m;

                    readMaterial(i,i+size,name,m);

                    mat[name] = m;

                    #ifndef NDEBUG
                    cout << "Material " << name << '\t' << m.diffuse() << endl;
                    #endif

                    break;
                }

            case 0x0100:            // Master scale, not yet implemented
            case 0x3d3e:            // Mesh Version, not yet implemented
            case 0x4700:            // Camera data, not yet implemented
                break;

            default:
                {
                    #ifndef NDEBUG
                     cout << "Unrecognised chunk in readEditor: 0x" << hex << id << " (" << dec << size << " bytes)" << endl;
                    #endif
                    break;
                }
        }

        i += size;
    }

    return true;
}

bool
readPrimary(const byte *i, const byte *end, GltShapes &shapes)
{
    chunkID   id   = 0;
    chunkSize size = 0;

    while (i<end && readChunk(&i,end,id,size))
    {
        switch (id)
        {
            case 0x3d3d:
                readEditor(i,i+size,shapes);
                break;

            case 0x0002:            // 3D Mesh version, not yet implemented
            case 0xb000:            // Keyframe data, not yet implemented
                break;

            default:
                {
                    #ifndef NDEBUG
                    cout << "Unrecognised chunk in readPrimary: 0x" << hex << id << " (" << dec << size << " bytes)" << endl;
                    #endif
                    break;
                }
        }

        i += size;
    }

    return true;
}

GltShapes
read3DS(const byte *buffer,const uint32 bufferSize)
{
    const byte *i   = buffer;
    const byte *end = i+bufferSize;

    GltShapes shapes;
    shapes.inheritColor() = true;

    chunkID   id   = 0;
    chunkSize size = 0;

    while (readChunk(&i,end,id,size))
    {
        // Process Primary 3DS chunk

        switch (id)
        {
            case 0x4d4d:
            case 0xc23d:
                readPrimary(i,i+size,shapes);
                break;

            default:
                {
                    #ifndef NDEBUG
                    cout << "Unrecognised chunk in read3DS: 0x" << hex << id << " (" << dec << size << " bytes)" << endl;
                    #endif
                    break;
                }
        }

        i += size;
    }

    return shapes;
}
