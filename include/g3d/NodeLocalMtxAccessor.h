#ifndef G3D_NODELOCALMTXACCESSOR_H
#define G3D_NODELOCALMTXACCESSOR_H

#include "g3d/NodeLocalMtx.h"

namespace g3d {

class NodeLocalMtxAccessor {
public:
    NodeLocalMtxAccessor();
    NodeLocalMtxAccessor(NodeLocalMtx& mtx);

    bool isValid() const;
    void reset() const;
    hel::math::Matrix34 rtMtx() const;
    void setRTMtx(const hel::math::Matrix34& mtx) const;
    hel::math::Vector3 scale() const;
    void setScale(const hel::math::Vector3& scale) const;
    void setCalcOp(NodeLocalMtxCalcOp op) const;

private:
    NodeLocalMtx* mMtx;
};

}

#endif
