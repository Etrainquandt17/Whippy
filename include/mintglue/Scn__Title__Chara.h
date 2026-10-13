#ifndef MINTGLUE_SCN__TITLE__CHARA_H
#define MINTGLUE_SCN__TITLE__CHARA_H

#include "mintvm/MintPtr.h"
#include "types.h"

namespace mintvm {

class VMCore;

}

namespace scn {
namespace title {

class Chara;

}}  // namespace scn::title

namespace mintglue {

class Scn__Title__Chara {
public:
    static void AddOn(mintvm::VMCore& core);

    void changeAnim(const char* name, int frame);
    bool isAnimLooped();
    void effectRequestN(u32 index, const char* name);

private:
    mintvm::MintPtr<scn::title::Chara> mChara;
};

}  // namespace mintglue

#endif
