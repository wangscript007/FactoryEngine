

#include <Processing/FaceTraversal.h>
#include <Graph/Vertex.h>
#include <Graph/Edge.h>

namespace ftr {
    
FaceTraversal::FaceTraversal(Vertex& vertex)
    :mVertex(vertex)
    ,mResult(NULL)
    ,mTriangle(NULL)
{
    
}
    
void FaceTraversal::Find(Result& result)
{
    mResult = &result;

    AppendResult(mVertex);
    Find(mVertex);

    if(mResult->mVertexes.size() < 3) {
        mResult->mVertexes.clear();
    }
}
 
bool FaceTraversal::Find(Vertex& current)
{
    for (auto &edge : current.mEdges) {
        Vertex* vertex = edge->OtherEnd(current);
        std::cout << Description() << vertex->mName << "\n";
        /* Conditions
        * Must not be already in result pathvertex
        * Must be in same plane as previous vertexes
        * Must be not visited before?
        */
        if (!IsPrev(*vertex)
            && !IsInResultPath(*vertex)
            && !IsVisited(*vertex)
            && IsInPlane(*vertex))
        {
            /* End condition
            * Equals to initial vertex
            */
            if (&mVertex == vertex) {
                return true;
            } else {
                AppendResult(*vertex);
                if (Find(*vertex)) return true;
                else mResult->mVertexes.pop_back();
            }
        }
    }
    return false;
}
    
    
void FaceTraversal::AppendResult(Vertex& vertex)
{
    mResult->mVertexes.push_back(&vertex);
    
}
    
#pragma mark - Conditions checking
    
bool FaceTraversal::IsPrev(const Vertex& vertex) const
{
    auto &vertexes = mResult->mVertexes;
    if (vertexes.size() > 1) {
        Vertex* prev = *(vertexes.end()-2);
        return prev == &vertex;
    }
    return false;
}
    
bool FaceTraversal::IsInPlane(const Vertex& vertex)
{
    return true;
}
    
bool FaceTraversal::IsInResultPath(const Vertex& vertex) const
{
    auto &vertexes = mResult->mVertexes;
    return std::find(vertexes.begin()+1, vertexes.end(), &vertex) != vertexes.end();
}
    
bool FaceTraversal::IsVisited(const Vertex& vertex) const
{
    return false;
}

std::string FaceTraversal::Description() const
{
    std::stringstream ss;
    for (auto &vertex : mResult->mVertexes) {
        ss << vertex->mName << "-";
    }
    return ss.str();
}
    
}

