#include "g3d/NodeLocalMtx.h"

#include "revolution/mtx.h"

namespace g3d {

NodeLocalMtx::NodeLocalMtx()
    : mIsEnable(false)
    , mCalcOp(NODE_LOCAL_MTX_CALC_OP_0) {
    reset();
}

void NodeLocalMtx::reset() {
    mIsEnable = false;
    mRTMtx = hel::math::Matrix34();
    mScale = hel::math::Vector3::ALL_ONE;
    mCalcOp = NODE_LOCAL_MTX_CALC_OP_0;
}

bool NodeLocalMtx::isEnable() const {
    return mIsEnable;
}

hel::math::Matrix34 NodeLocalMtx::rtMtx() const {
    return mRTMtx;
}

void NodeLocalMtx::setRTMtx(const hel::math::Matrix34& mtx) {
    mRTMtx = mtx;
    mIsEnable = true;
}

hel::math::Vector3 NodeLocalMtx::scale() const {
    return mScale;
}

void NodeLocalMtx::setScale(const hel::math::Vector3& scale) {
    mScale = scale;
    mIsEnable = true;
}

void NodeLocalMtx::setCalcOp(NodeLocalMtxCalcOp op) {
    mCalcOp = op;
}

}
