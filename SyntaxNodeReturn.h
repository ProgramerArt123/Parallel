#ifndef __SYNTAX_NODE_RETURN_H__
#define __SYNTAX_NODE_RETURN_H__

#include "SyntaxNode.h"

class SyntaxNodeReturn : public SyntaxNode {
public:
	explicit SyntaxNodeReturn();
	virtual ~SyntaxNodeReturn();

	void FindEffectives(std::shared_ptr<SyntaxNode> &self, std::set<std::shared_ptr<SyntaxNode>> &effectives) override;

	void OutputInstructions(std::unique_ptr<Output>& output) override;
};


#endif