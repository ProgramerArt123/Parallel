#include <fstream>
#include <string.h>
#include "Scanner.h"
#include "common.h"
#include "SyntaxNodeScope.h"

SyntaxNodeScope::SyntaxNodeScope(int line, const char *content) :
	SyntaxNode(line, content),m_parallel(*this) {
	m_type = SYNTAX_NODE_TYPE_SCOPE;
}

SyntaxNodeScope::SyntaxNodeScope(SyntaxNodeScope &outter, int line, const char *content):
	SyntaxNode(outter, line, content),
	m_base_pos(outter.GetCurrentPos()),m_parallel(*this) {
	m_type = SYNTAX_NODE_TYPE_SCOPE;
}
void SyntaxNodeScope::PushAddAssign(const char *variable) {
//	if (!IsVariableParamExist(variable)) {
//		Error(std::string(variable) + " undefined");
//	}
	std::shared_ptr<SyntaxNode> assign(new SyntaxNodeAssignment(*this,0));
	std::shared_ptr<SyntaxNode> var = m_variables[variable];
	assign->AddChild(var);
	
	std::shared_ptr<SyntaxNode> add(new SyntaxNodeAdd(*this, 0));
	add->AddChildFront(var);
	add->AddChildFront(m_stack.top());
	m_stack.pop();
	
	assign->AddChild(add);
	
	m_stack.push(assign);
	
}
void SyntaxNodeScope::PushAdd() {
	printf("plus\n");
	std::shared_ptr<SyntaxNode> current(new SyntaxNodeAdd(*this, 0));
	current->AddChildFront(m_stack.top());
	m_stack.pop();
	current->AddChildFront(m_stack.top());
	m_stack.pop();
	m_stack.push(current);
}

void SyntaxNodeScope::PushSub() {
	printf("sub\n");
	std::shared_ptr<SyntaxNode> current(new SyntaxNodeSub(*this,0));
	current->AddChildFront(m_stack.top());
	m_stack.pop();
	current->AddChildFront(m_stack.top());
	m_stack.pop();
	m_stack.push(current);
}

void SyntaxNodeScope::PushMul() {
	printf("mul\n"); 
	std::shared_ptr<SyntaxNode> current(new SyntaxNodeMul(*this, 0));
	current->AddChildFront(m_stack.top());
	m_stack.pop();
	current->AddChildFront(m_stack.top());
	m_stack.pop();
	m_stack.push(current);
}

void SyntaxNodeScope::PushDiv() {
	printf("div\n"); std::shared_ptr<SyntaxNode> current(new SyntaxNodeDiv(*this, 0));
	current->AddChildFront(m_stack.top());
	m_stack.pop();
	current->AddChildFront(m_stack.top());
	m_stack.pop();
	m_stack.push(current);
}

void SyntaxNodeScope::PushMod() {
	printf("mod\n");
	std::shared_ptr<SyntaxNode> current(new SyntaxNodeMod(*this, 0));
	current->AddChildFront(m_stack.top());
	m_stack.pop();
	current->AddChildFront(m_stack.top());
	m_stack.pop();
	m_stack.push(current);
}

void SyntaxNodeScope::PushInc(const char *variable, bool isBack) {
//	if (!IsVariableParamExist(variable)) {
//		Error(std::string(variable) + " undefined");
//	}	
	std::shared_ptr<SyntaxNode> var = m_variables[variable];
	std::shared_ptr<SyntaxNode> inc(new SyntaxNodeInc(*this, 0, isBack));
	inc->AddChild(var);
	m_stack.push(inc);
}

void SyntaxNodeScope::PushBlock() {
	printf("block\n");
	std::shared_ptr<SyntaxNode> current(new SyntaxNode(0, "()"));
	current->AddChildFront(m_stack.top());
	m_stack.pop();
	m_stack.push(current);
}

void SyntaxNodeScope::PushStatement() {
	SYNTAX_NODE_TYPE type = m_stack.top()->GetType();
	const char *content = m_stack.top()->GetContent();
	AddChild(m_stack.top());
	m_stack.pop();
}

void SyntaxNodeScope::PushAssignmentStatement() {
	//if (!IsVariableParamExist(m_last_variable.c_str())) {
	//	throw error_info(m_last_variable + " undefined");
	//}
//	std::shared_ptr<SyntaxNode> var = GetVariableParam(m_last_variable.c_str());
//	if (static_cast<SyntaxNodeVariable *>(var.get())->IsConst()) {
//		throw error_info(m_last_variable + " is const, can not be assgin");
//	}
//	std::shared_ptr<SyntaxNode> assign(new SyntaxNodeAssignment(*this, 0));
//	assign->AddChild(var);
//	assign->AddChild(m_stack.top());
//	m_stack.pop();
//	
//	m_stack.push(assign);
}
void SyntaxNodeScope::PushInitStatement() {
//	if (!IsVariableParamExist(m_last_variable.c_str())) {
//		throw error_info(m_last_variable + " undefined");
//	}
//	std::shared_ptr<SyntaxNode> var = GetVariableParam(m_last_variable.c_str());
//	std::shared_ptr<SyntaxNode> assign(new SyntaxNodeAssignment(*this, 0));
//	assign->AddChild(var);
//	assign->AddChild(m_stack.top());
//	m_stack.pop();
//	
//	m_stack.push(assign);
}

void SyntaxNodeScope::DefineVariable(const Lexical &lexical) {
	const std::string &varName = lexical.GetChild(1)->GetChild(1)->GetContent();
	if (IsVariableExistInner(varName.c_str())) {
		Error(lexical.GetLineNO(), varName + " redefined");
	}
	std::shared_ptr<SyntaxNodeVariable> variable(new SyntaxNodeVariable(*this,
		lexical.GetLineNO(),varName.c_str(),
		ProduceDataType(*lexical.GetChild(0)),
		StatisticsKeyWord("*", lexical), GetCurrentPos()));
	m_variables.insert(std::make_pair(varName, variable));	
}

const std::shared_ptr<SyntaxNodeScope> SyntaxNodeScope::DefineProc(const Lexical &lexical) {
	const std::string &procName = lexical.GetChild(1)->GetContent();
	if (IsProcExist(procName.c_str())) {
		Error(lexical.GetLineNO(), procName + " redefined");
	}
	std::shared_ptr<SyntaxNodeProcDef> procDef(new SyntaxNodeProcDef(*this,
		lexical.GetLineNO(), procName.c_str(),
		ProduceDataType(*lexical.GetChild(0))));
	AddChild(procDef);
	m_procs.insert(std::make_pair(procName, procDef));	
	return procDef->GetBody();
}

const std::shared_ptr<SyntaxNodeScope> &SyntaxNodeScope::DefineStruct(const Lexical &lexical) {
	const std::string &structName = lexical.GetChild(1)->GetChild(0)->GetContent();
	if (IsStructExist(structName.c_str())) {
		Error(lexical.GetLineNO(), structName + " redefined");
	}
	std::shared_ptr<SyntaxNodeStructDef> structDef(new SyntaxNodeStructDef(*this,
		lexical.GetLineNO(),
		structName.c_str()));
	AddChild(structDef);
	m_structs.insert(std::make_pair(structName, structDef));	
	return structDef->GetBody();
}

const std::shared_ptr<SyntaxNodeScope> &SyntaxNodeScope::DefineUnion(const Lexical &lexical) {
	const std::string &uinonName = lexical.GetChild(1)->GetChild(0)->GetContent();
	if (IsUnionExist(uinonName.c_str())) {
		Error(lexical.GetLineNO(), uinonName + " redefined");
	}
	std::shared_ptr<SyntaxNodeUnionDef> unionDef(new SyntaxNodeUnionDef(*this,
		lexical.GetLineNO(),
		uinonName.c_str()));
	AddChild(unionDef);
	m_unions.insert(std::make_pair(uinonName, unionDef));	
	return unionDef->GetBody();
}

void SyntaxNodeScope::DefineEnum(const Lexical &lexical) {
	const std::string &enumName = lexical.GetChild(1)->GetContent();
	if (IsEnumExistInner(enumName.c_str())) {
		Error(lexical.GetLineNO(), enumName + " redefined");
	}
	std::shared_ptr<SyntaxNodeEnumDef> enumDef(new SyntaxNodeEnumDef(*this,
		lexical.GetLineNO(),
		enumName.c_str(),
		GetCurrentPos()));
	AddChild(enumDef);
	const Lexical &values = *lexical.GetChild(3);
	int64_t value = 0;
	for (size_t index = 0; index < values.GetChildrenCount(); index += 2) {
		std::string name = values.GetChild(index)->GetContent();
		if (!values.GetChild(index)->GetChild(1)->GetContent().empty()) {
			name = values.GetChild(index)->GetChild(0)->GetContent();
			value = atoll(values.GetChild(index)->GetChild(1)->GetChild(1)->GetContent().c_str());
		}
		enumDef->SetEnumValue(name.c_str(), value++);
	}
	m_enums.insert(std::make_pair(enumName, enumDef));	
}

void SyntaxNodeScope::AppendProcCall(const Lexical &lexical) {
	const std::string &callName = lexical.GetChild(0)->GetContent();
	std::shared_ptr<SyntaxNodeProcCall> procCall(new SyntaxNodeProcCall(*this,
		lexical.GetLineNO(),
		callName.c_str()));
	AddChild(procCall);
	procCall->GenerateArgmentsSyntaxNode(*lexical.GetChild(2));
}
void SyntaxNodeScope::PushReturn() {
//	if (!CheckDataType(GetProcRetType(), m_stack.top())) {
//		Error("Type Error"); 
//	}
//	std::shared_ptr<SyntaxNode> ret(new SyntaxNodeReturn(*this, 0));
//	ret->AddChild(m_stack.top());
//	m_stack.pop();
//	AddChild(ret);
}

const std::shared_ptr<SyntaxNodeScope> &SyntaxNodeScope::AppendFor(const Lexical &lexical) {
	printf("AppendFor\n");
	std::shared_ptr<SyntaxNodeFor> current(new SyntaxNodeFor(*this, lexical.GetLineNO()));
	m_stack.push(current);
	return current->GetWhole();
}

const std::shared_ptr<SyntaxNodeScope> SyntaxNodeScope::AppendWhile(const Lexical &lexical) {
	printf("AppendWhile\n");
	std::shared_ptr<SyntaxNodeWhile> current(new SyntaxNodeWhile(*this, lexical.GetLineNO()));
	m_stack.push(current);
	current->GenerateCondtionSyntaxNode(*lexical.GetChild(1));
	return current->GetBody();
}

const std::shared_ptr<SyntaxNodeScope> SyntaxNodeScope::AppendDoWhile(const Lexical &lexical) {
	printf("AppendDoWhile\n");
	std::shared_ptr<SyntaxNodeWhile> current(new SyntaxNodeWhile(*this, lexical.GetLineNO(), true));
	m_stack.push(current);
	current->GenerateCondtionSyntaxNode(*lexical.GetChild(3));
	return current->GetBody();
}

const std::shared_ptr<SyntaxNodeScope> SyntaxNodeScope::AppendIf(const Lexical &lexical) {
	printf("AppendIf\n");
	std::shared_ptr<SyntaxNodeIfElse> current(new SyntaxNodeIfElse(*this, lexical.GetLineNO()));
	m_stack.push(current);
	current->GenerateCondtionSyntaxNode(*lexical.GetChild(1));
	return current->GetBody();
}
const std::shared_ptr<SyntaxNodeScope> SyntaxNodeScope::AppendElseIf(const Lexical &lexical) {
	printf("AppendElseIf\n");
	std::shared_ptr<SyntaxNodeIfElse> current(new SyntaxNodeIfElse(*this, lexical.GetLineNO()));
	m_stack.push(current);
	current->GenerateCondtionSyntaxNode(*lexical.GetChild(2));
	return current->GetBody();
}
const std::shared_ptr<SyntaxNodeScope> SyntaxNodeScope::AppendElse(const Lexical &lexical) {
	printf("AppendElse\n");
	std::shared_ptr<SyntaxNodeIfElse> current(new SyntaxNodeIfElse(*this, lexical.GetLineNO()));
	m_stack.push(current);
	return current->GetBody();
}

void SyntaxNodeScope::AddParam(const char *param) {
//	std::shared_ptr<SyntaxNodeVariable> variable(
//		new SyntaxNodeVariable(*this, 0, param, m_last_data_type, GetCurrentPos()));
//	m_parameters.push_back(variable);
}

void SyntaxNodeScope::PushType(const char *type, bool isConst) {

}

void SyntaxNodeScope::OutputFile(std::unique_ptr<Output>& output) throw (std::exception) {
	SyntaxNode::OutputInstructions(output);
}

void SyntaxNodeScope::OutputInstructions(std::unique_ptr<Output>& output) {
	output->ProcessScope(*this, output);
}



void SyntaxNodeScope::LoopGenerate(std::unique_ptr<Output>& output) {
	OutputInstructions(output);
	//int times = m_argments.front()->GetValue();
	//output->GetStream() << '\t' << "cmpq    $" << std::to_string(times) <<
	//	",  %rcx" << std::endl;
}

size_t SyntaxNodeScope::StatisticsAssginsCount() {
	return m_variables.size();
}

bool SyntaxNodeScope::IsProcExist(const char *name) {
	return m_procs.find(name) != m_procs.end();
}

bool SyntaxNodeScope::IsVariableExistInner(const char *name) const {
	return m_variables.find(name) != m_variables.end();
}

bool SyntaxNodeScope::IsVariableExist(const char *name) const {
	if (IsVariableExistInner(name)) {
		return true;
	}
	else if (IsOutermost()) {
		return false;
	}
	else {
		return m_outer->IsVariableExist(name);
	}
}


bool SyntaxNodeScope::IsEnumExistInner(const char *name)const {
	return m_enums.find(name) != m_enums.end();
}
bool SyntaxNodeScope::IsStructExist(const char *name)const {
	return m_structs.find(name) != m_structs.end();
}
bool SyntaxNodeScope::IsUnionExist(const char *name)const {
	return m_unions.find(name) != m_unions.end();
}
std::shared_ptr<SyntaxNodeVariable> SyntaxNodeScope::GetVariable(const char *name) {
	if (IsVariableExistInner(name)) {
		return m_variables[name];
	}
	else if (IsOutermost()) {
		return std::shared_ptr<SyntaxNodeVariable>();
	}
	else {
		return m_outer->GetVariable(name);
	}
}

void SyntaxNodeScope::FindEffectives() {
	FindEffectives(m_effectives);
}

void SyntaxNodeScope::GenerateParallel() throw (std::exception) {
	std::cout << std::endl << "Scope(" << GetContent() << "):";
	GenerateParallel(m_effectives);
	std::cout << m_parallel << std::endl;
}

std::shared_ptr<SyntaxNodeAssignment> SyntaxNodeScope::GetLastAssign(const char *name, int line, bool findedVariable) {
	for (auto it = m_children.rbegin(); it != m_children.rend(); ++it) {
		std::shared_ptr<SyntaxNode> node = (*it);
		if (!findedVariable) {
			if ((*it)->GetLine() == line) {
				findedVariable = true;
			}
		}
		else {
			if (SYNTAX_NODE_TYPE_ASSIGNMENT == (*it)->GetType()) {
				SyntaxNodeVariable *variable = static_cast<SyntaxNodeVariable *>((*it)->m_children.front().get());
				if (name == variable->GetContent()) {
					std::shared_ptr<SyntaxNodeAssignment> assignment =
						std::dynamic_pointer_cast<SyntaxNodeAssignment>(*it);
					return assignment;
				}
			}
		}
	}
	if (!IsOutermost()) {
		return m_outer->GetLastAssign(name, line, true);
	}
	else {
		return std::shared_ptr<SyntaxNodeAssignment>();
	}
}


void SyntaxNodeScope::FindEffectives(std::set<std::shared_ptr<SyntaxNode>> &effectives) {
	for (std::shared_ptr<SyntaxNode> &child : m_children) {
		child->FindEffectives(child, effectives);
	}
}

void SyntaxNodeScope::GenerateParallel(std::set<std::shared_ptr<SyntaxNode>> &effectives) throw (std::exception) {
	for (const std::shared_ptr<SyntaxNode> &effective : effectives) {
		while (true) {
			GENERATE_PARALLEL_RESULT result = effective->GenerateParallel(effective, m_parallel);
			if (GENERATE_PARALLEL_RESULT_COMPLETED == result) {
				break;
			}
			else if (GENERATE_PARALLEL_RESULT_NO_FIND == result) {
				m_parallel.AddElement();
			}
		}
	}
	m_parallel.Truncation();
}

size_t SyntaxNodeScope::PushRegister(const char *reg) {
	size_t offset = GetScopeStackTopOffset();
	m_registers.push(reg);
	return offset;
}

size_t SyntaxNodeScope::PopRegister(std::string &reg) {
	reg = m_registers.top();
	m_registers.pop();
	size_t offset =  GetScopeStackTopOffset();
	return offset;
}

size_t SyntaxNodeScope::PushArgument() {
	size_t offset = GetScopeStackTopOffset();
	m_arguments.push("");
	return offset;
}

void SyntaxNodeScope::PopArgument() {
	m_arguments.pop();
}

size_t SyntaxNodeScope::PushCache() {
	size_t offset = GetScopeStackTopOffset();
	m_caches.push("");
	return offset;
}
void SyntaxNodeScope::PopCache() {
	m_caches.pop();
}

const size_t SyntaxNodeScope::GetCurrentPos() const {
	return m_base_pos + m_arguments.size() +
		m_variables.size() + m_registers.size() + m_caches.size();
}

const size_t SyntaxNodeScope::GetScopeStackTopOffset() const {
	return (GetCurrentPos() + 1) * 8;
}

const size_t SyntaxNodeScope::GetSubProcOffset() const {
	return (GetCurrentPos() + 1) / 2 * 2 * 8;
}


bool SyntaxNodeScope::CheckDataType(DATA_TYPE_TYPE type, const std::shared_ptr<SyntaxNode> &node) {
	return node->IsSameDataType(type);
}

void SyntaxNodeScope::GenerateSyntaxNode(const Lexical &lexical, std::vector<std::shared_ptr<SyntaxNode>> &syntaxs) {
	const std::string &name = lexical.GetPattern().GetRule().GetName();
	if ("proc_call" == name) {
		syntaxs.push_back(std::shared_ptr<SyntaxNode>(
			new SyntaxNodeProcCall(*this, lexical.GetLineNO(), 
			lexical.GetChild(0)->GetChild(0)->GetContent().c_str())));
	}	
	else if ("variable" == name) {
		if (!IsVariableExist(lexical.GetContent().c_str())) {
			Error(lexical.GetLineNO(), lexical.GetContent() + " undefined");
		}
		syntaxs.push_back(GetVariable(lexical.GetContent().c_str()));
	}
	else if ("string" == name) {
		syntaxs.push_back(std::shared_ptr<SyntaxNode>(
			new SyntaxNodeString(*this, lexical.GetLineNO(), 
			lexical.GetContent().c_str())));
	}
	else if ("numeric" == name) {
	}
	else if ("integer" == name) {
		syntaxs.push_back(std::shared_ptr<SyntaxNode>(
			new SyntaxNodeNumber(*this, lexical.GetLineNO(), 
			atoi(lexical.GetContent().c_str()))));
	}
	else {
		for (size_t index = 0; index < lexical.GetChildrenCount(); index++) {
			GenerateSyntaxNode(*lexical.GetChild(index), syntaxs);
		}
	}
}