#include "mintvm/MintFuncProxy.h"

namespace mintvm {

void N_Mint_Cast_i2f(MintFuncProxy& proxy) {
    proxy.useRetVal();
    proxy.setRet_f32(static_cast<float>(proxy.getArg_s32(0)));
}

void N_Mint_Cast_f2i(MintFuncProxy& proxy) {
    proxy.useRetVal();
    proxy.setRet_s32(static_cast<int>(proxy.getArg_f32(0)));
}

}  // namespace mintvm
