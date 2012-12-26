// 
//  Copyright (c) 2012 Dimention. All rights reserved.
//

class FTWorkspace : public FTNode
{
public:
                        FTWorkspace();
                        ~FTWorkspace();
    virtual void        Render();
    void                SetViewportRect(FTRect rect);
    
private:
    FTPad*              mpPad;
    FTHUD*              mpHUD;
};

