#ifndef _SYNTAX_NODE_PROC_DEF_SCOPE_H_
#define _SYNTAX_NODE_PROC_DEF_SCOPE_H_

#include "SyntaxNodeScope.h"
class SyntaxNodeProcDefScope : public SyntaxNodeScope {
public:
	explicit SyntaxNodeProcDefScope(SyntaxNodeScope &outter, int line, 
		const SyntaxNodeProcDef &proc, const char *content);
	virtual ~SyntaxNodeProcDefScope() {}
	void AddParam(const char *param);
	void DefGenerate(std::unique_ptr<Output>& output);
	
	const SyntaxNodeProcDef &GetProcDef() const;
	
protected:
	const size_t GetParameterStackTopOffset(size_t index) const;
	const size_t GetCurrentPos() const override;
	std::shared_ptr<SyntaxNodeVariable> GetVariable(const char *name)override;
	virtual bool IsVariableExist(const char *name) const override;
	bool IsParamExistInner(const char *name)const;
	bool IsVariableExistInner(const char *name)const override;
	bool IsParamExist(const char *name)const;

	const DATA_TYPE_TYPE GetProcRetType()const;
	
	std::vector<std::shared_ptr<SyntaxNodeVariable>> m_parameters;
	const SyntaxNodeProcDef &m_proc;
};

#endif