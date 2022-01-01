#include "common.h"
#include "SyntaxNodeIfElse.h"


SyntaxNodeIfElse::SyntaxNodeIfElse(SyntaxNodeScope &outter, int line):
	SyntaxNode(outter, line, "WHILE"),
	m_body(std::shared_ptr<SyntaxNodeScope>(new SyntaxNodeScope(outter, line))){
		m_type = SYNTAX_NODE_TYPE_IF_ELSE;
}

SyntaxNodeIfElse::~SyntaxNodeIfElse() {

}

std::shared_ptr<SyntaxNodeScope> SyntaxNodeIfElse::GetBody() {
	return m_body;
}

void SyntaxNodeIfElse::GenerateCondtionSyntaxNode(const Lexical &condition) {
	std::vector<std::shared_ptr<SyntaxNode>> adapter;
	m_outer->GenerateSyntaxNode(condition, adapter);
	m_condition = adapter.front();
}
