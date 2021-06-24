//
// Created by alex2 on 6/17/2021.
//

#include "Replicator.h"
#include <Factory/FactoryRegistry.h>
#include <AUI/Autumn/Autumn.h>

_<ALayout> Replicator::layout(const AString& layoutName) {
    return _cast<ALayout>(Autumn::get<FactoryRegistry<AObject>>()->create(layoutName, {}));
}
