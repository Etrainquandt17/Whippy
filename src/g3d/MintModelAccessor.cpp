#include "g3d/MintModelAccessor.h"

#include "g3d/ModelAccessor.h"

namespace g3d {

namespace {

ModelAccessor t_obj;

}

namespace MintModelAccessor {

void RegisterForce(const ModelAccessor& obj) {
    t_obj = obj;
}

void Unregister() {
    t_obj = ModelAccessor();
}

void SetVisibility(bool visible) {
    t_obj.setVisibility(visible);
}

}
}
