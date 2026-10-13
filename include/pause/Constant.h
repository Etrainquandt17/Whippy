#ifndef PAUSE_CONSTANT_H
#define PAUSE_CONSTANT_H

namespace pause {

// TODO: name the values.
enum PageResKind {
    PAGE_RES_KIND_0,
    PAGE_RES_KIND_1,
    PAGE_RES_KIND_2,
    PAGE_RES_KIND_3,
    PAGE_RES_KIND_4,
    PAGE_RES_KIND_5,
};

class Constant {
public:
    static const char* LytResPathMain();
    static const char* LytResPathPage(PageResKind kind);
};

}  // namespace pause

#endif
