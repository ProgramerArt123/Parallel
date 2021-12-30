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
#include "SyntaxNodeLoop.h"
#include "SyntaxNodeScope.h"
#include "SourceCodeFile.h"
#include "DataType.h"
#include "DataTypeInt.h"
#include "DataTypeVoid.h"
#include "GCC_X86_64.h"
#include "CLANG_X86_64.h"
extern std::unique_ptr<SourceCodeFile> source;
extern int yyget_lineno(void);
extern char *yyget_text(void);
std::string error_info(std::string info);

#define PLATFORM CLANG_X86_64::GetInstance()

#endif