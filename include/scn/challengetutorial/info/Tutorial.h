#ifndef SCN_CHALLENGETUTORIAL_INFO_TUTORIAL_H
#define SCN_CHALLENGETUTORIAL_INFO_TUTORIAL_H

#include "scn/challengetutorial/DialogKind.h"
#include "scn/step/ChallengeKind.h"
#include "types.h"

namespace lyt {
class Layout;
}

namespace mem {
class IAllocator;
}

namespace scn {
namespace challengetutorial {
namespace info {

class Manager;

class Tutorial {
public:
    struct Recipe {
        step::ChallengeKind mKind;
        bool _4;
        DialogKind mDialog;
    };

    Tutorial(Manager& manager, mem::IAllocator& allocator, lyt::Layout& layout);
    ~Tutorial();

    void appear(const Recipe& recipe);
    bool isAnimEnd() const;

    u32 _0[0x61D];
    bool _1874;
};

}}}  // namespace scn::challengetutorial::info

#endif
