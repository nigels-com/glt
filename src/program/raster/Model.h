#ifndef MODEL_H
#define MODEL_H

// Model.h
// James Ward 02/10/01 (espresso@crema.co.uk)
//
// Simple class for loading and drawing 3D models in ASE format (very basic)

#include <string>
#include <vector>

#include <math/vector3.h>
#include <node/dlist.h>

class Model
{
public:
    Model();
    virtual ~Model();

    void Draw() const;
    void DrawWire() const;
    bool Load(const std::string &file);
    void Reset();

protected:
    bool LoadASE(const std::string &file);

private:
    std::vector<Vector> _vert;
    std::vector<Vector> _norm;
    std::vector<int>    _face;

    mutable GltDisplayList _list[2];
};

#endif
