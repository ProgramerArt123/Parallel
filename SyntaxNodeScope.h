#ifndef _SYNTAX_NODE_SCOPE_H_
#define _SYNTAX_NODE_SCOPE_H_

#include <stack>
#include <memory>
#include <map>
#include "SyntaxNode.h"
#include "Parallel.h"

class SyntaxNodeVariable ;
class SyntaxNodeProcDef;
class SyntaxNodeProcCall;
class SyntaxNodeLoop;
class SyntaxNodeNumber;
class SyntaxNodeAssignment;

class SyntaxNodeScope : public SyntaxNode {
public:
	explicit SyntaxNodeScope(const char *content = "");
	explicit SyntaxNodeScope(SyntaxNodeScope &outter, const char *content = "");

	void PushAdd();
	void PushSub();
	void PushMul();
	void PushDiv();
	void PushMod();
	void PushBlock();
	void PushNumber(int number);
	void PushString(const char *itera);
	void PushVariable(const char *name);
	
	std::shared_ptr<SyntaxNodeScope> &PushProcDefEnter(const char *name);
	void PushProcDefExit();

	void PushProcCallEnter(const char *name);
	void PushProcCallExit();

	void PushStatement();
	void PushAssignmentStatement(const char *variable);
	void PushReturn();

	std::shared_ptr<SyntaxNodeScope> &PushLoopEnter();
	void PushLoopExit();

	void AddArgment(uint64_t argment);
	void AddParam(const char *param);

	void OutputFile(std::unique_ptr<Output>& output) throw (std::exception);

	void OutputInstructions(std::unique_ptr<Output>& output) override;

	void DefGenerate(std::unique_ptr<Output>& output);
	void BeginCallGenerate(std::unique_ptr<Output>& output, std::list<std::shared_ptr<SyntaxNode>> &argments);
	void EndCallGenerate(std::stringstream& output, std::list<std::shared_ptr<SyntaxNode>> &argments);
	void LoopGenerate(std::unique_ptr<Output>& output);
	//void UpdateRuntimePos(size_t pos);

	void FindEffectives();
	void GenerateParallel() throw (std::exception);

	void FindEffectives(std::set<std::shared_ptr<SyntaxNode>> &effectives);
	void GenerateParallel(std::set<std::shared_ptr<SyntaxNode>> &effectives) throw (std::exception);

	std::shared_ptr<SyntaxNodeAssignment> GetLastAssign(const char *name, int line, bool findedVariable = false);
	
	size_t PushRegister(const char *reg);
	size_t PopRegister(std::string &reg);

	size_t PushArgument();
	void PopArgument();
	
	const size_t GetScopeStackTopOffset() const;
protected:
	bool IsProcExist(const char *name);
	bool IsVariableExist(const char *name);
	size_t StatisticsAssginsCount();

	//size_t GetNewVariablePos();

protected:
	std::stack<std::shared_ptr<SyntaxNode>> m_stack;
	std::map<std::string, std::shared_ptr<SyntaxNodeProcDef>> m_procs;
	std::map<std::string, std::shared_ptr<SyntaxNodeVariable>> m_vars;
	std::vector<std::shared_ptr<SyntaxNodeVariable>> m_parameters;
	std::vector<std::shared_ptr<SyntaxNodeNumber>> m_argments;
	std::shared_ptr<SyntaxNodeProcCall> m_proc_call;
	const size_t m_base_pos = 0;

	std::set<std::shared_ptr<SyntaxNode>> m_effectives;
	Parallel m_parallel;

protected:
	friend class SerialOutput;
	friend class ParallelOutput;

private:
	const size_t GetParameterStackTopOffset(size_t index) const;

	const size_t GetCurrentPos() const;

	const size_t GetSubProcOffset() const;

	std::stack<std::string> m_registers;
	std::stack<std::string> m_arguments;
};

#endif