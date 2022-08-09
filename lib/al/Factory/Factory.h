#pragma once

#include "al/System/ByamlIter.h"

namespace al {

template <typename Creator>
struct NameToCreator {
    const char* name;
    Creator creator;
};

template <typename T>
class Factory {
public:
    inline Factory(const char* factoryName)
        : mName(factoryName)
        , mEntries(nullptr)
        , mEntryAmount(0)
    {
    }

    template <int N>
    inline Factory(const char* factoryName, al::NameToCreator<T> (&entries)[N])
        : mName(factoryName)
    {
        initFactory(entries);
    }

    template <int N>
    inline void initFactory(al::NameToCreator<T> (&entries)[N])
    {
        mEntries = entries;
        mEntryAmount = N;
    }

    virtual const char* convertName(const char* name) const { return name; }

protected:
    const char* mName = nullptr;
    const al::NameToCreator<T>* mEntries = nullptr;
    int mEntryAmount = 0;
    ByamlIter mConvertNameData;
};

} // namespace al