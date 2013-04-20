

#pragma once

#include <Model/Node.h>
#include <Math/Geometry.h>
#include <Math/Polygon.h>

namespace ftr {

class  ModelManager;

class RectangleInteraction : public Node
{
public:
    
    
    RectangleInteraction(ModelManager& modelManager);
    virtual ~RectangleInteraction() {}
    
    void Render();
    void Begin();
    void End();
    void setOrigin(const Vec3& origin);
    void setCurrent(const Vec3& current);
    
    
private:
    Polygon mPolygon;
    Rectangle3 mRect3;
    ModelManager& mModelManager;
    bool mActive;
};
    
}

