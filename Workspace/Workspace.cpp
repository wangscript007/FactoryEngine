// 
//  Copyright (c) 2012 Dimention. All rights reserved.
//

#include <Workspace/Workspace.h>
#include <Main/Log.h>

namespace ftr {

Workspace::Workspace()
{
    mPad = new Pad();
    mHUD = new HUD();
    
    AddNode(reinterpret_cast<Node*>(mPad));
    AddNode(reinterpret_cast<Node*>(mHUD));
}

Workspace::~Workspace()
{
    FT_DELETE(mPad);
    FT_DELETE(mHUD);
}

void Workspace::setViewportRect(Rect rect)
{
    Log(kLogWorkspace, "");
    glViewport(rect.mOrigin.mX, rect.mOrigin.mY, rect.mSize.mX, rect.mSize.mY);
}

void Workspace::Render(Layer& layer)
{    
    Log(kLogWorkspace, "");
    Node::Render(layer);
    glFinish();
}

}


