

#pragma once

#include <Model/Node.h>
#include <Math/Geometry.h>
#include <Math/Polygon.h>

namespace ftr {

class  ModelEditor;

class RectangleInteraction : public Node
{
public:   
    RectangleInteraction(ModelEditor& ModelEditor);
    virtual ~RectangleInteraction() {}
    
    void Render();
    void Begin();
    void End();
    void setOrigin(const Vec3& origin);
    void setCurrent(const Vec3& current);
    
private:
    Polygon mPolygon;
    Rectangle3 mRect3;
    ModelEditor& mModelEditor;
    bool mActive;
};
    
}

