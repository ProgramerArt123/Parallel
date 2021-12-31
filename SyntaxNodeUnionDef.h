#ifndef __SYNTAX_NODE_UNION_DEF_H__
#define __SYNTAX_NODE_UNION_DEF_H__

#include "SyntaxNode.h"
#include "SyntaxNodeScope.h"

class SyntaxNodeUnionDef : public SyntaxNode {
public:
	explicit SyntaxNodeUnionDef(SyntaxNodeScope &outter,
		int line,
		const char *name);
	virtual ~SyntaxNodeUnionDef();
	
	std::shared_ptr<SyntaxNodeScope> &GetBody();
	
private:
	std::shared_ptr<SyntaxNodeScope> m_body;
};

#endif