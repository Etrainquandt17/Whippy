#ifndef SCN_STEP_BOSS_ROAH_WEAPONCTRL_H
#define SCN_STEP_BOSS_ROAH_WEAPONCTRL_H

#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace roah {

}

class Boss;

namespace roah {

// TODO: members, and the request functions that take weapon types.
class WeaponCtrl {
public:
    struct ReqData {
        int _0;
        f32 _4;
        f32 _8;
        int _C;
    };

    WeaponCtrl(Boss& boss);
    ~WeaponCtrl();

    void update();
    void addReqData(const ReqData& data);
    void clearReqBuff();
    bool isReqBuffEmpty();
    ReqData popReqData();
    void request();
    void requestOneByOne();
    void requestStarInvisible();
    void requestOar();
    bool isCaught();
    void caughtSignal();

private:
    u32 _0[0x250 / 4];
};

}}}}  // namespace scn::step::boss::roah

#endif
