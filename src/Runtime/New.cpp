#include <xenoblade/PowerPC_EABI_Support/include/stl/new>
#include <xenoblade/types.h>

// Nothing here is called. The function makes the compiler emit the type information and
// the destructor of std::exception in this unit, where the original has them.
static void dummy() {
    throw std::bad_alloc();
}
