//
// Created by alex2 on 6/11/2021.
//


#include <AUI/ASS/ASS.h>
#include <AUI/View/AListView.h>
#include <View/StyleTextField.h>

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
                c(".declaration_name"),
                TextColor {0xff0000_rgb },
            },
            {
                c(".declaration_br"),
                Opacity { 0.5f }
            },
            {
                c(".declaration_entry"),
                Margin{{}, {}, {}, 10_dp},
            },
            {
                c("side_panel") >> t<AListView>(),
                MinSize { {}, 200_dp },
            },
            {
                t<StyleTextField>(),
                Border { nullptr },
                BorderRadius { 0 },
                Margin { 1_dp },
                Expanding { 0 },
                MinSize { 5_dp, {} },
                Padding { 0, 2_dp },
            },
            {
                t<StyleTextField>::active(),
                BoxShadow { 0, 2_dp, 5_dp, 0x909090_rgb, },
            },
        });
    }
} style1212489214912894;