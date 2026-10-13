#include "mint/Engine.h"

#include "app/AddOnMint.h"
#include "g3d/AddOnMint.h"
#include "gobj/AddOnMint.h"
#include "hel/common/FixedString.h"
#include "hel/common/Traits.h"
#include "hel/mint/AddOnCast.h"
#include "hel/mint/AddOnMathDirection3.h"
#include "hel/mint/AddOnMathMath.h"
#include "mint/Manager.h"
#include "mint/ScriptArchive.h"
#include "mintglue/HEL__Math__Vector2.h"
#include "mintglue/HEL__Math__Vector3.h"
#include "mintglue/Scn__Title__Chara.h"
#include "mintglue/Scn__Title__Commander.h"
#include "scn/step/AddOnMint.h"
#include "snd/AddOnMint.h"
#include "std/cstring.h"

namespace mint {

Engine::Engine(Manager& manager) : mManager(manager), mCore(0xA00) {
    hel::mint::AddOnCast::RegisterAll(mCore);
    hel::mint::AddOnMathDirection3::RegisterAll(mCore);
    mintglue::HEL__Math__Vector3::AddOn(mCore);
    mintglue::HEL__Math__Vector2::AddOn(mCore);
    hel::mint::AddOnMathMath::RegisterAll(mCore);
    app::AddOnMint::RegisterAll(mCore);
    g3d::AddOnMint::RegisterAll(mCore);
    gobj::AddOnMint::RegisterAll(mCore);
    scn::step::AddOnMint::RegisterAll(mCore);
    snd::AddOnMint::RegisterAll(mCore);
    mintglue::Scn__Title__Chara::AddOn(mCore);
    mintglue::Scn__Title__Commander::AddOn(mCore);
    addModuleBellow("Mint");
}

Engine::~Engine() {}

const mintvm::VMCore& Engine::core() const {
    return mCore;
}

void Engine::addModuleBellow(const char* name) {
    const ScriptArchive& archive = mManager.scriptArchive();
    hel::common::FixedString<64> prefix = hel::common::FixedStringIN<char, 64>::FromFormat("%s.", name);
    u32 length = hel::common::Traits<char>::Strlen(prefix);
    for (u32 i = 0; i < archive.count(); i++) {
        ScriptArchive::Script script = archive.at(i);
        if (script.name->length >= length && strncmp(script.name->str, prefix, length) == 0) {
            mCore.addScript(script.data);
        }
    }
}

}  // namespace mint
