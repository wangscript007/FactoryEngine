// 
//  Copyright (c) 2012 Dimention. All rights reserved.
//

#include <FactoryEngine.h>

FTWorkspace::FTWorkspace()
{
    mpPad = new FTPad();
    mpHUD = new FTHUD();
    
    AddNode((FTNode*)mpPad);
    AddNode((FTNode*)mpHUD);
}

FTWorkspace::~FTWorkspace()
{
    delete mpPad;
    delete mpHUD;
}

void FTWorkspace::SetViewportRect(FTRectf rect)
{
    FTLog(kFTLogWorkspace, "");
    glViewport(rect.origin.x, rect.origin.y, rect.size.x, rect.size.y);
}

void FTWorkspace::Render()
{    
    FTLog(kFTLogWorkspace, "");
    FTNode::Render();
    glFinish();
}



