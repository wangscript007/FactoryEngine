
//
// Node: Face should consits of concave polygons array
//
#pragma once

#include <Model/FTModel.h>


class FTPolygon;
class FTLine;
class FTPoint;

class FTFace : public FTModel
{
public:
    enum FaceType
    {
        kRectangle = 0
    };
    typedef std::vector<FTPolygon*>     TPolygonsVector;
    typedef std::vector<FTPoint*>       TPointsVector;
    typedef std::vector<FTLine*>        TLinesVector;

                                        FTFace();
                                        ~FTFace();
    
    virtual void                        Render();
    virtual NodeType Type() const { return kFace; }
    bool                                IsInFacePlane(O5Vec3 vec);
    bool                                Contains(O5Vec3 vec);
    void                                Cut(FTFace* cutFace);
    
    void                                AddPolygon();
    void                                RemovePolygon();
    void                                AddPoint(FTPoint* pPoint);
    void                                AddLine(FTLine* pLine);
    
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

