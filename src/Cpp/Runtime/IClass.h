//
// Created by alex2 on 6/28/2021.
//

#pragma once

#include <AUI/Common/AMap.h>
#include "Callable.h"
#include "IType.h"

namespace Runtime {

    /**
     * Represents a class
     */
    class IClass: public IType {
    private:
        AMap<AString, Callable> mMemberFunctions;

    public:
        bool isClass() override;
        IClass* asClass() override;

        const Callable& getFunction(const AString& name) {
            return mMemberFunctions.at(name);
        }

        void registerFunction(const AString& name, const Callable& callable) {
            mMemberFunctions[name] = callable;
        }
    };
}