#ifndef __SYNTAX_NODE_IF_ELSE_H__
#define __SYNTAX_NODE_IF_ELSE_H__

#include "SyntaxNode.h"
#include "SyntaxNodeScope.h"

class SyntaxNodeIfElse : public SyntaxNode {
public:
	explicit SyntaxNodeIfElse(SyntaxNodeScope &outter, int line);
	virtual ~SyntaxNodeIfElse();
	void GenerateCondtionSyntaxNode(const Lexical &condition);
	std::shared_ptr<SyntaxNodeScope> GetBody();
private:
	std::shared_ptr<SyntaxNode> m_condition;
	std::shared_ptr<SyntaxNodeScope> m_body;
};


#endif