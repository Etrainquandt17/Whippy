#include "scn/step/boss/galactaknight/AttackDesc.h"

namespace scn {
namespace step {
namespace boss {
namespace galactaknight {

AttackDesc::AttackDesc(ScriptKind kind, bool a) : _0(kind), _4(0.0f), _8(0), _C(a), _D(false), _E(false) {}

AttackDesc::AttackDesc(ScriptKind kind, f32 a, u32 b, bool c) : _0(kind), _4(a), _8(b), _C(c), _D(false), _E(false) {}

}
}
}
}
