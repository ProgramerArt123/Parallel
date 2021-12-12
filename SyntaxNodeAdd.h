#ifndef __SYNTAX_NODE_ADD_H__
#define __SYNTAX_NODE_ADD_H__

#include "SyntaxNodeCompute.h"

class SyntaxNodeAdd : public SyntaxNodeCompute {
public:
	explicit SyntaxNodeAdd();
	virtual ~SyntaxNodeAdd();

	GENERATE_PARALLEL_RESULT GenerateParallel(const std::shared_ptr<SyntaxNode> &self, Parallel &parallel) throw (std::exception) override;

	void OutputInstructions(std::unique_ptr<Output>& output) override;


};


#endif