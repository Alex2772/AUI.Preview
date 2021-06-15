//
// Created by alex2 on 6/11/2021.
//


#include <AUI/ASS/ASS.h>
#include <AUI/View/AListView.h>

using namespace ass;

class Style1212489214912894 {
public:
    Style1212489214912894() {
        AStylesheet::inst().addRules({
            {
                c(".build_area"),
                BoxShadow { 0, 4_dp, 17_dp, 0x40000000_argb },
                MinSize { 10_dp, 10_dp },
                BackgroundSolid { 0xf0f0f0_rgb },
            },
            {
                c(".side_panel"),
                BackgroundSolid {0xffffff_rgb },
                FixedSize { 200_dp, {} },
            },
            {
                c("side_panel") >> t<AListView>(),
                MinSize { {}, 200_dp },
            }
        });
    }
} style1212489214912894;