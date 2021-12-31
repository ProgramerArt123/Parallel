#ifndef _SYNTAX_NODE_SCOPE_H_
#define _SYNTAX_NODE_SCOPE_H_

#include <stack>
#include <memory>
#include <map>
#include "SyntaxNode.h"
#include "Parallel.h"
#include "DataTypeType.h"
class SyntaxNodeEnum;
class SyntaxNodeVariable ;
class SyntaxNodeProcDef;
class SyntaxNodeProcCall;
class SyntaxNodeLoop;
class SyntaxNodeNumber;
class SyntaxNodeAssignment;
class DataType;
class Lexical;

class SyntaxNodeScope : public SyntaxNode {
public:
	explicit SyntaxNodeScope(int line, const char *content = "");
	explicit SyntaxNodeScope(SyntaxNodeScope &outter, int line, const SyntaxNodeProcDef *proc, const char *content = "");
	void PushAddAssign(const char *variable);
	void PushAdd();
	void PushSub();
	void PushMul();
	void PushDiv();
	void PushMod();
	void PushInc(const char *variable, bool isBack);
	void PushBlock();
	void PushNumber(int number);
	void PushString(const char *itera);
	void PushVariable(const char *name);
	
	std::shared_ptr<SyntaxNodeScope> &PushProcCallEnter(const char *name);
	void PushProcCallExit();

	void PushStatement();
	void PushAssignmentStatement();
	void PushInitStatement();
	void DefineVariable(const Lexical &lexical);
	const std::shared_ptr<SyntaxNodeScope> &DefineProc(const Lexical &lexical);
	void DefineEnum(const Lexical &lexical);
	void PushReturn();

	std::shared_ptr<SyntaxNodeScope> &PushLoopEnter();
	void PushLoopExit();

	void AddArgment(uint64_t argment);
	void AddParam(const char *param);
	
	void PushType(const char *type, bool isConst);

	void OutputFile(std::unique_ptr<Output>& output) throw (std::exception);

	void OutputInstructions(std::unique_ptr<Output>& output) override;

	void DefGenerate(std::unique_ptr<Output>& output);
	void LoopGenerate(std::unique_ptr<Output>& output);
	
	void FindEffectives();
	void GenerateParallel() throw (std::exception);

	void FindEffectives(std::set<std::shared_ptr<SyntaxNode>> &effectives);
	void GenerateParallel(std::set<std::shared_ptr<SyntaxNode>> &effectives) throw (std::exception);

	std::shared_ptr<SyntaxNodeAssignment> GetLastAssign(const char *name, int line, bool findedVariable = false);
	
	size_t PushRegister(const char *reg);
	size_t PopRegister(std::string &reg);

	size_t PushArgument();
	void PopArgument();
	
	size_t PushCache();
	void PopCache();
	
	const size_t GetScopeStackTopOffset() const;
	
	const size_t GetSubProcOffset() const;
	
	const SyntaxNodeProcDef *GetProcDef() const;
	
	bool CheckDataType(DATA_TYPE_TYPE type, const std::shared_ptr<SyntaxNode> &node);
protected:
	bool IsProcExist(const char *name);
	bool IsVariableParamExistInner(const char *name)const;
	bool IsVariableExistInner(const char *name)const;
	bool IsParamExistInner(const char *name)const;
	bool IsVariableParamExist(const char *name)const;
	bool IsVariableExist(const char *name) const;
	bool IsParamExist(const char *name)const;
	bool IsEnumExistInner(const char *name)const;
	std::shared_ptr<SyntaxNodeVariable> GetVariableParam(const char *name);
	size_t StatisticsAssginsCount();
	
	
protected:
	std::stack<std::shared_ptr<SyntaxNode>> m_stack;
	std::map<std::string, std::shared_ptr<SyntaxNodeProcDef>> m_procs;
	std::map<std::string, std::shared_ptr<SyntaxNodeVariable>> m_variables;
	std::vector<std::shared_ptr<SyntaxNodeVariable>> m_parameters;
	std::vector<std::shared_ptr<SyntaxNodeNumber>> m_argments;
	std::map<std::string, std::shared_ptr<SyntaxNodeEnum>> m_enums;
	const size_t m_base_pos = 0;

	std::set<std::shared_ptr<SyntaxNode>> m_effectives;
	Parallel m_parallel;

protected:
	friend class SerialOutput;
	friend class ParallelOutput;

private:
	const size_t GetParameterStackTopOffset(size_t index) const;

	const size_t GetCurrentPos() const;

	const DATA_TYPE_TYPE GetProcRetType()const;
	
	std::stack<std::string> m_registers;
	std::stack<std::string> m_arguments;
	std::stack<std::string> m_caches;
	
	
	const SyntaxNodeProcDef *m_proc = NULL;
};

#endif