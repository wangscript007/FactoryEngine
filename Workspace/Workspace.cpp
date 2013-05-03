// 
//  Copyright (c) 2012 Dimention. All rights reserved.
//

#include <Workspace/Workspace.h>
#include <Main/Log.h>

namespace ftr {

Workspace::Workspace(Layer* layer)
{
    glEnable(GL_NORMALIZE);
    
    mPad = new Pad();
    mHUD = new HUD();
    mBounds = new Bounds();
    
    mHudLayer = new Layer();
    mPadLayer = new Layer();
    mBoundsLayer = new Layer();
    mModelLayer = new Layer();
    
    mPadLayer->setDepth(1);
    mBoundsLayer->setDepth(2);
    mHudLayer->setDepth(3);
    mModelLayer->setDepth(4);
    
    layer->AddSublayer(mHudLayer);
    layer->AddSublayer(mBoundsLayer);
    layer->AddSublayer(mPadLayer);
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
}

void Workspace::setViewportRect(Rect rect)
{
    glViewport(rect.mOrigin.mX, rect.mOrigin.mY, rect.mSize.mX, rect.mSize.mY);
}

void Workspace::Render(Layer& layer)
{
    
    mPad->Render(*mPadLayer);
    mHUD->Render(*mHudLayer);
    mBounds->Render(*mBoundsLayer);
    Node::Render(*mModelLayer);
    glFinish();
}

}


