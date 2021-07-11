#ifndef _SYNTAX_NODE_STRING_H_
#define _SYNTAX_NODE_STRING_H_

#include <string>
#include "SyntaxNode.h"

class SyntaxNodeString : public SyntaxNode {
public:
	explicit SyntaxNodeString(const char *litera);
	virtual ~SyntaxNodeString();

	GENERATE_PARALLEL_RESULT GenerateParallel(const std::shared_ptr<SyntaxNode> &self, Parallel &parallel) throw (std::exception) override {
		return GENERATE_PARALLEL_RESULT_COMPLETED;
	}

	int GetNO();

	void generate(std::stringstream& output) override;
private:
	int m_NO;
};

#endif