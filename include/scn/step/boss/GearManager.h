#ifndef SCN_STEP_BOSS_GEARMANAGER_H
#define SCN_STEP_BOSS_GEARMANAGER_H

#include "types.h"

namespace scn {
namespace step {
namespace boss {

class Gear;

class GearManager {
public:
    Gear& gear(u32 index);
    void setup(u32 count);
    void onHitStopStart();
    void onHitStopEnd();
    void onObjStopStarted();
    void onObjStopFinished();
};

}}}  // namespace scn::step::boss

#endif
