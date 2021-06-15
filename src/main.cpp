//
// Created by alex2 on 6/11/2021.
//

#include <AUI/Platform/Entry.h>
#include <Window/MainWindow.h>
#include "Settings.h"
#include <Factory/FactoryRegistry.h>
#include <Factory/MyFactory.h>
#include <AUI/View/AButton.h>

AUI_ENTRY {
    Autumn::put(_new<FactoryRegistry>());

    Autumn::get<FactoryRegistry>()->registerFactory({
        new factory<AView>,

        new factory<ASpacer>,

        new factory<AButton>,
        new factory<AButton>::with_args<AString>,

        new factory<ALabel>,
        new factory<ALabel>::with_args<AString>
    });

    Settings::inst();
    _new<MainWindow>()->show();
    return 0;
};