#include "g3d/MintNodeAccessor.h"

#include "g3d/NodeAccessor.h"
#include "hel/math/Direction3.h"
#include "hel/mint/AddOnMathDirection3.h"
#include "hel/mint/AddOnMathVector3.h"

namespace g3d {

namespace {

NodeAccessor t_obj;

}

namespace MintNodeAccessor {

void RegisterForce(const NodeAccessor& obj) {
    t_obj = obj;
}

void Unregister() {
    t_obj = NodeAccessor();
}

void LoadWorldTrans() {
    hel::mint::AddOnMathVector3::Set(t_obj.worldTrans());
}

void LoadWorldRotate() {
    hel::mint::AddOnMathDirection3::Set(t_obj.worldRotate());
}

void LoadWorldScale() {
    hel::mint::AddOnMathVector3::Set(t_obj.worldScale());
}

bool IsVisible() {
    return t_obj.isVisible();
}

void SetVisibility(bool visible) {
    t_obj.setVisibility(visible);
}

void SetVisibilityBelow(bool visible) {
    t_obj.setVisibilityBelow(visible);
}

}}  // namespace g3d::MintNodeAccessor
