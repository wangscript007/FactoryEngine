
#pragma once

#include <Model/Model.h>
#include <Model/Point.h>

namespace ftr {

class Line : public Model
{
public:
    Line(Point* pStartPoint, Point* pEndPoint);
    virtual ~Line() {}
    
    virtual void Render();
    virtual NodeType Type() const { return kLine; }
    void SetEndPoint(Point* pEndPoint) { m_pEndPoint = pEndPoint; }
    void SetStartPoint(Point* pStartPoint) { m_pStartPoint = pStartPoint; }
    Point* StartPoint() const { return m_pStartPoint; }
    Point* EndPoint() const { return m_pEndPoint; }
    virtual void Transform(const Mat4& m4Transformation);

private:
    Point* m_pStartPoint;
    Point* m_pEndPoint;
};

}