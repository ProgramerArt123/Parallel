#include <fstream>
#include <string.h>
#include "Scope.h"
#include "common.h"

Scope::Scope(){
	m_type = SYNTAX_NODE_TYPE_SCOPE;
	m_content = "Scope";
}

Scope::Scope(Scope &outter) :
	SyntaxTree(*static_cast<SyntaxNode *>(&outter)) {
	m_type = SYNTAX_NODE_TYPE_SCOPE;
	m_content = "Scope";
}

void Scope::PushAdd() {
	printf("plus\n"); 
	std::shared_ptr<SyntaxNode> current = std::shared_ptr<SyntaxNode>(new SyntaxNodeAdd()); 
	current->AddChildFront(m_stack.top());
	m_stack.pop();
	current->AddChildFront(m_stack.top());
	m_stack.pop();
	m_stack.push(current);
}

void Scope::PushSub() {
	printf("sub\n"); 
	std::shared_ptr<SyntaxNode> current = std::shared_ptr<SyntaxNode>(new SyntaxNodeSub()); 
	current->AddChildFront(m_stack.top());
	m_stack.pop();
	current->AddChildFront(m_stack.top());
	m_stack.pop();
	m_stack.push(current);
}

void Scope::PushMul() {
	printf("mul\n"); std::shared_ptr<SyntaxNode> current = std::shared_ptr<SyntaxNode>(new SyntaxNodeMul());
	current->AddChildFront(m_stack.top());
	m_stack.pop();
	current->AddChildFront(m_stack.top());
	m_stack.pop();
	m_stack.push(current);
}

void Scope::PushDiv(){
	printf("div\n"); std::shared_ptr<SyntaxNode> current = std::shared_ptr<SyntaxNode>(new SyntaxNodeDiv());
	current->AddChildFront(m_stack.top());
	m_stack.pop();
	current->AddChildFront(m_stack.top());
	m_stack.pop();
	m_stack.push(current);
}

void Scope::PushMod() {
	printf("mod\n"); 
	std::shared_ptr<SyntaxNode> current = std::shared_ptr<SyntaxNode>(new SyntaxNodeMod()); 
	current->AddChildFront(m_stack.top());
	m_stack.pop();
	current->AddChildFront(m_stack.top());
	m_stack.pop();
	m_stack.push(current);
}

void Scope::PushBlock() {
	printf("block\n"); 
	std::shared_ptr<SyntaxNode> current = std::shared_ptr<SyntaxNode>(new SyntaxNode("()")); 
	current->AddChildFront(m_stack.top()); 
	m_stack.pop();
	m_stack.push(current);
}

void Scope::PushNumber(int number) {
	printf("+++%d\n", number);
	m_stack.push(std::shared_ptr<SyntaxNode>(new SyntaxNodeNumber(number)));
}

void Scope::PushString(const char *itera) {
	m_stack.push(std::shared_ptr<SyntaxNode>(new SyntaxNodeString(itera)));
}

void Scope::PushVariable(const char *name) {
	if (!IsVariableExist(name)) {
		perror(name);
		throw std::exception();
	}
	if (m_vars.find(name) != m_vars.end()) {
		m_stack.push(m_vars[name]);
	}
	else {
		for (std::shared_ptr<SyntaxNodeVariable> &parameter : m_parameters) {
			if (0 == strcmp(parameter->GetContent(), name)) {
				m_stack.push(parameter);
				break;
			}
		}
	}
}

std::shared_ptr<Scope> &Scope::PushProcDefEnter(const char *name) {
	printf("PushProcDefEnter\n");
	SyntaxNodeProcDef *proc = new SyntaxNodeProcDef(name, *this);
	std::shared_ptr<SyntaxNode> current = std::shared_ptr<SyntaxNode>(proc);
	m_stack.push(current);
	return proc->GetBody();
}

void Scope::PushProcDefExit() {
	printf("PushProcDefExit\n"); 
}

void Scope::PushProcCallEnter(const char *name) {
	printf("PushProcCallEnter\n");
	m_proc_call = std::shared_ptr<SyntaxNodeProcCall>(new SyntaxNodeProcCall(name, *this));
	m_stack.push(std::shared_ptr<SyntaxNode>(m_proc_call));
}

void Scope::PushProcCallExit() {
	m_proc_call.reset();
	printf("PushProcCallExit\n");
}

void Scope::PushStatement() {
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

void Scope::PushAssignmentStatement(const char *variable) {
	std::shared_ptr<SyntaxNode> assign = std::shared_ptr<SyntaxNode>(new SyntaxNodeAssignment(*this));
	std::shared_ptr<SyntaxNode> var;
	if (!IsVariableExist(variable)) {
		std::shared_ptr<SyntaxNodeVariable> varv = std::shared_ptr<SyntaxNodeVariable>(
			new SyntaxNodeVariable(*this, variable, GetNewVariablePos()));
		m_vars.insert(std::pair<std::string, std::shared_ptr<SyntaxNodeVariable>>(variable, varv));
		var = varv;
	}
	else {
		var = m_vars[variable];
	}
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

void Scope::PushReturn() {
	std::shared_ptr<SyntaxNode> ret = std::shared_ptr<SyntaxNode>(new SyntaxNodeReturn());
	ret->AddChild(m_stack.top());
	m_stack.pop();
	AddChild(ret);
}

std::shared_ptr<Scope> &Scope::PushLoopEnter() {
	printf("PushLoopEnter\n");
	SyntaxNodeLoop *loop = new SyntaxNodeLoop(*this);
	std::shared_ptr<SyntaxNodeLoop> current = std::shared_ptr<SyntaxNodeLoop>(loop);
	m_stack.push(current);
	return current->GetBody();
}

void Scope::PushLoopExit() {
	printf("PushLoopExit\n");
}

void Scope::AddArgment(uint64_t argment) {
	std::shared_ptr<SyntaxNodeNumber> arg(new SyntaxNodeNumber(argment));
	m_argments.push_back(arg);
}

void Scope::AddParam(const char *param) {
	std::shared_ptr<SyntaxNodeVariable> variable(new SyntaxNodeVariable(
		*this, param, m_parameters.size()));
	m_parameters.push_back(variable);
}


void Scope::generate(const char *fileName) throw (std::exception) {
	std::stringstream output;
	SyntaxTree::generate(output);
	std::ofstream file(fileName);
	if (!file.is_open()) {
		throw std::exception();
	}
	PLATFORM.PageHeaderGenerate(fileName, file);
	const std::string &constContent = consts.str();
	if (!constContent.empty()) {
		PLATFORM.ConstGenerate(file);
		file << constContent;
	}
	file << '\t' << ".text" << std::endl;
	file << output.str();
	PLATFORM.PageFooterGenerate(file);
}



void Scope::DefGenerate(std::stringstream& output) {
	//1.������ֵ��Ҫ���������ڴ�
	//2.registers����ջ��������
	//3.����ı���������ջ
	//4.ȡʵ��ֵʱ��Ҫ���ⲿ���ò���һ�µĶ�Ӧ����
	//5.fast_call��������ʵ��˳�����ν�ֵд��registers
	//6.registers��ֵ�ᱻ�����Ƶ��ڴ���ʹ�ã������Ĳ���ֱ��ʹ�����ʱ���ڴ�
	/*size_t assginsCount = StatisticsAssginsCount();
	size_t parametersCount = m_parameters.size();
	size_t registersParametersCount = parametersCount < registersCount ?
		parametersCount : registersCount;
	for (size_t index = 0; index < registersParametersCount; index ++) {
		output << '\t' << "movq	%" << registers[index] << ", -"
			<< std::to_string(assginsCount+4+index * 4) << 
			"(%rbp)" << std::endl;
	}
	SyntaxNode::generate(output);*/
	size_t parametersCount = m_parameters.size();
	uint32_t index = 0;
	for (std::shared_ptr<SyntaxNodeVariable> &parameter : m_parameters) {
		if (index < PLATFORM.registersCount) {
			output << '\t' << "movq	%" << PLATFORM.registers[index] << ", -"
				<< std::to_string((parameter->GetScopePos() + 1) * 8) <<
				"(%rbp)" << std::endl;
		}
		else {
			output << '\t' << "movq	" << 16 + 8 * (parametersCount - 1 - index) << 
				"(%rbp), %rax" << std::endl;
			output << '\t' << "movq	%rax, -" << std::to_string((parameter->GetScopePos() + 1) * 8)
				<< "(%rbp)" << std::endl;
		}
		index++;
	}
	SyntaxNode::generate(output);
}

uint32_t Scope::CallGenerate(std::stringstream& output, std::list<std::shared_ptr<SyntaxNode>> &argments) {
	uint32_t index = 0;
	uint32_t top = (m_runtime_pos + 1) / 2 * 16;

	for (std::shared_ptr<SyntaxNode> &argment : argments) {
		std::cout << *argment << std::endl;
	}

	if (argments.size() > PLATFORM.registersCount) {
		top += ((argments.size() - PLATFORM.registersCount + 1) / 2 * 16);
	}
	for (std::shared_ptr<SyntaxNode> &argment : argments) {
		std::string dst;
		if (index < PLATFORM.registersCount) {
			dst = std::string("%") + PLATFORM.registers[index];
		}
		else {
			dst = "-" + std::to_string(top - (index - PLATFORM.registersCount) * 8) + "(%rbp)";
		}
		switch (argment->GetType())
		{
		case SYNTAX_NODE_TYPE_NUMBER:
		{
			SyntaxNodeNumber *number = static_cast<SyntaxNodeNumber *>(argment.get());
			output << '\t' << "movq	$" << number->GetValue()
				<< ", " << dst << std::endl;
		}
		break;
		case SYNTAX_NODE_TYPE_STRING:
		{
			SyntaxNodeString *string = static_cast<SyntaxNodeString *>(argment.get());
			string->generate(output);
			PLATFORM.ProcStringArgmentGenerate(string->GetNO(), dst.c_str(), output);
		}
		break;
		case SYNTAX_NODE_TYPE_VARIABLE:
		{
			SyntaxNodeVariable *variable = static_cast<SyntaxNodeVariable *>(argment.get());
			if (index < PLATFORM.registersCount) {
				output << '\t' << "movq	-" << (variable->GetScopePos() + 1) * 8 << "(%rbp), " << dst << std::endl;
			}
			else {
				output << '\t' << "movq	-" << (variable->GetScopePos() + 1) * 8 << "(%rbp), %rax" << std::endl;
				output << '\t' << "movq	%rax, " << dst << std::endl;
			}
		}
		break;
		default:
			perror("Scope::CallGenerate");
			throw std::exception();
			break;
		}
		index++;
	}
	if (top > 0) {
		output << '\t' << "subq    $" << top << ", %rsp" << std::endl;
	}
	return top;
}

void Scope::LoopGenerate(std::stringstream& output) {
	SyntaxNode::generate(output);
	int times = m_argments.front()->GetValue();
	output << '\t' << "cmpq    $" << std::to_string(times) <<
		",  %rcx" << std::endl;
}

void Scope::UpdateRuntimePos(size_t pos) {
	m_runtime_pos = pos;
}

size_t Scope::StatisticsAssginsCount() {
	return m_vars.size();
}

size_t Scope::GetNewVariablePos() {
	size_t pos = m_parameters.size() + m_vars.size();
	if (!IsRoot()) {
		pos += static_cast<Scope *>(&m_parent)->GetNewVariablePos();
	}
	return pos;
}

bool Scope::IsProcExist(const char *name) {
	return m_procs.find(name) != m_procs.end();
}

bool Scope::IsVariableExist(const char *name) {
	if (m_vars.find(name) != m_vars.end()) {
		return true;
	}
	else {
		for (std::shared_ptr<SyntaxNodeVariable> & parameter : m_parameters) {
			if (0==strcmp(parameter->GetContent(),name)) {
				return true;
			}
		}
		return false;
	}
}

void Scope::FindEffectives() {
	SyntaxTree::FindEffectives(m_effectives);
}

void Scope::GenerateParallel() throw (std::exception) {
	SyntaxTree::GenerateParallel(m_effectives);
	std::cout << m_nodes << std::endl;
}

std::shared_ptr<SyntaxNodeAssignment> Scope::GetLastAssign(const char *name, int line, bool findedVariable) {
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
	if (!IsRoot()) {
		Scope &scope = *static_cast<Scope *>(&m_parent);
		scope.GetLastAssign(name, line, true);
	}
	else {
		return std::shared_ptr<SyntaxNodeAssignment>();
	}
}