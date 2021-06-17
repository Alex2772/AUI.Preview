//
// Created by alex2 on 6/11/2021.
//

#include <AUI/Platform/Entry.h>
#include <Window/MainWindow.h>
#include "Settings.h"
#include <Factory/FactoryRegistry.h>
#include <Factory/factory.h>
#include <Factory/factory_lambda.h>
#include <AUI/View/AButton.h>
#include <AUI/Model/AListModelAdapter.h>
#include <AUI/Model/AListModel.h>
#include <AUI/Util/UIBuildingHelpers.h>

AUI_ENTRY {
    Autumn::put(_new<FactoryRegistry>());

    Autumn::get<FactoryRegistry>()->registerFactory({
        // VIEWS =======================================================================================================
        new factory<AView>,

        new factory<ASpacer>,

        new factory<AButton>,
        new factory<AButton>::with_args<AString>,

        new factory<ALabel>,
        new factory<ALabel>::with_args<AString>,

        new factory_lambda( [] {
            _<AListModel<AString>> exampleModel = _new<AListModel<AString>>({
              "Example data #1",
              "Example data #2",
              "Example data #3",
              "Example data #4",
            });
            return _new<AListView>(AAdapter::make<AString>(exampleModel, [](const AString& s){ return s;}));
        }),

        // LAYOUTS =====================================================================================================
        new factory<AHorizontalLayout>,
        new factory<AVerticalLayout>,
        new factory<AStackedLayout>,
    });

    Settings::inst();
    _new<MainWindow>()->show();
    return 0;
};