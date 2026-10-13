#ifndef SCN_SUBGAME_SETSUNA_CHARA_AIM_H
#define SCN_SUBGAME_SETSUNA_CHARA_AIM_H

#include "hel/common/NonCopyable.h"
#include "hel/common/ScopedPtr.h"
#include "lyt/Layout.h"
#include "lyt/PaneAccessor.h"
#include "types.h"

namespace scn {
namespace subgame {
namespace setsuna {
namespace chara {

class Aim {
public:
    Aim();
    ~Aim();

    void updateMain();
    void drawLayout() const;
    void initialize();
    void start();
    void setResult();
    void reset();
    lyt::PaneAccessor hitEffectLoc();

private:
    int _0;
    hel::common::ScopedPtr<lyt::Layout> _4;
    hel::common::ScopedPtr<lyt::Layout> _8;
};

}
}
}
}

#endif
