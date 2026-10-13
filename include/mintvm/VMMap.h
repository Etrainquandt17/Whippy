#ifndef MINTVM_VMMAP_H
#define MINTVM_VMMAP_H

#include "mintvm/STLAllocator.h"
#include "mintvm/VMKey.h"
#include "mintvm/VMObject.h"
#include "std/map.h"

namespace mintvm {

template <class T, T Invalid>
class VMMap : public VMObject {
    typedef std::map<VMKey, T, std::less<VMKey>, STLAllocator<std::pair<VMKey, T> > > Map;

public:
    VMMap() {}

    void add(const VMKey& key, T value) {
        mMap.insert(std::pair<VMKey, T>(key, value));
    }

    T find(const VMKey& key) const {
        // The game looks the key up twice and drops the first result.
        mMap.find(key);
        typename Map::const_iterator it = mMap.find(key);
        if (it != mMap.end()) {
            return it->second;
        }
        return Invalid;
    }

private:
    Map mMap;
};

template <class T>
class VMMapPtr : public VMObject {
    typedef std::map<VMKey, T*, std::less<VMKey>, STLAllocator<std::pair<VMKey, T*> > > Map;

public:
    VMMapPtr() {}

    void add(const VMKey& key, T* value) {
        mMap.insert(std::pair<VMKey, T*>(key, value));
    }

    T* find(const VMKey& key) const {
        // The game looks the key up twice and drops the first result.
        mMap.find(key);
        typename Map::const_iterator it = mMap.find(key);
        if (it != mMap.end()) {
            return it->second;
        }
        return 0;
    }

private:
    Map mMap;
};

}

#endif
