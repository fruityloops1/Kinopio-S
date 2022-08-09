#include "al/Nerve/NerveStateBase.h"

namespace al {

#ifdef NON_MATCHING
bool NerveStateBase::update()
{
    updateNerve();
    if (!mIsDead)
        control();
    return mIsDead;
}
#endif

} // namespace al