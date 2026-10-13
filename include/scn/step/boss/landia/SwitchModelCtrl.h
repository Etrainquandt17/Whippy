#ifndef SCN_STEP_BOSS_LANDIA_SWITCHMODELCTRL_H
#define SCN_STEP_BOSS_LANDIA_SWITCHMODELCTRL_H

#include "types.h"
#include "util/ObjRefHandle.h"

namespace scn {
namespace step {
namespace boss {
namespace landia {

}
class Boss;
namespace landia {

class SwitchModelCtrl {
public:
    SwitchModelCtrl(Boss& boss);
    ~SwitchModelCtrl();
    void createLandiaDummy();
    void deadLandiaDummy();

private:
    Boss& mBoss;
    util::ObjRefHandle<Boss> mDummy;
};

}}}}  // namespace scn::step::boss::landia

#endif
