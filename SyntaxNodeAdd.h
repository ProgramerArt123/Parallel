#ifndef __SYNTAX_NODE_ADD_H__
#define __SYNTAX_NODE_ADD_H__

#include "SyntaxNode.h"

class SyntaxNodeAdd : public SyntaxNode {
public:
	explicit SyntaxNodeAdd();
	virtual ~SyntaxNodeAdd();

	GENERATE_PARALLEL_RESULT GenerateParallel(const std::shared_ptr<SyntaxNode> &self, Parallel &parallel) throw (std::exception) override;

	void OutputSerial(std::stringstream& output) override;
	void OutputParallel(std::stringstream& output) override;

	int GetRightChildStackTop();

};


#endif