//
// Created by alex2 on 6/28/2021.
//

#pragma once

namespace Runtime {

    class IClass;

    class IType {
    public:
        virtual bool isClass() { return false; }
        virtual IClass* asClass() = 0;

        virtual bool isFundamental() { return false; }
    };
}