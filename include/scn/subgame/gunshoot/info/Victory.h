#ifndef SCN_SUBGAME_GUNSHOOT_INFO_VICTORY_H
#define SCN_SUBGAME_GUNSHOOT_INFO_VICTORY_H

#include "hel/common/ScopedPtr.h"
#include "lyt/Layout.h"
#include "scn/subgame/gunshoot/LevelKind.h"
#include "types.h"
#include "util/FrameCounter.h"

namespace scn {
namespace subgame {
namespace gunshoot {
namespace info {

class Victory {
public:
    Victory(LevelKind level);

    void updateMain();
    void draw() const;
    void startExplosion();
    void startClear();
    void exit();
    bool isExitEnd() const;

private:
    LevelKind mLevel;
    hel::common::ScopedPtr<lyt::Layout> mLayout;
    int _8;
    bool mIsVisible;
    util::FrameCounter mCounter;
};

}}}}  // namespace scn::subgame::gunshoot::info

#endif
