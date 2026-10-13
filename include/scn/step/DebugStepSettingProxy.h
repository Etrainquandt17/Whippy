#ifndef SCN_STEP_DEBUGSTEPSETTINGPROXY_H
#define SCN_STEP_DEBUGSTEPSETTINGPROXY_H

namespace scn {
namespace step {

class DebugStepSettingProxy {
public:
    static bool GetGeneralSettingIsReverseWorld();
    static bool GetAlertInfoBossHandicapMonitor();
    static int GetHeroSettingStoneKind();
};

}}  // namespace scn::step

#endif
