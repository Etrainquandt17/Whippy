#ifndef SND_MINTSEREQUESTOR_H
#define SND_MINTSEREQUESTOR_H

#include "types.h"

namespace snd {

class SERequestor;

namespace MintSERequestor {

void RegisterForce(SERequestor& obj);
void Unregister();
void Start(u32 id);
void Stop();

}

}  // namespace snd

#endif
