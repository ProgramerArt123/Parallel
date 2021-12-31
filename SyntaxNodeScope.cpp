#include <fstream>
#include <string.h>
#include "Scanner.h"
#include "common.h"
#include "SyntaxNodeScope.h"

SyntaxNodeScope::SyntaxNodeScope(int line, const char *content) :
	SyntaxNode(line, content),m_parallel(*this) {
	m_type = SYNTAX_NODE_TYPE_SCOPE;
}

SyntaxNodeScope::SyntaxNodeScope(SyntaxNodeScope &outter, int line, const SyntaxNodeProcDef *proc, const char *content)
	:
	SyntaxNode(outter, line, content), m_proc(proc),
	m_base_pos(outter.GetCurrentPos()),m_parallel(*this) {
	m_type = SYNTAX_NODE_TYPE_SCOPE;
}
void SyntaxNodeScope::PushAddAssign(const char *variable) {
	if (!IsVariableParamExist(variable)) {
		Error(std::string(variable) + " undefined");
	}
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
	if (!IsVariableParamExist(variable)) {
		Error(std::string(variable) + " undefined");
	}	
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

void SyntaxNodeScope::PushNumber(int number) {
	printf("+++%d\n", number);
	m_stack.push(std::shared_ptr<SyntaxNode>(new SyntaxNodeNumber(*this,0, number)));
}

void SyntaxNodeScope::PushString(const char *itera) {
	m_stack.push(std::shared_ptr<SyntaxNode>(new SyntaxNodeString(*this, 0,itera)));
}

void SyntaxNodeScope::PushVariable(const char *name) {
	if (!IsVariableParamExist(name)) {
		Error(std::string(name) + " undefined");
	}
	m_stack.push(GetVariableParam(name));
}


std::shared_ptr<SyntaxNodeScope> &SyntaxNodeScope::PushProcCallEnter(const char *name) {
	printf("PushProcCallEnter\n");
	SyntaxNodeProcCall *call = new SyntaxNodeProcCall(*this, 0, name);
	std::shared_ptr<SyntaxNode> current(call);
	m_stack.push(current);
	return call->GetArgments();
}

void SyntaxNodeScope::PushProcCallExit() {
	printf("PushProcCallExit\n");
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
	const std::string &varName = lexical.GetChild(1)->GetContent();
	if (IsVariableParamExistInner(varName.c_str())) {
		Error(varName + " redefined");
	}
	std::shared_ptr<SyntaxNodeVariable> variable(new SyntaxNodeVariable(*this,
		lexical.GetLineNO(),varName.c_str(),
		SourceCodeFile::ProduceDataType(*lexical.GetChild(0)), GetCurrentPos()));
	m_variables.insert(std::make_pair(varName.c_str(), variable));	
}

const std::shared_ptr<SyntaxNodeScope> &SyntaxNodeScope::DefineProc(const Lexical &lexical) {
	const std::string &procName = lexical.GetChild(1)->GetContent();
	if (IsProcExist(procName.c_str())) {
		Error(procName + " redefined");
	}
	std::shared_ptr<SyntaxNodeProcDef> procDef(new SyntaxNodeProcDef(*this,
		lexical.GetLineNO(), procName.c_str(),
		SourceCodeFile::ProduceDataType(*lexical.GetChild(0))));
	AddChild(procDef);
	return procDef->GetBody();
}

void SyntaxNodeScope::DefineEnum(const Lexical &lexical) {
	const std::string &enumName = lexical.GetChild(1)->GetContent();
	if (IsEnumExistInner(enumName.c_str())) {
		Error(enumName + " redefined");
	}
	std::shared_ptr<SyntaxNodeEnum> variable(new SyntaxNodeEnum(*this,
		lexical.GetLineNO(),
		enumName.c_str(),
		GetCurrentPos()));
	const Lexical &values = *lexical.GetChild(3);
	int64_t value = 0;
	for (size_t index = 0; index < values.GetChildrenCount(); index += 2) {
		std::string name = values.GetChild(index)->GetContent();
		if (!values.GetChild(index)->GetChild(1)->GetContent().empty()) {
			name = values.GetChild(index)->GetChild(0)->GetContent();
			value = atoll(values.GetChild(index)->GetChild(1)->GetChild(1)->GetContent().c_str());
		}
		variable->SetEnumValue(name.c_str(), value++);
	}
	m_enums.insert(std::make_pair(enumName.c_str(), variable));	
}

void SyntaxNodeScope::PushReturn() {
	if (!CheckDataType(GetProcRetType(), m_stack.top())) {
		Error("Type Error"); 
	}
	std::shared_ptr<SyntaxNode> ret(new SyntaxNodeReturn(*this, 0));
	ret->AddChild(m_stack.top());
	m_stack.pop();
	AddChild(ret);
}

std::shared_ptr<SyntaxNodeScope> &SyntaxNodeScope::PushLoopEnter() {
	printf("PushLoopEnter\n");
	SyntaxNodeLoop *loop = new SyntaxNodeLoop(*this, 0);
	std::shared_ptr<SyntaxNodeLoop> current = std::shared_ptr<SyntaxNodeLoop>(loop);
	m_stack.push(current);
	return current->GetBody();
}

void SyntaxNodeScope::PushLoopExit() {
	printf("PushLoopExit\n");
}

void SyntaxNodeScope::AddArgment(uint64_t argment) {
	std::shared_ptr<SyntaxNodeNumber> arg(new SyntaxNodeNumber(*this, 0, argment));
	m_argments.push_back(arg);
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

void SyntaxNodeScope::DefGenerate(std::unique_ptr<Output>& output) {
	uint32_t index = 0;
	for (std::shared_ptr<SyntaxNodeVariable> &parameter : m_parameters) {
		if (index < PLATFORM.registersCount) {
			output->GetStream() << '\t' << "movq	%" << PLATFORM.registers[index] << ", -"
				<< std::to_string(parameter->GetScopeStackTopOffset()) <<
				"(%rbp)" << std::endl;
		}
		else {
			output->GetStream() << '\t' << "movq	" << GetParameterStackTopOffset(index) <<
				"(%rbp), %rax" << std::endl;
			output->GetStream() << '\t' << "movq	%rax, -" << std::to_string(parameter->GetScopeStackTopOffset())
				<< "(%rbp)" << std::endl;
		}
		index++;
	}
	OutputInstructions(output);
}

void SyntaxNodeScope::LoopGenerate(std::unique_ptr<Output>& output) {
	OutputInstructions(output);
	int times = m_argments.front()->GetValue();
	output->GetStream() << '\t' << "cmpq    $" << std::to_string(times) <<
		",  %rcx" << std::endl;
}

size_t SyntaxNodeScope::StatisticsAssginsCount() {
	return m_variables.size();
}

bool SyntaxNodeScope::IsProcExist(const char *name) {
	return m_procs.find(name) != m_procs.end();
}

bool SyntaxNodeScope::IsVariableParamExistInner(const char *name)const {
	return IsVariableExistInner(name) || IsParamExistInner(name);
}

bool SyntaxNodeScope::IsVariableExistInner(const char *name) const {
	return m_variables.find(name) != m_variables.end();
}

bool SyntaxNodeScope::IsParamExistInner(const char *name) const {
	for (const std::shared_ptr<SyntaxNodeVariable> &parameter : m_parameters) {
		if (0 == strcmp(parameter->GetContent(), name)) {
			return true;
		}
	}
	return false;
}

bool SyntaxNodeScope::IsVariableParamExist(const char *name) const {
	return IsVariableExist(name) || IsParamExist(name);
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

bool SyntaxNodeScope::IsParamExist(const char *name)const {
	if (IsParamExistInner(name)) {
		return true;
	}
	else if (IsOutermost()) {
		return false;
	}
	else {
		return m_outer->IsParamExist(name);
	}
}
bool SyntaxNodeScope::IsEnumExistInner(const char *name)const {
	return m_enums.find(name) != m_enums.end();
}

std::shared_ptr<SyntaxNodeVariable> SyntaxNodeScope::GetVariableParam(const char *name) {
	if (IsVariableExistInner(name)) {
		return m_variables[name];
	}
	else if (IsParamExistInner(name)) {
		for (std::shared_ptr<SyntaxNodeVariable> & parameter : m_parameters) {
			if (0 == strcmp(parameter->GetContent(), name)) {
				return parameter;
			}
		}
	}
	else if (IsOutermost()) {
		return std::shared_ptr<SyntaxNodeVariable>();
	}
	else {
		return m_outer->GetVariableParam(name);
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
	return m_base_pos + m_parameters.size() + m_arguments.size() +
		m_variables.size() + m_registers.size() + m_caches.size();
}

const size_t SyntaxNodeScope::GetScopeStackTopOffset() const {
	return (GetCurrentPos() + 1) * 8;
}

const size_t SyntaxNodeScope::GetSubProcOffset() const {
	return (GetCurrentPos() + 1) / 2 * 2 * 8;
}

const size_t SyntaxNodeScope::GetParameterStackTopOffset(size_t index) const {
	size_t parametersCount = m_parameters.size();
	size_t count = 0;
	const size_t codePointer = 2;
	if (0 == m_outer->GetCurrentPos() % 2){
		count = parametersCount - index + codePointer;
	}
	else{
		count = parametersCount - index + 1 + codePointer;
	}
	return count * 8;
}

const DATA_TYPE_TYPE SyntaxNodeScope::GetProcRetType()const{
	return GetProcDef()->GetDataType();
}


const SyntaxNodeProcDef *SyntaxNodeScope::GetProcDef() const {
	return m_proc;
}

bool SyntaxNodeScope::CheckDataType(DATA_TYPE_TYPE type, const std::shared_ptr<SyntaxNode> &node) {
	return node->IsSameDataType(type);
}