
//
// Node: Face should consits of concave polygons array
//
#pragma once

#include <Model/FTModel.h>

class  FTPolygon;

class FTFace : public FTModel
{
public:
    enum FaceType
    {
        kRectangle = 0
    };
    
    typedef std::vector<FTPolygon*>    FTPolygonsVector;
    typedef std::vector<O5Vec3>        VertextVector;

                                        FTFace();
                                        ~FTFace();
    
    virtual void                        Render();
    virtual NodeType Type() const { return kFace; }
    bool                                IsInFacePlane(O5Vec3 vec);
    bool                                Contains(O5Vec3 vec);
    void                                Cut(FTFace* cutFace);
    
    void                                AddPolygon();
    void                                RemovePolygon();
    
    FaceType                            m_eType;
    O5Vec3                              m_vOrigin;
    O5Vec3                              m_vSize;
    
private:
    FTPolygonsVector                    m_vPolygons;
};

