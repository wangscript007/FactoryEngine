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
    
    mHudLayer = new Layer();
    mPadLayer = new Layer();
    mModelLayer = new Layer();
    
    mPadLayer->setDepth(1);
    mHudLayer->setDepth(2);
    mModelLayer->setDepth(3);
    
    layer->AddSublayer(mHudLayer);
    layer->AddSublayer(mPadLayer);
    layer->AddSublayer(mModelLayer);
}

Workspace::~Workspace()
{
    FT_DELETE(mPad);
    FT_DELETE(mHUD);
    FT_DELETE(mHudLayer);
    FT_DELETE(mPadLayer);
    FT_DELETE(mModelLayer);
}

void Workspace::setViewportRect(Rect rect)
{
    glViewport(rect.mOrigin.mX, rect.mOrigin.mY, rect.mSize.mX, rect.mSize.mY);
}

void Workspace::Render(Layer& layer)
{
    Node::Render(*mModelLayer);
    mPad->Render(*mPadLayer);
    mHUD->Render(*mHudLayer);
    glFinish();
}

}


