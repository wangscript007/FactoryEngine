

#pragma once

#include <Graph/Node.h>
#include <Geometry/Rect.h>
#include <Workspace/Pad.h>
#include <Render/Layer.h>





namespace ftr {
    
class Octree;
class ModelTree;

class Workspace : public Node
{
public:
    Workspace(Layer* layer);
    ~Workspace();
    virtual void Render(Layer& layer);
    
    
    void setOctree(Octree& octree) { mOctree = &octree; };
    void setModelTree(ModelTree* modelTree) { mModelTree = modelTree; }
    
    
    bool mRenderOctree;
private:
    
    Octree* mOctree;
    ModelTree* mModelTree;
    Pad* mPad;

    
    Layer* mHudLayer;
    Layer* mPadLayer;
    Layer* mBoundsLayer;
    Layer* mModelLayer;
    Layer* mTestLayer;
    Layer* mOctreeLayer;
    
    
};

}
