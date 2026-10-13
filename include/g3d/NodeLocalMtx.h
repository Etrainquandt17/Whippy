#ifndef G3D_NODELOCALMTX_H
#define G3D_NODELOCALMTX_H

#include "hel/math/Matrix34.h"
#include "hel/math/Vector3.h"

namespace g3d {

// TODO: name the values.
enum NodeLocalMtxCalcOp {
    NODE_LOCAL_MTX_CALC_OP_0,
    NODE_LOCAL_MTX_CALC_OP_1,
};

class NodeLocalMtx {
public:
    NodeLocalMtx();

    void reset();
    bool isEnable() const;
    hel::math::Matrix34 rtMtx() const;
    void setRTMtx(const hel::math::Matrix34& mtx);
    hel::math::Vector3 scale() const;
    void setScale(const hel::math::Vector3& scale);
    void setCalcOp(NodeLocalMtxCalcOp op);

private:
    hel::math::Matrix34 mRTMtx;
    hel::math::Vector3 mScale;
    bool mIsEnable;
    NodeLocalMtxCalcOp mCalcOp;
};

}  // namespace g3d

#endif
