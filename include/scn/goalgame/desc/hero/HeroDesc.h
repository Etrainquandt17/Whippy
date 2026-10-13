#ifndef SCN_GOALGAME_DESC_HERO_HERODESC_H
#define SCN_GOALGAME_DESC_HERO_HERODESC_H

#include "scn/goalgame/GGHeroKind.h"
#include "scn/step/hero/modeldesc/ModelDesc.h"
#include "types.h"

namespace scn {
namespace goalgame {
namespace desc {
namespace hero {

class HeroDesc {
public:
    static const step::hero::modeldesc::ModelDesc& Model(GGHeroKind kind);
    static const step::hero::modeldesc::AnimDesc& Anim(GGHeroKind kind);
    static const char* ModelPath(GGHeroKind kind);
    static const char* AnimPath(GGHeroKind kind);
};

}
}
}
}

#endif
