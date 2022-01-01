#ifndef __SYNTAX_NODE_SWITCH_CASE_H__
#define __SYNTAX_NODE_SWITCH_CASE_H__

#include "SyntaxNode.h"
#include "SyntaxNodeScope.h"

class SyntaxNodeSwitchCase : public SyntaxNode {
public:
	explicit SyntaxNodeSwitchCase(SyntaxNodeScope &outter, int line, bool isOutter = true);
	virtual ~SyntaxNodeSwitchCase();
	void GenerateValueSyntaxNode(const Lexical &condition);
	std::shared_ptr<SyntaxNodeScope> GetBody();
private:
	const bool m_is_outter=true;
	std::shared_ptr<SyntaxNode> m_value;
	std::shared_ptr<SyntaxNodeScope> m_body;
};


#endif