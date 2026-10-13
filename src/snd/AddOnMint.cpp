#include "snd/AddOnMint.h"

#include "mintglue/WrapNative.h"
#include "snd/MintSERequestor.h"

// TODO: the original reaches an argument through one more level of inlining than MINT_ARG in
// mintglue/WrapNative.h has. It only shows where a binding is expanded in place, as two swapped
// registers. This stands in until the shared template has that level.
inline mintvm::MValue* mintArgAddr(mintvm::MintFuncProxy* proxy, unsigned int index) {
    return proxy->internal_getArg_addr(index);
}

inline void mintCallWrappedFunc(void (*func)(u32), mintvm::MintFuncProxy* proxy) {
    func(reinterpret_cast<mint_wrapNative_helper<u32>*>(mintArgAddr(proxy, 0))->mValue);
}

namespace snd {
namespace AddOnMint {

void RegisterAll(mintvm::VMCore& core) {
    MINT_NATIVE_FUNCTION(core, "Snd.SERequestor", "void Start(int)", Start, &MintSERequestor::Start);
    MINT_NATIVE_FUNCTION(core, "Snd.SERequestor", "void Stop()", Stop, &MintSERequestor::Stop);
}

}}  // namespace snd::AddOnMint
