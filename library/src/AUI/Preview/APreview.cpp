//
// Created by alex2772 on 7/11/21.
//

#include "APreview.h"

void APreview::registerFactory(const AVector<IFactory<AObject>*>& factories) {
    Autumn::get<FactoryRegistry<AObject>>()->registerFactory(factories);
}

_<FactoryRegistry<AObject>> APreview::getFactoryRegistry() {
    return Autumn::get<FactoryRegistry<AObject>>();
}
