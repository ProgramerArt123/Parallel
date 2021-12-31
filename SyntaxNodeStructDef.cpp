#include "SyntaxNodeStructDef.h"
#include "common.h"

SyntaxNodeStructDef::SyntaxNodeStructDef(SyntaxNodeScope &outter,
	int line,
	const char *name):
	SyntaxNode(line, name), m_body(std::shared_ptr<SyntaxNodeScope>(new SyntaxNodeScope(outter, line, name))){
		m_type = SYNTAX_NODE_TYPE_STRUCT_DEF;
}

SyntaxNodeStructDef::~SyntaxNodeStructDef() {

}

std::shared_ptr<SyntaxNodeScope> &SyntaxNodeStructDef::GetBody() {
	return m_body;
}
