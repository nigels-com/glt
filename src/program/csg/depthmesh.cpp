// DepthMesh utility

#include <iostream>
#include <string>
#include <vector>

#include <mesh/mesh.h>
#include <mesh/triangle.h>

#include <misc/string.h>
#include <misc/image.h>

using namespace std;

const double e = 0.005;

int main(int argc,char *argv[])
{
    //
    // Read the image into a memory buffer
    //

    string input;
    readStream(cin,input);

    //
    // Decode the PPM, BMP or TGA image
    //

    string type;
    uint32 width,height;
    string image;

    if (decodePPM(type,width,height,image,input))
    {
    }
    else
        if (decodeBMP(width,height,image,input))
        {
        }
        else
            if (decodeTGA(width,height,image,input))
            {
            }
            else
            {
                cerr << "Image not recognised." << endl;
                return EXIT_FAILURE;
            }

    if (image.size()!=width*height)
    {
        cerr << "Image must be greyscale." << endl;
        return EXIT_FAILURE;
    }

    //
    // Create vertex array
    //

    vector<Vector> vertex;
    vertex.resize(image.size());

    {
        int k=0;
        for (uint32 i=0; i<height; i++)
            for (uint32 j=0; j<width; j++)
                vertex[k++] = Vector(double(j)/width*2.0-1.0,double(i)/height*2.0-1.0,byte(image[k])/255.0*2.0-1.0);
    }

#if 0
    //
    // Write boxes
    //

    const Vector delta(2.0/width,2.0/height,2.0/255.0);

    cout << "union { " << endl;
    for (int i=0; i<vertex.size(); i++)
    {
/*
        cout << "box { ";
        (vertex[i]-delta).writePov(cout);
        (vertex[i]+delta).writePov(cout);
        cout << "}" << endl;
*/

        cout << "sphere { ";
        vertex[i].writePov(cout);
        cout << " " << 1.0/255.0 << " } " << endl;
    }

#else
    //
    // Create normals
    //

    vector<Vector> normal;
    normal.resize(image.size());

    {
        int k=0;
        for (uint32 i=0; i<height; i++)
            for (uint32 j=0; j<width; j++,k++)
            {
                normal[k] = VectorZ;

                if (i>0 && j>0 && byte(image[k])!=255)
                {
                    normal[k] = xProduct(vertex[k-1]-vertex[k],vertex[k-width]-vertex[k]);
                    normal[k].normalize();
                }
            }
    }

    //
    // Filter normals
    //

    {
        int k=0;
        for (uint32 i=0; i<height; i++)
            for (uint32 j=0; j<width; j++,k++)
                if (i>0 && j>0 && i<height-1 && j<width-1)
                {
                    Vector n;

                    n += normal[k-1];
                    n += normal[k]*3.0;
                    n += normal[k+1];
                    n += normal[k-width];
                    n += normal[k+width];

                    n.normalize();

                    if (n*normal[k]>0.95)
                        normal[k] = n;
                }
    }

    //
    // Output triangles

    cout << "mesh { " << endl;

    {
        uint32 k=0;
        for (uint32 i=0; i<height-1; i++)
        {
            for (uint32 j=0; j<width-1; j++,k++)
            {
                bool ok = false;

                if
                (
                    (vertex[k]-vertex[k+1]    ).norm()<=e &&
                    (vertex[k]-vertex[k+width]).norm()<=e
                )
                {
                    cout << "smooth_triangle { ";
                    vertex[k      ].writePov(cout);
                    normal[k      ].writePov(cout);
                    vertex[k+1    ].writePov(cout);
                    normal[k+1    ].writePov(cout);
                    vertex[k+width].writePov(cout);
                    normal[k+width].writePov(cout);
                    cout << " } " << endl;

                    ok = true;
                }

                if
                (
                    (vertex[k+1+width]-vertex[k+1]   ).norm()<=e &&
                    (vertex[k+1+width]-vertex[k+width]).norm()<=e
                )
                {
                    cout << "smooth_triangle { ";
                    vertex[k+1      ].writePov(cout);
                    normal[k+1      ].writePov(cout);
                    vertex[k+1+width].writePov(cout);
                    normal[k+1+width].writePov(cout);
                    vertex[k+width  ].writePov(cout);
                    normal[k+width  ].writePov(cout);
                    cout << " } " << endl;

                    ok = true;
                }

                if (ok)
                    continue;

            }

            k++;
        }
    }


/*
    const double dy = 2.0/(height-1);
    const double dx = 2.0/(width-1);

    double y = -1.0;
    int    k = 0;
    for (int i=0; i<height-1; i++)
    {
        double x = -1.0;

        for (int j=0; j<width-1; j++)
        {
            if
            (
                abs(byte(image[k+1    ])-byte(image[k]))<=e &&
                abs(byte(image[k+width])-byte(image[k]))<=e
            )
            {
                cout << "triangle { ";
                Vector(x   ,y   ,byte(image[k      ])/255.0).writePov(cout);
                Vector(x+dx,y   ,byte(image[k+1    ])/255.0).writePov(cout);
                Vector(x   ,y+dy,byte(image[k+width])/255.0).writePov(cout);
                cout << "}" << endl;
            }

            if
            (
                abs(uint32(image[k+1    ])-uint32(image[k+width+1]))<=e &&
                abs(uint32(image[k+width])-uint32(image[k+width+1]))<=e
            )
            {
                cout << "triangle { ";
                Vector(x+dx,y   ,byte(image[k+1      ])/255.0).writePov(cout);
                Vector(x+dx,y+dy,byte(image[k+width+1])/255.0).writePov(cout);
                Vector(x   ,y+dy,byte(image[k+width  ])/255.0).writePov(cout);
                cout << "}" << endl;
            }

            k++;
            x += dx;
        }

        k++;
        y += dy;
    }

*/
#endif

    cout << "pigment { White } " << endl;
    cout << "}" << endl;

    return EXIT_SUCCESS;
}

