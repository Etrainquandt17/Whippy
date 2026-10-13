#ifndef SCN_STEP_ENEMY_BURABURADEE_BRAINHANG_H
#define SCN_STEP_ENEMY_BURABURADEE_BRAINHANG_H

#include "scn/step/enemy/BrainBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace buraburadee {

class BrainHang : public BrainBase {
public:
    BrainHang(Enemy& enemy);
    virtual bool onStart();
    virtual bool onLanding();
    virtual void update();
};

}
}
}
}

#endif
