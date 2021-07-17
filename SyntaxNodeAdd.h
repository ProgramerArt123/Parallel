#ifndef __SYNTAX_NODE_ADD_H__
#define __SYNTAX_NODE_ADD_H__

#include "SyntaxNode.h"

class SyntaxNodeAdd : public SyntaxNode {
public:
	explicit SyntaxNodeAdd();
	virtual ~SyntaxNodeAdd();

	void OutputSerial(std::stringstream& output) override;
	void OutputParallel(std::stringstream& output) override;
};


#endif