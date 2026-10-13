#include <kdc/revolution/AX.h>
#include <kdc/revolution/OS.h>
#include <kdc/revolution/version.h>

RVL_LIB_VERSION(AX, "Dec 11 2009", "15:55:44", "0x4302_145");

static BOOL __init = FALSE;

void AXInit(void) {
    AXInitEx(0);
}

BOOL AXIsInit() {
    return __init;
}

void AXInitEx(u32 mode) {
    if (!__init) {
        OSRegisterVersion(__AXVersion);

        __AXAllocInit();
        __AXVPBInit();
        __AXSPBInit();
        __AXAuxInit();
        __AXClInit();
        __AXOutInit(mode);

        __init = TRUE;
    }

}
