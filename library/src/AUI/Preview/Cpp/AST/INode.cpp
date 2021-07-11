//
// Created by alex2 on 6/16/2021.
//

#include <AUI/Preview/Cpp/Parser.h>
#include <AUI/Autumn/Autumn.h>
#include "INode.h"

INode::INode(): mLineNumber(Autumn::get<Parser>()->getCurrentLineNumber()) {

}


