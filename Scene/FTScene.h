//
//  Copyright (c) 2012 Edvinas Sarkus. All rights reserved.
//


class FTScene
{
public:
                        FTScene();
                        ~FTScene();
    //
    // Workspace
    //
    void                Render();
    void                SetViewportRect(int x, int y, int width, int height);
    //
    // Camera
    //
    void                MoveBy(const FTVec2f deltaMove);
    void                RotateBy(const FTVec2f deltaRotation);
    void                ZoomBy(const GLfloat times);
    void                Look();
    void                Reset();
    void                SetProjectionMode(FTProjectionMode projectionMode);
    //
    // Lights           
    //
    void                TurnOnLight(int index);
    //
    // Model
    //
    void                CreateFace(FTVec3f vOrigin);
    void                ChangeFaceSize(FTVec3f vSize);
    
private:
    
    FTWorkspace*        m_pWorkspace;
    FTCamera*           m_pCamera;
    FTModelManager*     m_pModelManager;
    
};

