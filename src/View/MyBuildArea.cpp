//
// Created by alex2 on 6/25/2021.
//

#include "MyBuildArea.h"
#include <AUI/ASS/ASS.h>
#include <AUI/Util/UIBuildingHelpers.h>

using namespace ass;

MyBuildArea::MyBuildArea(const _<AView>& wrappedView):
        ARulerArea(wrappedView)
{
}
