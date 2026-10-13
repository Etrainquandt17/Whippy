#ifndef SCN_STEP_HERO_SUPERSWORD_SWORDSELECTOR_H
#define SCN_STEP_HERO_SUPERSWORD_SWORDSELECTOR_H

#include "mint/Runner.h"
#include "types.h"

namespace scn {
namespace step {

class Component;

namespace hero {
namespace supersword {

enum GearSwordNodeKind {
    GEAR_SWORD_NODE_KIND_RARE = 5,
};

class SwordSelector {
public:
    SwordSelector(Component& component);
    ~SwordSelector();

    u32 getKind(bool isRare);
    bool isRare(GearSwordNodeKind kind);
    void setKind(u32 kind);
    void setRareTryCount(u32 count);

private:
    mint::Runner mRunner;
    u32 mKind;
    u32 mRareTryCount;
};

}
}
}
}

#endif
