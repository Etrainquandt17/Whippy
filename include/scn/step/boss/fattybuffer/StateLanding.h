#ifndef SCN_STEP_BOSS_FATTYBUFFER_STATELANDING_H
#define SCN_STEP_BOSS_FATTYBUFFER_STATELANDING_H

#include "scn/step/boss/StateBase.h"

namespace scn {
namespace step {
namespace boss {
namespace fattybuffer {

class StateLanding : public StateBase {
public:
    StateLanding(Boss* boss);
    virtual ~StateLanding();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}}}}  // namespace scn::step::boss::fattybuffer

#endif
