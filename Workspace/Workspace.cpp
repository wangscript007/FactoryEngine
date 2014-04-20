

#include <Workspace/Workspace.h>
#include <Main/GLError.h>
#include <Processing/Octree.h>
#include <Processing/ModelTree.h>

namespace ftr {

Workspace::Workspace(Layer* layer)
    :mModelTree(NULL)
{
    mRenderOctree = false;
    
    //glEnable(GL_NORMALIZE);
    GetError();
    mPad = new Pad();
    mHUD = new HUD();
    mBounds = new Bounds();
    mTestRactangle = new TestRectangle();
    
    mHudLayer = new Layer();
    mPadLayer = new Layer();
    mBoundsLayer = new Layer();
    mModelLayer = new Layer();
    mTestLayer = new Layer();
    mOctreeLayer = new Layer();
    
    mPadLayer->setDepth(1);
    mBoundsLayer->setDepth(2);
    mHudLayer->setDepth(3);
    mModelLayer->setDepth(4);
    mTestLayer->setDepth(5);
    mOctreeLayer->setDepth(6);
    
    layer->AddSublayer(mHudLayer);
    layer->AddSublayer(mBoundsLayer);
    layer->AddSublayer(mPadLayer);
    layer->AddSublayer(mModelLayer);
    layer->AddSublayer(mTestLayer);
    layer->AddSublayer(mOctreeLayer);
    layer->AddSublayer(mModelLayer);
}

Workspace::~Workspace()
{
    FT_DELETE(mPad);
    FT_DELETE(mHUD);
    FT_DELETE(mBounds);
    FT_DELETE(mHudLayer);
    FT_DELETE(mPadLayer);
    FT_DELETE(mModelLayer);
    FT_DELETE(mBoundsLayer);
    FT_DELETE(mTestRactangle);
    FT_DELETE(mTestLayer);
    FT_DELETE(mOctreeLayer);
    FT_DELETE(mModelLayer);
}

void Workspace::Render(Layer& layer)
{
    //mTestRactangle->Render(*mTestLayer);
    mPad->Render(*mPadLayer);
    //mHUD->Render(*mHudLayer);
    if (mRenderOctree) {
        mOctree->Render(*mOctreeLayer);
    }
    if (mModelTree) {
        mModelTree->Render(*mModelLayer);
    }
    Node::Render(*mModelLayer);
}

}


