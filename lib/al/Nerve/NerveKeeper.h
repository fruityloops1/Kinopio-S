#pragma once

#include "al/Nerve/NerveStateCtrl.h"
#include <basis/seadTypes.h>

namespace al {

class Nerve;
class IUseNerve;
class NerveActionCtrl;
class NerveKeeper {
public:
    NerveKeeper(void*, const Nerve*, int);

    void update();
    void setNerve(const Nerve*);
    const Nerve* getCurrentNerve();
    void initNerveAction(al::NerveActionCtrl*);

    IUseNerve* mParent = nullptr;

private:
    const Nerve* mLastNerve = nullptr;
    const Nerve* mNerve = nullptr;
    s32 mStep = 0;
    s32 _1c;
    NerveStateCtrl* mNerveStateCtrl = nullptr;
    NerveActionCtrl* mNerveActionCtrl = nullptr;
};

class IUseNerve {
public:
    virtual NerveKeeper* getNerveKeeper() const = 0;
};

} // namespace al