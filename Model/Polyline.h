
#pragma once

#include <Model/Node.h>
#include <Model/Point.h>

namespace Factory {

class Polyline : Model
{
public:
    typedef std::vector<Point*>  TPoinsVector;
    virtual ~Polyline() {}
    
private:
    TPoinsVector m_cPointsVector;
};
    
}

