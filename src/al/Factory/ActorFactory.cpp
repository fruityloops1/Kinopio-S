#include "al/Factory/ActorFactory.h"
#include "al/System/StringUtil.h"

namespace al {

ActorFactory::ActorFactory(const char* name)
    : Factory(name)
{
}

#ifdef NON_MATCHING
void ActorFactory::setConvertNameData(const u8* data)
{
    mConvertNameData = ByamlIter(data);
}

void ActorFactory::setConvertNameData(const ByamlIter& data)
{
    mConvertNameData = data;
}

const char* ActorFactory::convertName(const char* name) const
{
    const ByamlIter& iter = mConvertNameData;
    if (iter.isValid()) {
        int size = iter.getSize();
        if (size > 0)
            for (int i = 0; i < size; i++) {
                ByamlIter object;
                iter.tryGetIterByIndex(&object, i);
                const char* objectName = nullptr;
                if (object.tryGetStringByKey(&objectName, "ObjectName") && al::isEqualString(objectName, name)) {
                    const char* className = nullptr;
                    if (object.tryGetStringByKey(&className, "ClassName"))
                        return className;
                }
            }
    }
    return nullptr;
}
#endif

} // namespace al