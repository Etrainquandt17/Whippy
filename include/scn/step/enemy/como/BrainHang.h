#ifndef SCN_STEP_ENEMY_COMO_BRAINHANG_H
#define SCN_STEP_ENEMY_COMO_BRAINHANG_H

#include "scn/step/enemy/BrainBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace como {

class BrainHang : public BrainBase {
public:
    BrainHang(Enemy& enemy);
    virtual bool onStart();
    virtual bool onRecover();
};

}
}
}
}

#endif
