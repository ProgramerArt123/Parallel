#ifndef __SYNTAX_NODE_WHILE_H__
#define __SYNTAX_NODE_WHILE_H__

#include "SyntaxNode.h"
#include "SyntaxNodeScope.h"

class SyntaxNodeWhile : public SyntaxNode {
public:
	explicit SyntaxNodeWhile(SyntaxNodeScope &outter, int line, bool ifsDo = false);
	virtual ~SyntaxNodeWhile();
	void GenerateCondtionSyntaxNode(const Lexical &condition);
	std::shared_ptr<SyntaxNodeScope> GetBody();
private:
	const bool m_is_do=false;
	std::shared_ptr<SyntaxNode> m_condition;
	std::shared_ptr<SyntaxNodeScope> m_body;
};


#endif