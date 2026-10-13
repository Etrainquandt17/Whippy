#ifndef MINTVM_TMPSYMBOL_H
#define MINTVM_TMPSYMBOL_H

#include "mintvm/MintAssert.h"
#include "mintvm/stdc.h"

namespace mintvm {

class TmpSymbol {
public:
    enum {
        BUFFER_SIZE = 0x100,
    };

    TmpSymbol(const char* a) {
        strcpy(mBuffer, "");
        add(a);
    }

    TmpSymbol(const char* a, const char* b) {
        strcpy(mBuffer, "");
        add(a);
        add(b);
    }

    TmpSymbol(const char* a, const char* b, const char* c) {
        strcpy(mBuffer, "");
        add(a);
        add(b);
        add(c);
    }

    TmpSymbol(const char* a, const char* b, const char* c, const char* d) {
        strcpy(mBuffer, "");
        add(a);
        add(b);
        add(c);
        add(d);
    }

    ~TmpSymbol() {}

    void add(const char* text) {
        MINT_ASSERT("TmpSymbol.hpp", 65, strlen(mBuffer) + strlen(text) < BUFFER_SIZE);
        strcat(mBuffer, text);
    }

    char* divide(int index) {
        MINT_ASSERT("TmpSymbol.hpp", 99, index < BUFFER_SIZE - 1);
        char* p = mBuffer + index;
        *p = '\0';
        return p + 1;
    }

    static int find(const char* text, char c) {
        for (const char* p = text; *p != '\0'; p++) {
            if (*p == c) {
                return p - text;
            }
        }
        return -1;
    }

    int find(char c) const {
        return find(mBuffer, c);
    }

    const char* c_str() const {
        return mBuffer;
    }

    int rfind(char c) const {
        int index = -1;
        for (const char* p = mBuffer; *p != '\0'; p++) {
            if (*p == c) {
                index = p - mBuffer;
            }
        }
        return index;
    }

    char* buffer() {
        return mBuffer;
    }

private:
    char mBuffer[BUFFER_SIZE];
};

}  // namespace mintvm

#endif
