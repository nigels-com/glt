#include "sierpink.h"

#include <glt/color.h>

#include <node/shapes.h>
#include <glutm/shape.h>

void
sierpinskiSponge
(
    GltShapes &shapes,
    const int n,
    const Vector3 &min,
    const Vector3 &max,
    const GltColor &color
)
{
    if (n<1)
        return;

    const Vector3 delta = (max - min)*(1.0/3.0);

    // Subdivide into 3x3x3 sub-cubes

    Vector3 minT(min);
    Vector3 maxT(min+delta);

    for (int i=0; i<3; i++)
    {
        minT[1] = min[1];
        maxT[1] = min[1] + delta[1];

        for (int j=0; j<3; j++)
        {
            minT[2] = min[2];
            maxT[2] = min[2] + delta[2];

            for (int k=0; k<3; k++)
            {
                const bool internal = i==1 && j==1 || i==1 && k==1 || j==1 && k==1;

                if (!internal)
                {
                    if (n==1)
                    {
                        GlutCube *box = new GlutCube();
                        box->position(minT,maxT);
                        box->color() = color;
                        shapes.push_back(box);
                    }
                    else
                        sierpinskiSponge(shapes,n-1,minT,maxT,color);
                }

                minT[2] += delta[2];
                maxT[2] += delta[2];
            }

            minT[1] += delta[1];
            maxT[1] += delta[1];
        }

        minT[0] += delta[0];
        maxT[0] += delta[0];
    }
}

void
sierpinskiCross
(
    GltShapes &shapes,
    const int n,
    const Vector3 &min,
    const Vector3 &max,
    const GltColor &color
)
{
    if (n<1)
        return;

    const Vector3 delta = (max - min)*(1.0/3.0);

    // Subdivide into 3x3x3 sub-cubes

    Vector3 minT(min);
    Vector3 maxT(min+delta);

    for (int i=0; i<3; i++)
    {
        minT[1] = min[1];
        maxT[1] = min[1] + delta[1];

        for (int j=0; j<3; j++)
        {
            minT[2] = min[2];
            maxT[2] = min[2] + delta[2];

            for (int k=0; k<3; k++)
            {
                const bool internal = i==1 && j==1 || i==1 && k==1 || j==1 && k==1;

                if (internal)
                {
                    GlutCube *box = new GlutCube();
                    box->position(minT,maxT);
                    box->color() = color;
                    shapes.push_back(box);
                }
                else
                    if (n>1)
                        sierpinskiCross(shapes,n-1,minT,maxT,color);

                minT[2] += delta[2];
                maxT[2] += delta[2];
            }

            minT[1] += delta[1];
            maxT[1] += delta[1];
        }

        minT[0] += delta[0];
        maxT[0] += delta[0];
    }
}

void
sierpinskiFlake
(
    GltShapes &shapes,
    const int n,
    const Vector3 &min,
    const Vector3 &max,
    const GltColor &color
)
{
    if (n<1)
        return;

    const Vector3 delta = (max - min)*(1.0/3.0);

    // Subdivide into 3x3x3 sub-cubes

    Vector3 minT(min);
    Vector3 maxT(min+delta);

    for (int i=0; i<3; i++)
    {
        minT[1] = min[1];
        maxT[1] = min[1] + delta[1];

        for (int j=0; j<3; j++)
        {
            minT[2] = min[2];
            maxT[2] = min[2] + delta[2];

            for (int k=0; k<3; k++)
            {
                const bool internal = i==1 && j==1 || i==1 && k==1 || j==1 && k==1;

                if (internal)
                {
                    if (n==1)
                    {
                        GlutCube *box = new GlutCube();
                        box->position(minT,maxT);
                        box->color() = color;
                        shapes.push_back(box);
                    }
                    else
                        sierpinskiFlake(shapes,n-1,minT,maxT,color);
                }

                minT[2] += delta[2];
                maxT[2] += delta[2];
            }

            minT[1] += delta[1];
            maxT[1] += delta[1];
        }

        minT[0] += delta[0];
        maxT[0] += delta[0];
    }
}
