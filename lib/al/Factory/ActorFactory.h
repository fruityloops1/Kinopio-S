#pragma once

#include "al/Factory/Factory.h"
#include "al/LiveActor/LiveActor.h"

namespace al {

class ActorFactory : Factory<al::LiveActor* (*)(const char*)> {
public:
    ActorFactory(const char* name);

    void setConvertNameData(const u8* data);
    void setConvertNameData(const ByamlIter& data);
    const char* convertName(const char* name) const override;
};

} // namespace al