#ifndef SCN_SUBGAME_CONTEXT_H
#define SCN_SUBGAME_CONTEXT_H

#include "types.h"

namespace hel {
namespace common {
template <int N>
class FixedString;
template <typename T, int N>
class MutableArray;
}
}

namespace scn {
namespace subgame {

class Context {
public:
    // TODO: name the other values.
    enum Kind {
        KIND_SETSUNA,
        KIND_1,
        KIND_2,
    };

    // TODO: _0 is the hero kind as a signed value (7 for nobody) and _8 a bool.
    struct Player {
        u32 _0;
        u32 _4;
        u32 _8;
    };
    typedef Player Entry;

    static Context Create();
    static const char* MenuDN(Kind kind);

    void addStepDNIfNeccesary(hel::common::MutableArray<hel::common::FixedString<64>, 24>& paths) const;
    bool isExtraMode() const;

    Kind mKind;
    Entry _4[4];
    u32 _34[4];
};

}
}

#endif
