#ifndef SCN_STEP_BOSS_HANDICAP_H
#define SCN_STEP_BOSS_HANDICAP_H

namespace scn {
namespace step {
namespace boss {

class Boss;

class Handicap {
public:
    Handicap(Boss& boss);

    void setup();

private:
    Boss& mBoss;
};

}
}
}

#endif
