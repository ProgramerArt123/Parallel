#ifndef __SYNTAX_NODE_STRUCT_DEF_H__
#define __SYNTAX_NODE_STRUCT_DEF_H__

#include "SyntaxNode.h"
#include "SyntaxNodeScope.h"

class SyntaxNodeStructDef : public SyntaxNode {
public:
	explicit SyntaxNodeStructDef(SyntaxNodeScope &outter,
		int line,
		const char *name);
	virtual ~SyntaxNodeStructDef();
	
	std::shared_ptr<SyntaxNodeScope> &GetBody();
	
private:
	std::shared_ptr<SyntaxNodeScope> m_body;
};

#endif