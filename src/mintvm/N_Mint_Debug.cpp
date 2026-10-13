#include "mintvm/MintFuncProxy.h"
#include "mintvm/MintSystemCall.h"
#include "mintvm/stdc.h"

namespace mintvm {

namespace {

void t_AssertFail() {
    MintSystemCall::messageHandler(MINT_MSG_WARNING, "Assert Fail", "");
}

void t_TestFail() {
    MintSystemCall::messageHandler(MINT_MSG_WARNING, "Test Fail!", "");
}

}

void N_Mint_Debug_Assert(MintFuncProxy& proxy) {
    MINT_ASSERT("N_Mint_Debug.cpp", 37, proxy.getArg_bool(0));
}

void N_Mint_Debug_Assert_i(MintFuncProxy& proxy) {
    if (proxy.getArg_s32(0) != proxy.getArg_s32(1)) {
        printf("[Assert_i] 期待: %d, 実際: %d\n", proxy.getArg_s32(0), proxy.getArg_s32(1));
        t_AssertFail();
    }
}

void N_Mint_Debug_Assert_f(MintFuncProxy& proxy) {
    if (proxy.getArg_f32(0) != proxy.getArg_f32(1)) {
        printf("[Assert_f] 期待: %f, 実際: %f\n", proxy.getArg_f32(0), proxy.getArg_f32(1));
        t_AssertFail();
    }
}

void N_Mint_Debug_Assert_ft(MintFuncProxy& proxy) {
    float diff = proxy.getArg_f32(0) - proxy.getArg_f32(1);
    float error = diff < 0.0f ? -diff : diff;
    if (error > proxy.getArg_f32(2)) {
        printf("[Assert_ft] 期待: %f, 実際: %f | 誤差=%f, 許容誤差= +-%f\n", proxy.getArg_f32(0), proxy.getArg_f32(1), diff,
               proxy.getArg_f32(2));
        t_AssertFail();
    }
}

void N_Mint_Debug_Test_i(MintFuncProxy& proxy) {
    if (proxy.getArg_s32(0) != proxy.getArg_s32(1)) {
        printf("[Test_i] 期待: %d, 実際: %d ... error!\n", proxy.getArg_s32(0), proxy.getArg_s32(1));
        t_TestFail();
    }
}

void N_Mint_Debug_Test_f(MintFuncProxy& proxy) {
    if (proxy.getArg_f32(0) != proxy.getArg_f32(1)) {
        printf("[Test_f] 期待: %f, 実際: %f ... error!\n", proxy.getArg_f32(0), proxy.getArg_f32(1));
        t_TestFail();
    }
}

void N_Mint_Debug_Test_ft(MintFuncProxy& proxy) {
    float diff = proxy.getArg_f32(0) - proxy.getArg_f32(1);
    float error = diff < 0.0f ? -diff : diff;
    if (!(error <= proxy.getArg_f32(2))) {
        printf("[Test_ft] 期待: %f, 実際: %f | 誤差=%f, 許容誤差= +-%f ... error!\n", proxy.getArg_f32(0),
               proxy.getArg_f32(1), diff, proxy.getArg_f32(2));
        t_TestFail();
    }
}

void N_Mint_Debug_Dump_i(MintFuncProxy& proxy) {
    printf("Dump(int) : %d\n", proxy.getArg_s32(0));
}

void N_Mint_Debug_Dump_f(MintFuncProxy& proxy) {
    printf("Dump(float) : %f\n", proxy.getArg_f32(0));
}

void N_Mint_Debug_print(MintFuncProxy& proxy) {
    printf("%s", proxy.getArg_string(0));
}

void N_Mint_Debug_puts(MintFuncProxy& proxy) {
    printf("%s\n", proxy.getArg_string(0));
}

void N_Mint_Debug_StackDump(MintFuncProxy& proxy) {
    proxy.mRegset->dump();
}

}
