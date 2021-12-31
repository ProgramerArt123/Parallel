#include "common.h"
#include "SyntaxNodeUnionDef.h"

SyntaxNodeUnionDef::SyntaxNodeUnionDef(SyntaxNodeScope &outter,
	int line,
	const char *name):
	SyntaxNode(line, name), m_body(std::shared_ptr<SyntaxNodeScope>(new SyntaxNodeScope(outter, line, name))){
		m_type = SYNTAX_NODE_TYPE_UNION_DEF;
}

SyntaxNodeUnionDef::~SyntaxNodeUnionDef() {

}

std::shared_ptr<SyntaxNodeScope> &SyntaxNodeUnionDef::GetBody() {
	return m_body;
}
