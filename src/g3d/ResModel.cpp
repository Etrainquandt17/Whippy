#include "g3d/ResModel.h"

#include "g3d/ResModelContext.h"

namespace g3d {

ResModel::ResModel()
    : mFile()
    , mObj(0) {}

ResModel::ResModel(const ResModelContext& context)
    : mFile(context.resFile())
    , mObj(0) {
    mObj = mFile.model(context.name());
}

u32 ResModel::nodeCount() const {
    return mObj.GetResNodeNumEntries();
}

ResNode ResModel::nodeByIndex(u32 index) const {
    return ResNode(mObj.GetResNode(static_cast<int>(index)));
}

ResNode ResModel::nodeByName(const char* name) const {
    return ResNode(mObj.GetResNode(name));
}

}  // namespace g3d
