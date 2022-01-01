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
#include "SyntaxNodeInc.h"
#include "SyntaxNodeProcDef.h"
#include "SyntaxNodeProcCall.h"
#include "SyntaxNodeAssignment.h"
#include "SyntaxNodeVariable.h"
#include "SyntaxNodeReturn.h"
#include "SyntaxNodeFor.h"
#include "SyntaxNodeWhile.h"
#include "SyntaxNodeIfElse.h"
#include "SyntaxNodeScope.h"
#include "SourceCodeFile.h"
#include "DataType.h"
#include "DataTypeInt.h"
#include "DataTypeDouble.h"
#include "DataTypeVoid.h"
#include "SyntaxNodeEnumDef.h"
#include "SyntaxNodeStructDef.h"
#include "SyntaxNodeUnionDef.h"
#include "SyntaxNodeProcDefScope.h"
#include "GCC_X86_64.h"
#include "CLANG_X86_64.h"
extern std::unique_ptr<SourceCodeFile> source;

#define PLATFORM CLANG_X86_64::GetInstance()

#endif