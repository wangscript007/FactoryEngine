
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
    
    virtual void                        Render(Layer& layer);
    virtual NodeType                    Type() const { return kFace; }
    virtual void                        Transform(glm::mat4& m4Transformation);
    bool                                IsInFacePlane(glm::vec3 vec);
    bool                                Contains(glm::vec3 vec);
    void                                Cut(FaceNode* cutFace);
    
    void                                AddPolygon();
    void                                RemovePolygon();
    void                                AddPoint(PointNode* pPoint);
    void                                AddLine(LineNode* line);
    
    FaceType                            m_eType;
    
    void                                setSize(const glm::vec3 size);
    const glm::vec3&                       Size() const { return mSize; }
    void                                setOrigin(const glm::vec3 origin);
    const glm::vec3&                       Origin() const { return mOrigin; }
    
    const TPointsVector&                PointNodesVector() const { return mPointsVector; }
    
private:
    TPolygonsVector                     mPolygons;
    TLinesVector                        mLinesVector;
    TPointsVector                       mPointsVector;
    glm::vec3                              mOrigin;
    glm::vec3                              mSize;
};

}