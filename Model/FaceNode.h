
//
// Node: FaceNode should consits of concave polygons array
//
#pragma once

#include <Model/Node.h>

namespace ftr {

class Polygon;
class LineNode;
class PointNode;

class FaceNode : public Node
{
public:
    enum FaceType
    {
        kRectangle = 0
    };
    typedef std::vector<Polygon*>     TPolygonsVector;
    typedef std::vector<PointNode*>       TPointsVector;
    typedef std::vector<LineNode*>        TLinesVector;

                                        FaceNode();
                                        ~FaceNode();
    
    virtual void                        Render(RenderBundle& renderBundle);
    virtual NodeType                    Type() const { return kFace; }
    virtual void                        Transform(Mat4& m4Transformation);
    bool                                IsInFacePlane(Vec3 vec);
    bool                                Contains(Vec3 vec);
    void                                Cut(FaceNode* cutFace);
    
    void                                AddPolygon();
    void                                RemovePolygon();
    void                                AddPoint(PointNode* pPoint);
    void                                AddLine(LineNode* line);
    
    FaceType                            m_eType;
    
    void                                setSize(const Vec3 size);
    const Vec3&                       Size() const { return mSize; }
    void                                setOrigin(const Vec3 origin);
    const Vec3&                       Origin() const { return mOrigin; }
    
    const TPointsVector&                PointNodesVector() const { return mPointsVector; }
    
private:
    TPolygonsVector                     mPolygons;
    TLinesVector                        mLinesVector;
    TPointsVector                       mPointsVector;
    Vec3                              mOrigin;
    Vec3                              mSize;
};

}