//
// Created by alex2 on 6/17/2021.
//

#pragma once

#include <AUI/Layout/ALayout.h>
#include <AUI/Preview/Cpp/Runtime/Callable.h>

namespace Replicator {
    _<ALayout> layout(const AString& layoutName);
    void setCustomAss(AView* target, const Runtime::CallArgs& args);

    AString prettyName(AView* view);
}


