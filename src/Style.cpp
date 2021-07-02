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
                c(".side_panel"),
                BackgroundSolid {0xffffff_rgb },
                FixedSize { 300_dp, {} },
            },
            {
                c("side_panel") >> t<AListView>(),
                MinSize { {}, 200_dp },
            }
        });
    }
} style1212489214912894;