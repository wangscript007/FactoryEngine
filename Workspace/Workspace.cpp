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

void Workspace::SetViewportRect(Rect rect)
{
    Log(kLogWorkspace, "");
    glViewport(rect.m_vOrigin.mX, rect.m_vOrigin.mY, rect.m_vSize.mX, rect.m_vSize.mY);
}

void Workspace::Render()
{    
    Log(kLogWorkspace, "");
    Node::Render();
    glFinish();
}

}


