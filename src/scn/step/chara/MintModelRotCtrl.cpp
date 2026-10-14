#include "scn/step/chara/MintModelRotCtrl.h"

#include "hel/common/PointerWrapper.h"
#include "scn/step/chara/ModelRotCtrl.h"

using hel::common::PointerWrapper;

namespace scn {
namespace step {
namespace chara {

namespace {

PointerWrapper<ModelRotCtrl> t_obj;

}

namespace MintModelRotCtrl {

void Register(ModelRotCtrl& obj) {
    t_obj.set(obj);
}

void Unregister(ModelRotCtrl&) {
    t_obj.reset();
}

void SetValid(bool valid) {
    t_obj->setValid(valid);
}

void ResetRotTarget() {
    t_obj->resetRotTarget();
}

f32 GetRotH() {
    return t_obj->getRotH();
}

void InitRotH(f32 rot) {
    t_obj->initRotH(rot);
}

void SetRotH(f32 rot) {
    t_obj->setRotH(rot);
}

void SetRotHTarget(f32 rot) {
    t_obj->setRotHTarget(rot);
}

void SetRotHIntpRate(f32 rate) {
    t_obj->setRotHIntpRate(rate);
}

void SetRotHIntoTarget() {
    t_obj->setRotHIntoTarget();
}

f32 GetRotV() {
    return t_obj->getRotV();
}

void InitRotV(f32 rot) {
    t_obj->initRotV(rot);
}

void SetRotV(f32 rot) {
    t_obj->setRotV(rot);
}

void SetRotVTarget(f32 rot) {
    t_obj->setRotVTarget(rot);
}

void SetRotVIntpRate(f32 rate) {
    t_obj->setRotVIntpRate(rate);
}

void SetRotVIntoTarget() {
    t_obj->setRotVIntoTarget();
}

f32 GetRotD() {
    return t_obj->getRotD();
}

void InitRotD(f32 rot) {
    t_obj->initRotD(rot);
}

void SetRotD(f32 rot) {
    t_obj->setRotD(rot);
}

void SetRotDTarget(f32 rot) {
    t_obj->setRotDTarget(rot);
}

void SetRotDIntpRate(f32 rate) {
    t_obj->setRotDIntpRate(rate);
}

void SetRotDIntoTarget() {
    t_obj->setRotDIntoTarget();
}

}}}}  // namespace scn::step::chara::MintModelRotCtrl
