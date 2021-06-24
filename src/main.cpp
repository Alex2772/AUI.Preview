//
// Created by alex2 on 6/11/2021.
//

#include <AUI/Platform/Entry.h>
#include <Window/MainWindow.h>
#include "Settings.h"
#include <Factory/FactoryRegistry.h>
#include <Factory/rule_factory.h>
#include <Factory/lambda_factory.h>
#include <Converter/all.h>
#include <AUI/View/AButton.h>
#include <AUI/Model/AListModelAdapter.h>
#include <AUI/Model/AListModel.h>
#include <AUI/Util/UIBuildingHelpers.h>
#include <AUI/ASS/ASS.h>

AUI_ENTRY {
    using namespace ass;
    using dimension = unset_wrap<AMetric>;

    Autumn::put(_new<FactoryRegistry<AObject>>());
    Autumn::get<FactoryRegistry<AObject>>()->registerFactory({
        // VIEWS =======================================================================================================
        new object_factory<AView>,

        new object_factory<ASpacer>,

        new object_factory<AButton>,
        new object_factory<AButton>::with_args<AString>,

        new object_factory<ALabel>,
        new object_factory<ALabel>::with_args<AString>,

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
        new object_factory<AHorizontalLayout>,
        new object_factory<AVerticalLayout>,
        new object_factory<AStackedLayout>,
    });

    Autumn::put(_new<FactoryRegistry<ass::decl::IDeclarationBase>>());

    Autumn::get<FactoryRegistry<ass::decl::IDeclarationBase>>()->registerFactory({
        // STYLESHEET RULES ============================================================================================

        // Expanding
        new rule_factory<Expanding>::with_args<bool>,

        // BackgroundImage
        new rule_factory<BackgroundImage>::with_args<AString>,
        new rule_factory<BackgroundImage>::with_args<unset_wrap<AString>, unset_wrap<AColor>>,
        new rule_factory<BackgroundImage>::with_args<unset_wrap<AString>, unset_wrap<AColor>, unset_wrap<Repeat>>,
        new rule_factory<BackgroundImage>::with_args<unset_wrap<AString>, unset_wrap<AColor>, unset_wrap<Repeat>, unset_wrap<Sizing>>,
        new rule_factory<BackgroundImage>::with_args<unset_wrap<AString>, unset_wrap<AColor>, unset_wrap<Repeat>, unset_wrap<Sizing>, unset_wrap<glm::vec2>>,

        new rule_factory<BackgroundSolid>::with_args<AColor>,

        // Padding
        new rule_factory<Padding>::with_args<dimension>,
        new rule_factory<Padding>::with_args<dimension, dimension>,
        new rule_factory<Padding>::with_args<dimension, dimension, dimension>,
        new rule_factory<Padding>::with_args<dimension, dimension, dimension, dimension>,

        // TextColor
        new rule_factory<TextColor>::with_args<AColor>,
    });

    Settings::inst();
    Autumn::put(_new<MainWindow>())->show();
    return 0;
};

