#ifndef SCN_STEP_CHARA_MINTMODELROTCTRL_H
#define SCN_STEP_CHARA_MINTMODELROTCTRL_H

#include "types.h"

namespace scn {
namespace step {
namespace chara {

class ModelRotCtrl;

namespace MintModelRotCtrl {

void Register(ModelRotCtrl& obj);
void Unregister(ModelRotCtrl& obj);
void SetValid(bool valid);
void ResetRotTarget();
f32 GetRotH();
void InitRotH(f32 rot);
void SetRotH(f32 rot);
void SetRotHTarget(f32 rot);
void SetRotHIntpRate(f32 rate);
void SetRotHIntoTarget();
f32 GetRotV();
void InitRotV(f32 rot);
void SetRotV(f32 rot);
void SetRotVTarget(f32 rot);
void SetRotVIntpRate(f32 rate);
void SetRotVIntoTarget();
f32 GetRotD();
void InitRotD(f32 rot);
void SetRotD(f32 rot);
void SetRotDTarget(f32 rot);
void SetRotDIntpRate(f32 rate);
void SetRotDIntoTarget();

}}}}  // namespace scn::step::chara::MintModelRotCtrl

#endif
