//
// Created by alex2772 on 7/11/21.
//


#include <AUI/View/AListView.h>
#include "AUI/api.h"

#include "APreview.h"

struct Entry {
    Entry() {
        using namespace ass;
        using dimension = unset_wrap<AMetric>;

        Autumn::put(_new<FactoryRegistry<AObject>>());
        Autumn::get<FactoryRegistry<AObject>>()->registerFactory({
            // VIEWS =======================================================================================================
            new object_factory<AView>,
            new object_factory<ASpacer>,
            new object_factory<AButton>,
            new object_factory<AButton>::with_args<AString>,
            new object_factory<AHDividerView>,
            new object_factory<AVDividerView>,
            new object_factory<APageView>,
            new object_factory<ALabel>,
            new object_factory<ALabel>::with_args<AString>,
            new object_factory<ASelectableLabel>,
            new object_factory<ASelectableLabel>::with_args<AString>,
            new object_factory<AImageView>::with_args<_<AImage>>,
            new object_factory<ATabView>,
            new object_factory<ATabButtonView>,
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

             // BackgroundGradient
             new rule_factory<BackgroundGradient>::with_args<std::nullptr_t>,

             // BackgroundImage
             new rule_factory<BackgroundImage>::with_args<AString>,
             new rule_factory<BackgroundImage>::with_args<unset_wrap<AString>, unset_wrap<AColor>>,
             new rule_factory<BackgroundImage>::with_args<unset_wrap<AString>, unset_wrap<AColor>, unset_wrap<Repeat>>,
             new rule_factory<BackgroundImage>::with_args<unset_wrap<AString>, unset_wrap<AColor>, unset_wrap<Repeat>, unset_wrap<Sizing>>,
             new rule_factory<BackgroundImage>::with_args<unset_wrap<AString>, unset_wrap<AColor>, unset_wrap<Repeat>, unset_wrap<Sizing>, unset_wrap<glm::vec2>>,

             // BackgroundSolid
             new rule_factory<BackgroundSolid>::with_args<AColor>,
             new rule_factory<BackgroundSolid>::with_args<std::nullptr_t>,
             new rule_factory<BackgroundGradient>::with_args<AColor, AColor, LayoutDirection>,

             // Border
             new rule_factory<Border>::with_args<std::nullptr_t>,
             new rule_factory<Border>::with_args<AMetric, AColor>,

             // BorderRadius
             new rule_factory<BorderRadius>::with_args<AMetric>,

             // BorderBottom
             new rule_factory<BorderBottom>::with_args<AMetric, AColor>,

             // BoxShadow
             new rule_factory<BoxShadow>::with_args<AMetric,AMetric,AMetric, AMetric, AColor>,
             new rule_factory<BoxShadow>::with_args<AMetric,AMetric,AMetric, AColor>,
             new rule_factory<BoxShadow>::with_args<std::nullptr_t>,

             // Expanding
             new rule_factory<Expanding>::with_args<bool>,
             new rule_factory<Expanding>::with_args<unset_wrap<int>>,
             new rule_factory<Expanding>::with_args<unset_wrap<int>, unset_wrap<int>>,

             // FixedSize
             new rule_factory<FixedSize>::with_args<dimension, dimension>,
             new rule_factory<FixedSize>::with_args<AMetric>,

             // FontFamily
             new rule_factory<FontFamily>::with_args<AString>,

             // FontRendering
             new rule_factory<FontRendering>::with_args<FontRendering>,

             // FontSize
             new rule_factory<FontSize>::with_args<AMetric>,

             // ImageRendering
             new rule_factory<ImageRendering>::with_args<ImageRendering>,

             // LayoutSpacing
             new rule_factory<LayoutSpacing>::with_args<AMetric>,

             // Margin
             new rule_factory<Margin>::with_args<dimension>,
             new rule_factory<Margin>::with_args<dimension, dimension>,
             new rule_factory<Margin>::with_args<dimension, dimension, dimension>,
             new rule_factory<Margin>::with_args<dimension, dimension, dimension, dimension>,

             // MaxSize
             new rule_factory<MaxSize>::with_args<dimension, dimension>,
             new rule_factory<MaxSize>::with_args<AMetric>,

             // MinSize
             new rule_factory<MinSize>::with_args<dimension, dimension>,
             new rule_factory<MinSize>::with_args<AMetric>,

             // Opacity TODO

             // LayoutSpacing
             new rule_factory<Overflow>::with_args<Overflow>,

             // Padding
             new rule_factory<Padding>::with_args<dimension>,
             new rule_factory<Padding>::with_args<dimension, dimension>,
             new rule_factory<Padding>::with_args<dimension, dimension, dimension>,
             new rule_factory<Padding>::with_args<dimension, dimension, dimension, dimension>,

             // TextColor
             new rule_factory<TextAlign>::with_args<TextAlign>,

             // TextColor
             new rule_factory<TextColor>::with_args<AColor>,
     });
    }
} entry;