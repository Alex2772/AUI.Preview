//
// Created by alex2 on 6/28/2021.
//

#include <Model/Project.h>
#include <AUI/Autumn/Autumn.h>
#include "ConversionHelper.h"

AString ConversionHelper::remapUrl(const AString& str) {
    if (str.startsWith(':')) {
        // url; replace it
        auto projectRoot = Autumn::get<Project>()->getRoot();
        return "file://"_as + projectRoot["assets"][AString(str.begin() + 1, str.end())];
    }
    return str;
}
