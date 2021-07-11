//
// Created by alex2 on 6/11/2021.
//

#include <AUI/Platform/Entry.h>
#include <Window/MainWindow.h>
#include "Settings.h"
#include <AUI/Preview/APreview.h>

AUI_ENTRY {
    Autumn::put(APreview::getFactoryRegistry());
    Settings::inst();
    Autumn::put(_new<MainWindow>())->show();
    return 0;
};

