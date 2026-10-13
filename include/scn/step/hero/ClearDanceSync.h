#ifndef SCN_STEP_HERO_CLEARDANCESYNC_H
#define SCN_STEP_HERO_CLEARDANCESYNC_H

namespace scn {
namespace step {
namespace hero {

class ClearDanceSync {
public:
    bool isSync();
    int firstAnim() const;
    int secondAnim() const;
    int thirdAnim() const;
    int finishAnim() const;
};

}
}
}

#endif
