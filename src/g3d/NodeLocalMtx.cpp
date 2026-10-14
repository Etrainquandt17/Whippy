#include "g3d/NodeLocalMtx.h"

using hel::math::Matrix34;
using hel::math::Vector3;

namespace g3d {

NodeLocalMtx::NodeLocalMtx()
    : mIsEnable(false)
    , mCalcOp(NODE_LOCAL_MTX_CALC_OP_0) {
    reset();
}

void NodeLocalMtx::reset() {
    mIsEnable = false;
    mRTMtx = Matrix34();
    mScale = Vector3::ALL_ONE;
    mCalcOp = NODE_LOCAL_MTX_CALC_OP_0;
}

bool NodeLocalMtx::isEnable() const {
    return mIsEnable;
}

Matrix34 NodeLocalMtx::rtMtx() const {
    return mRTMtx;
}

void NodeLocalMtx::setRTMtx(const Matrix34& mtx) {
    mRTMtx = mtx;
    mIsEnable = true;
}

Vector3 NodeLocalMtx::scale() const {
    return mScale;
}

void NodeLocalMtx::setScale(const Vector3& scale) {
    mScale = scale;
    mIsEnable = true;
}

void NodeLocalMtx::setCalcOp(NodeLocalMtxCalcOp op) {
    mCalcOp = op;
}

}  // namespace g3d
