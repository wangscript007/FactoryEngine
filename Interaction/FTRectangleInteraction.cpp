
#include <Interaction/FTRectangleInteraction.h>

void FTRectangleInteraction::Render()
{
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
    static GLfloat normals1[] = {0,1,0,  0,1,0,  0,1,0,  0,1,0};             // v0-v1-v2-v3
    static GLfloat normals2[] = {0,-1,0,  0,-1,0,  0,-1,0,  0,-1,0};             // v0-v1-v2-v3
    //
    // colors
    //
    static GLfloat colors[] = {1,0,0,  1,0,0,  1,0,0,  1,0,0};
    //
    // indices
    //
    static GLubyte indices1[] = {3,2,1,0};
    static GLubyte indices2[] = {0,1,2,3};
    
    
    
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glColorPointer(3, GL_FLOAT, 0, colors);
    //
    // Top
    //
    glNormalPointer(GL_FLOAT, 0, normals1);
    glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, indices1);
    //
    // Bottom
    //
    glNormalPointer(GL_FLOAT, 0, normals2);
    glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, indices2);
    
    
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
}

#pragma mark Instance

void FTRectangleInteraction::Begin()
{
    
}

void FTRectangleInteraction::End()
{
    
}

void FTRectangleInteraction::SetSize(const O5Vec3 vSize)
{
    m_vSize = vSize;
}

void FTRectangleInteraction::SetOrigin(const O5Vec3 vOrigin)
{
    m_vOrigin = vOrigin;
}

