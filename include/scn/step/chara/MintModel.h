#ifndef SCN_STEP_CHARA_MINTMODEL_H
#define SCN_STEP_CHARA_MINTMODEL_H

#include "types.h"

namespace scn {
namespace step {
namespace chara {

class Model;

namespace MintModel {

void Register(Model& obj);
void Unregister(Model& obj);
void SetScale3(f32 x, f32 y, f32 z);

}}}}  // namespace scn::step::chara::MintModel

#endif
