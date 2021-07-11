//
// Created by alex2 on 6/17/2021.
//

#pragma once

#include <AUI/Layout/ALayout.h>
#include <AUI/Preview/Cpp/Runtime/Callable.h>

namespace Replicator {
    API_AUI_PREVIEW_LIBRARY _<ALayout> layout(const AString& layoutName);
    API_AUI_PREVIEW_LIBRARY void setCustomAss(AView* target, const Runtime::CallArgs& args);

    API_AUI_PREVIEW_LIBRARY AString prettyName(AView* view);
}


