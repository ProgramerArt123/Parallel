#ifndef _SYNTAX_NODE_VARIABLE_H_
#define _SYNTAX_NODE_VARIABLE_H_

#include <string>
#include "SyntaxNode.h"

class SyntaxNodeAssignment;
class SyntaxNodeProcCall;
class DataType;

class SyntaxNodeVariable : public SyntaxNode {
public:
	explicit SyntaxNodeVariable(SyntaxNodeScope &scope, const char *name,
		std::shared_ptr<DataType> dataType, bool isConst, size_t pos);
	virtual ~SyntaxNodeVariable();

	GENERATE_PARALLEL_RESULT GenerateParallel(const std::shared_ptr<SyntaxNode> &self, Parallel &parallel) throw (std::exception) override;

	void OutputInstructions(std::unique_ptr<Output>& output) override;

	const size_t GetScopeStackTopOffset()const;
	
	bool IsConst() const;
private:
	std::shared_ptr<SyntaxNodeAssignment> GetLastAssign();

	const size_t GetScopePos()const;
private:
	std::string m_name;
	const size_t m_scope_pos = 0;
	const std::shared_ptr<DataType> m_data_type;
	const bool m_is_const = false;

};

#endif