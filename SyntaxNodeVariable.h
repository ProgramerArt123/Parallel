#ifndef _SYNTAX_NODE_VARIABLE_H_
#define _SYNTAX_NODE_VARIABLE_H_

#include <string>
#include "SyntaxNode.h"

class SyntaxNodeAssignment;
class SyntaxNodeProcCall;

class SyntaxNodeVariable : public SyntaxNode {
public:
	explicit SyntaxNodeVariable(SyntaxNode &scope, const char *name, size_t pos);
	virtual ~SyntaxNodeVariable();

	GENERATE_PARALLEL_RESULT GenerateParallel(const std::shared_ptr<SyntaxNode> &self, Parallel &parallel) throw (std::exception) override;

	void generate(std::stringstream& output) override;

	size_t GetScopePos();
private:
	std::shared_ptr<SyntaxNodeAssignment> GetLastAssign();
	
private:
	std::string m_name;
	size_t m_scope_pos = 0;
};

#endif