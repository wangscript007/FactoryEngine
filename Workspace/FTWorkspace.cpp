// 
//  Copyright (c) 2012 Dimention. All rights reserved.
//

#include <FactoryEngine.h>
#include "octree.h"

FTWorkspace::FTWorkspace()
{
    mpPad = new FTPad();
    mpHUD = new FTHUD();
    
    AddNode(reinterpret_cast<FTNode*>(mpPad));
    AddNode(reinterpret_cast<FTNode*>(mpHUD));
}

FTWorkspace::~FTWorkspace()
{
    delete mpPad;
    delete mpHUD;
}

void FTWorkspace::SetViewportRect(FTRect rect)
{
    FTLog(kFTLogWorkspace, "");
    glViewport(rect.m_vOrigin.m_fX, rect.m_vOrigin.m_fY, rect.m_vSize.m_fX, rect.m_vSize.m_fY);
}

void FTWorkspace::Render()
{    
    FTLog(kFTLogWorkspace, "");
    FTNode::Render();
    glFinish();
}



