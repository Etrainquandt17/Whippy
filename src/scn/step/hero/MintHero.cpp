#include "scn/step/hero/MintHero.h"

#include "hel/common/PointerWrapper.h"

namespace scn {
namespace step {
namespace hero {

namespace {

hel::common::PointerWrapper<Hero> t_obj;

}

namespace MintHero {

void Register(Hero& obj) {
    t_obj.set(obj);
}

void Unregister(Hero&) {
    t_obj.reset();
}

Hero& Obj() {
    return t_obj.ref();
}

}
}
}
}
