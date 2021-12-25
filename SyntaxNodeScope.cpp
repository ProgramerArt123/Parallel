#include <fstream>
#include <string.h>
#include "SyntaxNodeScope.h"
#include "common.h"

SyntaxNodeScope::SyntaxNodeScope(const char *content) :
	SyntaxNode(content),m_parallel(*this) {
	m_type = SYNTAX_NODE_TYPE_SCOPE;
}

SyntaxNodeScope::SyntaxNodeScope(SyntaxNodeScope &outter, const char *content) :
	SyntaxNode(outter, content),
	m_base_pos(outter.GetCurrentPos()),m_parallel(*this) {
	m_type = SYNTAX_NODE_TYPE_SCOPE;
}

void SyntaxNodeScope::PushAdd() {
	printf("plus\n");
	std::shared_ptr<SyntaxNode> current = std::shared_ptr<SyntaxNode>(new SyntaxNodeAdd());
	current->AddChildFront(m_stack.top());
	m_stack.pop();
	current->AddChildFront(m_stack.top());
	m_stack.pop();
	m_stack.push(current);
}

void SyntaxNodeScope::PushSub() {
	printf("sub\n");
	std::shared_ptr<SyntaxNode> current = std::shared_ptr<SyntaxNode>(new SyntaxNodeSub());
	current->AddChildFront(m_stack.top());
	m_stack.pop();
	current->AddChildFront(m_stack.top());
	m_stack.pop();
	m_stack.push(current);
}

void SyntaxNodeScope::PushMul() {
	printf("mul\n"); std::shared_ptr<SyntaxNode> current = std::shared_ptr<SyntaxNode>(new SyntaxNodeMul());
	current->AddChildFront(m_stack.top());
	m_stack.pop();
	current->AddChildFront(m_stack.top());
	m_stack.pop();
	m_stack.push(current);
}

void SyntaxNodeScope::PushDiv() {
	printf("div\n"); std::shared_ptr<SyntaxNode> current = std::shared_ptr<SyntaxNode>(new SyntaxNodeDiv());
	current->AddChildFront(m_stack.top());
	m_stack.pop();
	current->AddChildFront(m_stack.top());
	m_stack.pop();
	m_stack.push(current);
}

void SyntaxNodeScope::PushMod() {
	printf("mod\n");
	std::shared_ptr<SyntaxNode> current = std::shared_ptr<SyntaxNode>(new SyntaxNodeMod());
	current->AddChildFront(m_stack.top());
	m_stack.pop();
	current->AddChildFront(m_stack.top());
	m_stack.pop();
	m_stack.push(current);
}

void SyntaxNodeScope::PushBlock() {
	printf("block\n");
	std::shared_ptr<SyntaxNode> current = std::shared_ptr<SyntaxNode>(new SyntaxNode("()"));
	current->AddChildFront(m_stack.top());
	m_stack.pop();
	m_stack.push(current);
}

void SyntaxNodeScope::PushNumber(int number) {
	printf("+++%d\n", number);
	m_stack.push(std::shared_ptr<SyntaxNode>(new SyntaxNodeNumber(number)));
}

void SyntaxNodeScope::PushString(const char *itera) {
	m_stack.push(std::shared_ptr<SyntaxNode>(new SyntaxNodeString(itera)));
}

void SyntaxNodeScope::PushVariable(const char *name) {
	if (!IsVariableParamExist(name)) {
		throw "Error:" + std::string(name) + " undefined";
	}
	m_stack.push(GetVariableParam(name));
}

std::shared_ptr<SyntaxNodeScope> &SyntaxNodeScope::PushProcDefEnter(const char *name) {
	printf("PushProcDefEnter\n");
	SyntaxNodeProcDef *proc = new SyntaxNodeProcDef(name, *this);
	std::shared_ptr<SyntaxNode> current = std::shared_ptr<SyntaxNode>(proc);
	m_stack.push(current);
	return proc->GetBody();
}

void SyntaxNodeScope::PushProcDefExit() {
	printf("PushProcDefExit\n");
}

void SyntaxNodeScope::PushProcCallEnter(const char *name) {
	printf("PushProcCallEnter\n");
	m_proc_call = std::shared_ptr<SyntaxNodeProcCall>(new SyntaxNodeProcCall(name, *this));
	m_stack.push(std::shared_ptr<SyntaxNode>(m_proc_call));
}

void SyntaxNodeScope::PushProcCallExit() {
	m_proc_call.reset();
	printf("PushProcCallExit\n");
}

void SyntaxNodeScope::PushStatement() {
	SYNTAX_NODE_TYPE type = m_stack.top()->GetType();
	const char *content = m_stack.top()->GetContent();
	if (m_proc_call) {
		m_proc_call->AddChild(m_stack.top());
	}
	else {
		AddChild(m_stack.top());
	}
	m_stack.pop();
}

void SyntaxNodeScope::PushAssignmentStatement(const char *variable) {
	if (!IsVariableParamExist(variable)) {
		throw "Error:" + std::string(variable) + " undefined";
	}
	std::shared_ptr<SyntaxNode> assign = std::shared_ptr<SyntaxNode>(new SyntaxNodeAssignment(*this));
	std::shared_ptr<SyntaxNode> var = m_variables[variable];
	assign->AddChild(var);
	assign->AddChild(m_stack.top());
	m_stack.pop();
	if (m_proc_call) {
		m_proc_call->AddChild(assign);
	}
	else {
		AddChild(assign);
	}
}

void SyntaxNodeScope::DecalreVariable(const char *variable) {
	if (IsVariableParamExistInner(variable)) {
		throw "Error:" + std::string(variable) + " redefined";
	}
	std::shared_ptr<SyntaxNodeVariable> varv(new SyntaxNodeVariable(*this, variable, GetCurrentPos()));
	m_variables.insert(std::pair<std::string, std::shared_ptr<SyntaxNodeVariable>>(variable, varv));
}

void SyntaxNodeScope::PushReturn() {
	std::shared_ptr<SyntaxNode> ret = std::shared_ptr<SyntaxNode>(new SyntaxNodeReturn());
	ret->AddChild(m_stack.top());
	m_stack.pop();
	AddChild(ret);
}

std::shared_ptr<SyntaxNodeScope> &SyntaxNodeScope::PushLoopEnter() {
	printf("PushLoopEnter\n");
	SyntaxNodeLoop *loop = new SyntaxNodeLoop(*this);
	std::shared_ptr<SyntaxNodeLoop> current = std::shared_ptr<SyntaxNodeLoop>(loop);
	m_stack.push(current);
	return current->GetBody();
}

void SyntaxNodeScope::PushLoopExit() {
	printf("PushLoopExit\n");
}

void SyntaxNodeScope::AddArgment(uint64_t argment) {
	std::shared_ptr<SyntaxNodeNumber> arg(new SyntaxNodeNumber(argment));
	m_argments.push_back(arg);
}

void SyntaxNodeScope::AddParam(const char *param) {
	std::shared_ptr<SyntaxNodeVariable> variable(
		new SyntaxNodeVariable(*this, param, GetCurrentPos()));
	m_parameters.push_back(variable);
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

void SyntaxNodeScope::BeginCallGenerate(std::unique_ptr<Output>& output, std::list<std::shared_ptr<SyntaxNode>> &argments) {
	uint32_t index = 0;

	for (std::shared_ptr<SyntaxNode> &argment : argments) {
		std::string dst;
		if (index < PLATFORM.registersCount) {
			dst = std::string("%") + PLATFORM.registers[index];
		}
		else {
			dst = "-" + std::to_string(PushArgument()) + "(%rbp)";
		}
		if (index < PLATFORM.registersCount && 0 == strcmp(PLATFORM.registers[index], "rcx")) {
			output->GetStream() << '\t' << "movq	" << dst << ", -" << std::to_string(PushRegister(dst.c_str())) << "(%rbp)" << std::endl;
		}
		switch (argment->GetType())
		{
		case SYNTAX_NODE_TYPE_NUMBER:
		{
			SyntaxNodeNumber *number = static_cast<SyntaxNodeNumber *>(argment.get());
			output->GetStream() << '\t' << "movq	$" << number->GetValue() << ", " << dst << std::endl;
		}
		break;
		case SYNTAX_NODE_TYPE_STRING:
		{
			SyntaxNodeString *string = static_cast<SyntaxNodeString *>(argment.get());
			string->OutputInstructions(output);
			PLATFORM.ProcStringArgmentGenerateSerial(string->GetNO(), dst.c_str(), output->GetStream());
		}
		break;
		case SYNTAX_NODE_TYPE_VARIABLE:
		{
			SyntaxNodeVariable *variable = static_cast<SyntaxNodeVariable *>(argment.get());
			output->GetStream() << '\t' << "movq	-" << variable->GetScopeStackTopOffset() << "(%rbp), " << dst << std::endl;
		}
		break;
		default:
			perror("Scope::BeginCallGenerate");
			throw std::exception();
			break;
		}
		index++;
	}

	if (GetSubProcOffset()) {
		output->GetStream() << '\t' << "subq    $" << GetSubProcOffset() << ", %rsp" << std::endl;
	}
}

void SyntaxNodeScope::EndCallGenerate(std::stringstream& output, std::list<std::shared_ptr<SyntaxNode>> &argments) {
	if (GetSubProcOffset()) {
		output << '\t' << "addq    $" << GetSubProcOffset() << ", %rsp" << std::endl;
	}
	uint32_t index = argments.size() - 1;
	for (std::shared_ptr<SyntaxNode> &argment : argments) {
		if (index < PLATFORM.registersCount) {
			if (0 == strcmp(PLATFORM.registers[index], "rcx")) {
				std::string dst;
				size_t offset = PopRegister(dst);
				output << '\t' << "movq	" << "-" << std::to_string(offset) << "(%rbp)," << dst << std::endl;
			}
		}
		else {
			PopArgument();
		}
		index--;
	}
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
	return GetScopeStackTopOffset();
}

size_t SyntaxNodeScope::PushArgument() {
	size_t offset = GetScopeStackTopOffset();
	m_arguments.push("");
	return offset;
}

void SyntaxNodeScope::PopArgument() {
	m_arguments.pop();
}

const size_t SyntaxNodeScope::GetCurrentPos() const {
	return m_base_pos + m_parameters.size() + m_arguments.size() +
		m_variables.size() + m_registers.size();
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