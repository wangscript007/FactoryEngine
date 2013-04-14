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
    glViewport(rect.m_vOrigin.m_fX, rect.m_vOrigin.m_fY, rect.m_vSize.m_fX, rect.m_vSize.m_fY);
}

void Workspace::Render()
{    
    Log(kLogWorkspace, "");
    Node::Render();
    glFinish();
}

}


