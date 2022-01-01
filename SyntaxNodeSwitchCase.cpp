#include "common.h"
#include "SyntaxNodeSwitchCase.h"


SyntaxNodeSwitchCase::SyntaxNodeSwitchCase(SyntaxNodeScope &outter, int line, bool isOutter)
	: SyntaxNode(outter, line, "SWITCH_CASE")
	, m_is_outter(isOutter),
	m_body(std::shared_ptr<SyntaxNodeScope>(new SyntaxNodeScope(outter, line))){
		m_type = SYNTAX_NODE_TYPE_SWITCH_CASE;
}

SyntaxNodeSwitchCase::~SyntaxNodeSwitchCase() {

}

std::shared_ptr<SyntaxNodeScope> SyntaxNodeSwitchCase::GetBody() {
	return m_body;
}

void SyntaxNodeSwitchCase::GenerateValueSyntaxNode(const Lexical &condition) {
	std::vector<std::shared_ptr<SyntaxNode>> adapter;
	m_outer->GenerateSyntaxNode(condition, adapter);
	m_value = adapter.front();
}
