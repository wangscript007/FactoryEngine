
#include <Processing/PointNodeIterator.h>
#include <Model/PointNode.h>

namespace ftr {

PointNodeIterator& PointNodeIterator::operator ++ ()
{
    if (mEdge == NULL) {
        mEdge = mPointNode.mEdge;
    } else {
        for (int i = 0; i < 2; i++) {
            if ((mEdge->originNode() != &mPointNode) && mEdge->next()) {
                mEdge = mEdge->next();
            } else {
                mEdge = mEdge->twin();
            }
        }
        if (mEdge == mPointNode.mEdge) {
            mEdge = NULL;
        }
    }
    return *this;
}

PointNodeIterator& PointNodeIterator::operator -- ()
{
    if (mEdge == mPointNode.mEdge) {
        mEdge = NULL;
    } else {
        if (mEdge == NULL) {
            Edge* beginEdge = mPointNode.mEdge->prev();
            if (beginEdge) {
                mEdge = beginEdge->twin();
            }
        } else {
            for (int i = 0; i < 2; i++) {
                if ((mEdge->originNode() == &mPointNode) && mEdge->prev()) {
                    mEdge = mEdge->prev();
                } else {
                    mEdge = mEdge->twin();
                }
            }
        }
    }
    return *this;
}

}