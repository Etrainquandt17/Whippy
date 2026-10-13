#ifndef SCN_STEP_BOSS_WHISPY_ENEMYREQBUFF_H
#define SCN_STEP_BOSS_WHISPY_ENEMYREQBUFF_H

#define HEL_COMMON_MUTABLEARRAY_DESTRUCTOR_IN_CLASS

#include "hel/common/MutableArray.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace whispy {

class EnemyReqBuff {
public:
    struct ReqData {
        u32 mKind;
        u32 mSize;
        u32 _8;
    };

    EnemyReqBuff();

    void add(const ReqData& data);
    void clear();
    bool isEmpty() const;
    ReqData pick();

private:
    hel::common::MutableArray<ReqData, 10> mBuff;
};

}}}}  // namespace scn::step::boss::whispy

#endif
