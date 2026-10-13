#include <kdc/revolution/BASE.h>
#include <kdc/revolution/DB.h>
#include <kdc/revolution/OS.h>

OSDebugInterface* __DBInterface;

BOOL DBIsDebuggerPresent() {
    if (__DBInterface == NULL) {
        return FALSE;
    }
    return __DBInterface->usingDebugger;
}
