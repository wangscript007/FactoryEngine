
//
// Node: Face should consits of concave polygons array
//
#pragma once

#include <Model/Model.h>

namespace ftr {

class Polygon;
class Line;
class Point;

class Face : public Model
{
public:
    enum FaceType
    {
        kRectangle = 0
    };
    typedef std::vector<Polygon*>     TPolygonsVector;
    typedef std::vector<Point*>       TPointsVector;
    typedef std::vector<Line*>        TLinesVector;

                                        Face();
                                        ~Face();
    
    virtual void                        Render();
    virtual NodeType                    Type() const { return kFace; }
    virtual void                        Transform(Mat4& m4Transformation);
    bool                                IsInFacePlane(Vec3 vec);
    bool                                Contains(Vec3 vec);
    void                                Cut(Face* cutFace);
    
    void                                AddPolygon();
    void                                RemovePolygon();
    void                                AddPoint(Point* pPoint);
    void                                AddLine(Line* line);
    
    FaceType                            m_eType;
    
    void                                setSize(const Vec3 size);
    const Vec3&                       Size() const { return mSize; }
    void                                setOrigin(const Vec3 origin);
    const Vec3&                       Origin() const { return mOrigin; }
    
    const TPointsVector&                PointsVector() const { return mPointsVector; }
    
private:
    TPolygonsVector                     mPolygons;
    TLinesVector                        mLinesVector;
    TPointsVector                       mPointsVector;
    Vec3                              mOrigin;
    Vec3                              mSize;
};

}