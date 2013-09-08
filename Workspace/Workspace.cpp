// 
//  Copyright (c) 2012 Dimention. All rights reserved.
//

#include <Workspace/Workspace.h>
#include <Main/GLError.h>

namespace ftr {

Workspace::Workspace(Layer* layer)
{
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
    
    mPadLayer->setDepth(1);
    mBoundsLayer->setDepth(2);
    mHudLayer->setDepth(3);
    //mModelLayer->setDepth(4);
    mTestLayer->setDepth(5);
    
    layer->AddSublayer(mHudLayer);
    layer->AddSublayer(mBoundsLayer);
    layer->AddSublayer(mPadLayer);
    layer->AddSublayer(mModelLayer);
    layer->AddSublayer(mTestLayer);
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
}

void Workspace::Render(Layer& layer)
{
//    mTestRactangle->Render(*mTestLayer);
    mPad->Render(*mPadLayer);
    mHUD->Render(*mHudLayer);
    mBounds->Render(*mBoundsLayer);
//    Node::Render(*mModelLayer);
}

}


