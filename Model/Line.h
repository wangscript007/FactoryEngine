
#pragma once

#include <Model/Model.h>
#include <Model/Point.h>

namespace ftr {

class Line : public Model
{
public:
    Line(Point* startPoint, Point* endPoint);
    virtual ~Line() {}
    
    virtual void Render();
    virtual NodeType Type() const { return kLine; }
    void setEndPoint(Point* endPoint) { mEndPoint = endPoint; }
    void setStartPoint(Point* startPoint) { mStartPoint = startPoint; }
    Point* StartPoint() const { return mStartPoint; }
    Point* EndPoint() const { return mEndPoint; }
    virtual void Transform(const Mat4& m4Transformation);

private:
    Point* mStartPoint;
    Point* mEndPoint;
};

}