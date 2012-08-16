
class FTUtils
{
public:
    static FTVec3d WindowFromScene(FTVec3d sceneVec);
    static FTVec3d SceneFromWindow(const FTVec3d windowVec);
    static GLfloat DepthAtWindowPoint(const FTVec2d point);
    static void PrintMatrix(int cols, int rows, GLdouble* matrix);
};

