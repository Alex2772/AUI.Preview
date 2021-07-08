//
// Created by alex2772 on 7/8/21.
//

#pragma once


#include <AUI/View/ATextField.h>

class StyleTextField: public ATextField {
public:
    int getContentMinimumWidth() override;

protected:
    void typeableErase(size_t begin, size_t end) override;
    void typeableInsert(size_t at, const AString& toInsert) override;

    void typeableInsert(size_t at, wchar_t toInsert) override;

public:
    void setText(const AString& t) override;
};

