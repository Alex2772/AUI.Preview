//
// Created by alex2 on 6/15/2021.
//

#include "FactoryRegistry.h"

void FactoryRegistry::registerFactory(IFactory* factory) {
    auto typeName = factory->getTypeName();
    mFactories[typeName] << _unique<IFactory>(factory);
}
