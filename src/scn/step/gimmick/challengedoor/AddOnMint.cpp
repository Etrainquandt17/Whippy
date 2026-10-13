#include "scn/step/gimmick/challengedoor/AddOnMint.h"

#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "mintglue/VectorInline.h"
#include "mintglue/WrapNative.h"
#include "scn/step/Component.h"
#include "scn/step/Context.h"
#include "scn/step/challenge/Score.h"
#include "scn/step/effect/Kind.h"
#include "scn/step/gimmick/challengedoor/ChallengeDoor.h"
#include "scn/step/gimmick/challengedoor/MintChallengeDoor.h"
#include "util/ObjList.h"
#include "util/ObjRefHandle.h"

// TODO: these belong in the headers of their units, which do not exist yet.
namespace scn {
namespace step {

namespace map {

enum BinItemKind {
    BIN_ITEM_KIND_1 = 1,
    BIN_ITEM_KIND_6 = 6,
    BIN_ITEM_KIND_7 = 7,
    BIN_ITEM_KIND_F = 0xF,
};

enum BinItemVariation {
    BIN_ITEM_VARIATION_9 = 9,
};

}

namespace item {

class Item;

class Desc {
public:
    Desc(map::BinItemKind kind, u32, bool, map::BinItemVariation variation, const hel::math::Vector2& pos);

private:
    u32 _0[0xC];
};

class Manager {
public:
    util::ObjRefHandle<Item> request(const Desc& desc);
};

}

namespace core {

class PermEffectDetail {
public:
    void requestP(effect::Kind kind, const hel::math::Vector3& pos);
};

class PermEffect {
public:
    void requestP(effect::Kind kind, const hel::math::Vector3& pos) { mDetail.requestP(kind, pos); }

private:
    u32 _0[2];
    PermEffectDetail mDetail;
};

}
}
}

namespace scn {
namespace step {
namespace gimmick {
namespace challengedoor {

namespace {

// TODO: the challenge state of the Context, which has no members yet.
inline bool t_isChallenge(const Context& context) {
    return *reinterpret_cast<const bool*>(&context._0[0xF8]);
}

inline const challenge::Score& t_score(const Context& context) {
    return *reinterpret_cast<const challenge::Score*>(&context._0[0xD7]);
}

void t_SetZoom(f32 a, f32 b) {
    MintChallengeDoor::Obj().setZoom(a, b);
}

void t_UpdateZoom(u32 id, f32 rate) {
    MintChallengeDoor::Obj().updateZoom(id, rate);
}

void t_UnsetZoom(u32 id) {
    MintChallengeDoor::Obj().unsetZoom(id);
}

void t_RequestItem() {
    ChallengeDoor& obj = MintChallengeDoor::Obj();
    if (t_isChallenge(obj.component().context())) {
        map::BinItemKind kind;
        switch (t_score(obj.component().context()).medalKind()) {
        case 1:
            kind = map::BIN_ITEM_KIND_6;
            break;
        case 2:
            kind = map::BIN_ITEM_KIND_7;
            break;
        case 3:
            kind = map::BIN_ITEM_KIND_1;
            break;
        case 4:
            kind = map::BIN_ITEM_KIND_1;
            break;
        default:
            kind = map::BIN_ITEM_KIND_F;
            break;
        }
        hel::math::Vector2 offs(obj.pos());
        offs.y += 3.0f;
        obj.component().itemManager().request(item::Desc(kind, 0, false, map::BIN_ITEM_VARIATION_9, offs));
        core::PermEffect& effect = obj.component().permEffect();
        effect.requestP(static_cast<effect::Kind>(0x338), offs.toVector3());
    }
}

void t_RequestItemCombo() {
    if (t_score(MintChallengeDoor::Obj().component().context()).medalKind() == 4) {
        t_RequestItem();
    }
}

}

namespace AddOnMint {

void RegisterAll(mintvm::VMCore& core) {
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Gimmick.ChallengeDoor.Custom", "int SetZoom(float,float)", SetZoom,
                         reinterpret_cast<int (*)(f32, f32)>(t_SetZoom));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Gimmick.ChallengeDoor.Custom", "void UpdateZoom(int,float)", UpdateZoom, &t_UpdateZoom);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Gimmick.ChallengeDoor.Custom", "void UnsetZoom(int)", UnsetZoom, &t_UnsetZoom);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Gimmick.ChallengeDoor.Custom", "void RequestItem()", RequestItem, &t_RequestItem);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Gimmick.ChallengeDoor.Custom", "void RequestItemCombo()", RequestItemCombo, &t_RequestItemCombo);
}

}
}
}
}
}
