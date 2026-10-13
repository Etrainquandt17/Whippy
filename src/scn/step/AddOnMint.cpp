#include "scn/step/AddOnMint.h"

#include "scn/step/boss/AddOnMint.h"
#include "scn/step/camera/AddOnMint.h"
#include "scn/step/core/AddOnMint.h"

// TODO: these belong in the headers of their units, which do not exist yet.
namespace scn {
namespace step {

namespace chara {
namespace AddOnMint {
void RegisterAll(mintvm::VMCore& core);
}}  // namespace chara::AddOnMint

namespace enemy {
namespace AddOnMint {
void RegisterAll(mintvm::VMCore& core);
}}  // namespace enemy::AddOnMint

namespace hero {
namespace AddOnMint {
void RegisterAll(mintvm::VMCore& core);
}}  // namespace hero::AddOnMint

namespace sfx {
namespace AddOnMint {
void RegisterAll(mintvm::VMCore& core);
}}  // namespace sfx::AddOnMint

namespace vacuum {
namespace AddOnMint {
void RegisterAll(mintvm::VMCore& core);
}}  // namespace vacuum::AddOnMint

namespace gimmick {
namespace AddOnMint {
void RegisterAll(mintvm::VMCore& core);
}}  // namespace gimmick::AddOnMint

namespace ocoll {
namespace AddOnMint {
void RegisterAll(mintvm::VMCore& core);
}}  // namespace ocoll::AddOnMint

namespace AddOnMint {

void RegisterAll(mintvm::VMCore& core) {
    boss::AddOnMint::RegisterAll(core);
    camera::AddOnMint::RegisterAll(core);
    chara::AddOnMint::RegisterAll(core);
    core::AddOnMint::RegisterAll(core);
    enemy::AddOnMint::RegisterAll(core);
    hero::AddOnMint::RegisterAll(core);
    sfx::AddOnMint::RegisterAll(core);
    vacuum::AddOnMint::RegisterAll(core);
    gimmick::AddOnMint::RegisterAll(core);
    ocoll::AddOnMint::RegisterAll(core);
}

}}}  // namespace scn::step::AddOnMint
