
//
// Node: Face should consits of concave polygons array
//
#pragma once

#include <Model/Model.h>

namespace Factory {

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
    virtual void                        Transform(O5Mat4& m4Transformation);
    bool                                IsInFacePlane(O5Vec3 vec);
    bool                                Contains(O5Vec3 vec);
    void                                Cut(Face* cutFace);
    
    void                                AddPolygon();
    void                                RemovePolygon();
    void                                AddPoint(Point* pPoint);
    void                                AddLine(Line* pLine);
    
    FaceType                            m_eType;
    
    void                                SetSize(const O5Vec3 vSize);
    const O5Vec3&                       Size() const { return m_vSize; }
    void                                SetOrigin(const O5Vec3 vOrigin);
    const O5Vec3&                       Origin() const { return m_vOrigin; }
    
    const TPointsVector&                PointsVector() const { return m_vPointsVector; }
    
private:
    TPolygonsVector                     m_vPolygons;
    TLinesVector                        m_vLinesVector;
    TPointsVector                       m_vPointsVector;
    O5Vec3                              m_vOrigin;
    O5Vec3                              m_vSize;
};

}