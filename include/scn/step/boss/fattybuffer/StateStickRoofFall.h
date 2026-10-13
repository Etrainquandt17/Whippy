#ifndef SCN_STEP_BOSS_FATTYBUFFER_STATESTICKROOFFALL_H
#define SCN_STEP_BOSS_FATTYBUFFER_STATESTICKROOFFALL_H

#include "scn/step/boss/StateBase.h"

namespace scn {
namespace step {
namespace boss {
namespace fattybuffer {

class StateStickRoofFall : public StateBase {
public:
    StateStickRoofFall(Boss* boss);
    virtual ~StateStickRoofFall();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}}}}  // namespace scn::step::boss::fattybuffer

#endif
