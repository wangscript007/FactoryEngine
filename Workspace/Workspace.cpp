// 
//  Copyright (c) 2012 Dimention. All rights reserved.
//

#include <Workspace/Workspace.h>
#include <Main/Log.h>

namespace ftr {

Workspace::Workspace()
{
    mpPad = new Pad();
    mpHUD = new HUD();
    
    AddNode(reinterpret_cast<Node*>(mpPad));
    AddNode(reinterpret_cast<Node*>(mpHUD));
}

Workspace::~Workspace()
{
    delete mpPad;
    delete mpHUD;
}

void Workspace::setViewportRect(Rect rect)
{
    Log(kLogWorkspace, "");
    glViewport(rect.mOrigin.mX, rect.mOrigin.mY, rect.mSize.mX, rect.mSize.mY);
}

void Workspace::Render()
{    
    Log(kLogWorkspace, "");
    Node::Render();
    glFinish();
}

}


