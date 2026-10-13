#ifndef SCN_SUBGAME_SETSUNA_CHARA_BLIND_H
#define SCN_SUBGAME_SETSUNA_CHARA_BLIND_H

#include "hel/common/ScopedPtr.h"
#include "lyt/Layout.h"
#include "types.h"

namespace scn {
namespace subgame {
namespace setsuna {
namespace chara {

class Blind {
public:
    enum Type {
        TYPE_FOG_1,
        TYPE_FOG_2,
        TYPE_FOG_3,
        TYPE_WOOD_1,
        TYPE_WOOD_2,
        TYPE_NUM,
    };

    Blind();
    ~Blind();

    void updateMain();
    void updateDebug();
    void drawLayout() const;
    void fadeIn(Type type);
    void fadeOut();

private:
    hel::common::ScopedPtr<lyt::Layout> mFog;
    hel::common::ScopedPtr<lyt::Layout> mWood;
    lyt::Layout* mLayout;
    Type mType;
    int mState;
};

}}}}  // namespace scn::subgame::setsuna::chara

#endif
