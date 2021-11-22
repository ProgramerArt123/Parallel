#ifndef __COMMON_H__
#define __COMMON_H__

#include <stack>

#include "SyntaxNode.h"
#include "SyntaxNodeNumber.h"
#include "SyntaxNodeString.h"
#include "SyntaxNodeAdd.h"
#include "SyntaxNodeSub.h"
#include "SyntaxNodeMul.h"
#include "SyntaxNodeDiv.h"
#include "SyntaxNodeMod.h"
#include "SyntaxNodeProcDef.h"
#include "SyntaxNodeProcCall.h"
#include "SyntaxNodeAssignment.h"
#include "SyntaxNodeVariable.h"
#include "SyntaxNodeReturn.h"
#include "SyntaxNodeLoop.h"
#include "Scope.h"
#include "GCC_X86_64.h"
#include "CLANG_X86_64.h"

extern std::stack<std::shared_ptr<Scope>> scopes;

extern std::stringstream consts;

#define PLATFORM CLANG_X86_64::GetInstance()

#endif