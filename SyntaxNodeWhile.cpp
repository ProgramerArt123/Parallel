#include "common.h"
#include "SyntaxNodeWhile.h"


SyntaxNodeWhile::SyntaxNodeWhile(SyntaxNodeScope &outter, int line, bool isDo):
	SyntaxNode(outter, line, "WHILE"),m_is_do(isDo),
	m_body(std::shared_ptr<SyntaxNodeScope>(new SyntaxNodeScope(outter, line))){
	m_type = SYNTAX_NODE_TYPE_WHILE;
}

SyntaxNodeWhile::~SyntaxNodeWhile() {

}

std::shared_ptr<SyntaxNodeScope> SyntaxNodeWhile::GetBody() {
	return m_body;
}

void SyntaxNodeWhile::GenerateCondtionSyntaxNode(const Lexical &condition) {
	std::vector<std::shared_ptr<SyntaxNode>> adapter;
	m_outer->GenerateSyntaxNode(condition, adapter);
	m_condition = adapter.front();
}
