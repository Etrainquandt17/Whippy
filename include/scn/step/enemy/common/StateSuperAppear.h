#ifndef SCN_STEP_ENEMY_COMMON_STATESUPERAPPEAR_H
#define SCN_STEP_ENEMY_COMMON_STATESUPERAPPEAR_H

#include "ostop/ReqHandle.h"
#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace common {

class StateSuperAppear : public StateBase {
public:
    StateSuperAppear(Enemy* enemy, const ::ostop::ReqHandle& handle, int _18);
    virtual ~StateSuperAppear();
};

}}}}  // namespace scn::step::enemy::common

#endif
