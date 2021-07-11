//
// Created by alex2 on 6/23/2021.
//

#pragma once

#include "converter.h"
#include <AUI/ASS/ASS.h>

namespace aui::preview {

    template<>
    struct converter<ass::unset_wrap<ass::Sizing>>: enum_converter<ass::Sizing> {};
}