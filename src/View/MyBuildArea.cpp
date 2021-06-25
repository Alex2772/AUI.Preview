//
// Created by alex2 on 6/25/2021.
//

#include "MyBuildArea.h"
#include <AUI/ASS/ASS.h>
#include <AUI/Util/UIBuildingHelpers.h>
#include <AUI/View/ARulerView.h>
#include <AUI/View/AScrollbar.h>

using namespace ass;

MyBuildArea::MyBuildArea(const _<AView>& wrappedView) {
    setContents(_container<AAdvancedGridLayout>({
        _container<AAdvancedGridLayout>({
            _new<AView>(),
            _new<ARulerView>(LayoutDirection::HORIZONTAL),
            _new<ARulerView>(LayoutDirection::VERTICAL),
            Stacked {wrappedView} with_style { Expanding {2, 2} },
        }, 2, 2) with_style { Expanding {2, 2} },
            _new<AScrollbar>(),
            _new<AScrollbar>(LayoutDirection::HORIZONTAL),
        _new<AView>(),
    }, 2, 2));

    setCustomAss({Expanding {2, 2}});
}
