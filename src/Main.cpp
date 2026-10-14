#include "app/EntryPoint.h"

using app::EntryPoint;

void main(int argc, char** argv) {
    EntryPoint::Run(argc > 0);
}
