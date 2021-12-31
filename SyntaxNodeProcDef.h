#ifndef __SYNTAX_NODE_PROC_DEF_H__
#define __SYNTAX_NODE_PROC_DEF_H__

#include "SyntaxNode.h"
#include "SyntaxNodeScope.h"

class SyntaxNodeVariable;
class DataType;
class SyntaxNodeProcDefScope;

class SyntaxNodeProcDef : public SyntaxNode {
public:
	explicit SyntaxNodeProcDef(SyntaxNodeScope &outter,
		int line,
		const char *name, 
		std::shared_ptr<DataType> dataType);
	virtual ~SyntaxNodeProcDef();
	
	std::shared_ptr<SyntaxNodeProcDefScope> GetBody();
	
	void FindEffectives(std::shared_ptr<SyntaxNode> &self, std::set<std::shared_ptr<SyntaxNode>> &effectives) override;
	GENERATE_PARALLEL_RESULT GenerateParallel(const std::shared_ptr<SyntaxNode> &self, Parallel &parallel) throw (std::exception) override;

	void OutputInstructions(std::unique_ptr<Output>& output) override;
	friend std::ostream &operator<<(std::ostream &out, SyntaxNodeProcDef &def);
	
	DATA_TYPE_TYPE GetDataType()const;

private:
	void OutputHead(std::stringstream& output);
	void OutputTail(std::stringstream& output);
	unsigned int m_NO = 0;
private:
	std::shared_ptr<SyntaxNodeProcDefScope> m_body;
	const std::shared_ptr<DataType> m_data_type;
};

#endif