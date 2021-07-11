//
// Created by alex2772 on 7/11/21.
//

#pragma once

#include "AUI/Preview/Converter/all.h"
#include <AUI/View/AButton.h>
#include <AUI/Model/AListModelAdapter.h>
#include <AUI/Model/AListModel.h>
#include <AUI/Util/UIBuildingHelpers.h>
#include <AUI/ASS/ASS.h>
#include <AUI/View/AImageView.h>
#include <AUI/View/AHDividerView.h>
#include <AUI/View/AVDividerView.h>
#include <AUI/View/ASelectableLabel.h>
#include <AUI/View/APageView.h>
#include <AUI/View/ATabView.h>
#include "Factory/FactoryRegistry.h"
#include "Factory/rule_factory.h"
#include "Factory/lambda_factory.h"

namespace APreview {
    API_AUI_PREVIEW_LIBRARY void registerFactory(const AVector<IFactory<AObject>*>& factories);
    API_AUI_PREVIEW_LIBRARY _<FactoryRegistry<AObject>> getFactoryRegistry();
};

