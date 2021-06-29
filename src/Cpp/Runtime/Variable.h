//
// Created by alex2 on 6/28/2021.
//

#pragma once


#include <AUI/Common/AObject.h>
#include "IType.h"

namespace Runtime {
    class Variable {
    private:
        IType* mType;
        _<AObject> mValue;

    public:
        Variable(IType* type, const _<AObject>& value) : mType(type), mValue(value) {}

        [[nodiscard]] const _ <AObject>& getValue() const {
            return mValue;
        }

        [[nodiscard]] IType* getType() const {
            return mType;
        }

        operator bool() const {
            return mValue != nullptr;
        }
    };
}