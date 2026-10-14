#define HEL_COMMON_MUTABLEARRAY_ADD_IN_CLASS
#define HEL_COMMON_MUTABLEARRAY_REMOVEATINDEX_IN_CLASS

#include "scn/step/boss/fattybuffer/EnemyReqBuff.h"

#include "app/Random.h"

using app::Random;

namespace scn {
namespace step {
namespace boss {
namespace fattybuffer {

EnemyReqBuff::EnemyReqBuff() : mBuff() {}

void EnemyReqBuff::add(const ReqData& data) {
    mBuff.add(data);
}

void EnemyReqBuff::clear() {
    mBuff.clear();
}

bool EnemyReqBuff::isEmpty() const {
    return mBuff.count() == 0;
}

EnemyReqBuff::ReqData EnemyReqBuff::pick() {
    u32 index = Random::RandU32(mBuff.count());
    ReqData data = mBuff[index];
    mBuff.removeAtIndex(index);
    return data;
}

}}}}  // namespace scn::step::boss::fattybuffer
