
typedef enum {
    kFTProjectionModeProjection,
    kFTProjectionModeOrthographic
} FTProjectionMode;

class FTCamera : public FTModel
{
public:
                        FTCamera();
                        FTCamera(const FTVec3f coords);
    void                MoveBy(const FTVec2f deltaMove);
    void                RotateBy(const FTVec2f deltaRotation);
    void                ZoomBy(const GLfloat times);
    void                Look();
    void                SetProjectionMode(FTProjectionMode projectionMode);
    void                Reset();
private:
    FTVec2f             mvRotated;
    FTVec2f             mvMoved;
    FTVec3f             mvCoords;
    FTProjectionMode    mprojectionMode;
    GLdouble             mfZoomFactor;
};

