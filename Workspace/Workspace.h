

#pragma once

#include <Model/Node.h>
#include <Geometry/Rect.h>
#include <Workspace/Pad.h>
#include <Workspace/HUD.h>
#include <Workspace/Bounds.h>
#include <Workspace/TestRectangle.h>
#include <Render/Layer.h>





namespace ftr {
    
class Octree;

class Workspace : public Node
{
public:
    Workspace(Layer* layer);
    ~Workspace();
    virtual void Render(Layer& layer);
    
    
    void setOctree(Octree& octree) { mOctree = &octree; };
    
    bool mRenderOctree;
private:
    
    Octree* mOctree;
    Pad* mPad;
    HUD* mHUD;
    Bounds* mBounds;
    TestRectangle* mTestRactangle;
    
    Layer* mHudLayer;
    Layer* mPadLayer;
    Layer* mBoundsLayer;
    Layer* mModelLayer;
    Layer* mTestLayer;
    Layer* mOctreeLayer;
    
    
};

}
