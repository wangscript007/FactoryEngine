
//
// Node: Face should consits of concave polygons array
//
#pragma once

class FTFace : public FTModel
{
public:
    enum FaceType
    {
        FTRectangle = 0
    };
    
    typedef std::vector<FTPolygon*>     FTPolygonsVector;
    typedef std::vector<FTVec3d>        VertextVector;

                                        FTFace();
                                        ~FTFace();
    
    virtual void                        Render();
    bool                                IsInFacePlane(FTVec3f vec);
    bool                                Contains(FTVec3f vec);
    void                                Cut(FTFace* cutFace);
    
    void                                AddPolygon();
    void                                RemovePolygon();
    
    FaceType                            m_eType;
    O5Vec3                              m_vOrigin;
    O5Vec3                              m_vSize;
    
private:
    FTPolygonsVector                    m_vPolygons;
};

