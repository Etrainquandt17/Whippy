#ifndef SCN_STEP_HERO_CHARGEFLASH_H
#define SCN_STEP_HERO_CHARGEFLASH_H

namespace scn {
namespace step {
namespace hero {

// TODO: members and the other functions.
class ChargeFlash {
public:
    // TODO: enumerators.
    enum ChargeLv {
        CHARGE_LV_0,
        CHARGE_LV_1,
        CHARGE_LV_2,
        CHARGE_LV_3,
    };

    void set(ChargeLv lv);
    void clear();
};

}
}
}

#endif
