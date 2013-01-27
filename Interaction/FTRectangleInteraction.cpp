
#include <Interaction/FTRectangleInteraction.h>
#include <Managers/FTModelManager.h>

FTRectangleInteraction::FTRectangleInteraction(FTModelManager& rModelManager)
    :m_rModelManager(rModelManager)
    ,m_bActive(false)
{}

void FTRectangleInteraction::Render()
{
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    //
    // vertices
    //
    GLfloat vertices[] =
    {
        m_vOrigin.m_fX,                  m_vOrigin.m_fY,             m_vOrigin.m_fZ,
        m_vOrigin.m_fX + m_vSize.m_fX,   m_vOrigin.m_fY,             m_vOrigin.m_fZ,
        m_vOrigin.m_fX + m_vSize.m_fX ,  m_vOrigin.m_fY,             m_vOrigin.m_fZ + m_vSize.m_fZ,
        m_vOrigin.m_fX,                  m_vOrigin.m_fY,             m_vOrigin.m_fZ + m_vSize.m_fZ
    };
    //
    // normals
    //
    static GLfloat normals[] = {0,1,0,  0,1,0,  0,1,0,  0,1,0};             // v0-v1-v2-v3
    //
    // colors
    //
    static GLfloat colors[] = {1,0,0,  0.5,0,0,  1,0,0,  0.5,0,0};
    //
    // indices
    //
    static GLubyte indices[] = {3,2,1,0};
    
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glColorPointer(3, GL_FLOAT, 0, colors);
    
    glNormalPointer(GL_FLOAT, 0, normals);
    glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, indices);
    
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
}

#pragma mark Instance

void FTRectangleInteraction::Begin()
{
    m_bActive = true;
    m_rModelManager.SelectedNode()->AddNode(this);
    m_vSize = O5Vec3();
}

void FTRectangleInteraction::End()
{
    if (m_bActive) {
        m_bActive = false;
        m_rModelManager.CreateRectangle(m_vOrigin, m_vSize);
        m_rModelManager.SelectedNode()->RemoveNode(this);
    }
}

void FTRectangleInteraction::SetSize(const O5Vec3 vSize)
{
    m_vSize = vSize;
}

void FTRectangleInteraction::SetOrigin(const O5Vec3 vOrigin)
{
    m_vOrigin = vOrigin;
}

