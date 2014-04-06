
#pragma once


namespace ftr {

class ModelEditor;
class FaceNode;

class FaceExtruder
{
public:
    struct Result {
        int createdEdges;
        int createdFaces;
        Result() : createdEdges(0), createdFaces(0) {};
    };
    
    FaceExtruder(ModelEditor& modelEditor);
    virtual ~FaceExtruder();
    
    void Extrude(FaceNode& faceNode);
    
private:
    ModelEditor& mModelEditor;
    FaceNode* mFaceNode;
    
};
    
}

