#ifndef _SCOPE_H_
#define _SCOPE_H_

#include <stack>
#include <memory>
#include <map>
#include "SyntaxTree.h"

class SyntaxNodeVariable ;
class SyntaxNodeProcDef;
class SyntaxNodeProcCall;
class SyntaxNodeLoop;
class SyntaxNodeNumber;
class SyntaxNodeAssignment;

class Scope : public SyntaxTree {
public:
	explicit Scope();
	explicit Scope(Scope &outter);


	void PushAdd();
	void PushSub();
	void PushMul();
	void PushDiv();
	void PushMod();
	void PushBlock();
	void PushNumber(int number);
	void PushString(const char *itera);
	void PushVariable(const char *name);
	
	std::shared_ptr<Scope> &PushProcDefEnter(const char *name);
	void PushProcDefExit();

	void PushProcCallEnter(const char *name);
	void PushProcCallExit();

	void PushStatement();
	void PushAssignmentStatement(const char *variable);
	void PushReturn();

	std::shared_ptr<Scope> &PushLoopEnter();
	void PushLoopExit();

	void AddArgment(uint64_t argment);
	void AddParam(const char *param);
	void generate(const char *fileName) throw (std::exception);
	void DefGenerate(std::stringstream& output);
	uint32_t CallGenerate(std::stringstream& output, std::list<std::shared_ptr<SyntaxNode>> &argments);
	void LoopGenerate(std::stringstream& output);
	void UpdateRuntimePos(size_t pos);

	void FindEffectives();
	void GenerateParallel() throw (std::exception);
	std::shared_ptr<SyntaxNodeAssignment> GetLastAssign(const char *name, int line, bool findedVariable = false);
protected:
	bool IsProcExist(const char *name);
	bool IsVariableExist(const char *name);
	size_t StatisticsAssginsCount();

	size_t GetNewVariablePos();
protected:
	std::stack<std::shared_ptr<SyntaxNode>> m_stack;
	std::map<std::string, std::shared_ptr<SyntaxNodeProcDef>> m_procs;
	std::map<std::string, std::shared_ptr<SyntaxNodeVariable>> m_vars;
	std::vector<std::shared_ptr<SyntaxNodeVariable>> m_parameters;
	std::vector<std::shared_ptr<SyntaxNodeNumber>> m_argments;
	std::shared_ptr<SyntaxNodeProcCall> m_proc_call;
	size_t m_runtime_pos = 0;

	std::set<std::shared_ptr<SyntaxNode>> m_effectives;

};

#endif