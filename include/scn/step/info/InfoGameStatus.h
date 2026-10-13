#ifndef SCN_STEP_INFO_INFOGAMESTATUS_H
#define SCN_STEP_INFO_INFOGAMESTATUS_H

#include "lyt/Layout.h"
#include "types.h"

namespace scn {
namespace step {
namespace info {

class BossPanel;
class WarpStarPanel;

class InfoGameStatus {
public:
    void startAnimOut();
    void startAnimIn();
    void startAnimOutS();
    void startAnimInS();
    BossPanel* bossPanel();
    WarpStarPanel& warpStarPanel();
    bool isWarpStarMap();
    bool isInfoIn();
    void checkLowBattery(u32 padChan);

private:
    u32 _0;
    lyt::Layout mLayout;
    BossPanel* _194;
    u8 _198[0x2760 - 0x198];
    bool _2760;
};

}}}  // namespace scn::step::info

#endif
