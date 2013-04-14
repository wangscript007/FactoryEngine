
#include <Model/Line.h>

namespace ftr {

Line::Line(Point* pStartPoint, Point* pEndPoint)
    :m_pStartPoint(pStartPoint)
    ,m_pEndPoint(pEndPoint)
{}

#pragma mark - Instance


void Line::Render()
{
    Node::Render();
    if (m_pStartPoint) {
        m_pStartPoint->Render();
    }
    if (m_pEndPoint) {
        m_pEndPoint->Render();
    }
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    glLineWidth(1);

    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    glBegin(GL_LINES);
    {
        Vec3 startVec = m_pStartPoint->m_vOrigin;
        Vec3 endVec = m_pEndPoint->m_vOrigin;
        glVertex3d(startVec.m_fX,
                   startVec.m_fY,
                   startVec.m_fZ);
        glVertex3d(endVec.m_fX,
                   endVec.m_fY,
                   endVec.m_fZ);
    }
    glEnd();
}

void Line::Transform(const Mat4& m4Transformation)
{
    m_pStartPoint->Transform(m4Transformation);
    m_pEndPoint->Transform(m4Transformation);
}
    
}



