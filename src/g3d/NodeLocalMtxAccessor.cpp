#include "g3d/NodeLocalMtxAccessor.h"

using hel::math::Matrix34;
using hel::math::Vector3;

namespace g3d {

NodeLocalMtxAccessor::NodeLocalMtxAccessor()
    : mMtx(0) {}

NodeLocalMtxAccessor::NodeLocalMtxAccessor(NodeLocalMtx& mtx)
    : mMtx(&mtx) {}

bool NodeLocalMtxAccessor::isValid() const {
    return mMtx != 0;
}

void NodeLocalMtxAccessor::reset() const {
    mMtx->reset();
}

Matrix34 NodeLocalMtxAccessor::rtMtx() const {
    return mMtx->rtMtx();
}

void NodeLocalMtxAccessor::setRTMtx(const Matrix34& mtx) const {
    mMtx->setRTMtx(mtx);
}

Vector3 NodeLocalMtxAccessor::scale() const {
    return mMtx->scale();
}

void NodeLocalMtxAccessor::setScale(const Vector3& scale) const {
    mMtx->setScale(scale);
}

void NodeLocalMtxAccessor::setCalcOp(NodeLocalMtxCalcOp op) const {
    mMtx->setCalcOp(op);
}

}  // namespace g3d
