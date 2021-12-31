#include <string.h>
#include "common.h"
#include "SyntaxNodeProcDefScope.h"

SyntaxNodeProcDefScope::SyntaxNodeProcDefScope(SyntaxNodeScope &outter, int line, const SyntaxNodeProcDef &proc, const char *content):
	SyntaxNodeScope(outter, line, content), m_proc(proc) {
	m_type = SYNTAX_NODE_TYPE_SCOPE;
}
void SyntaxNodeProcDefScope::AddParam(const char *param) {
//	std::shared_ptr<SyntaxNodeVariable> variable(
//		new SyntaxNodeVariable(*this, 0, param, m_last_data_type, GetCurrentPos()));
//	m_parameters.push_back(variable);
}
void SyntaxNodeProcDefScope::DefGenerate(std::unique_ptr<Output>& output) {
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

bool SyntaxNodeProcDefScope::IsParamExistInner(const char *name) const {
	for (const std::shared_ptr<SyntaxNodeVariable> &parameter : m_parameters) {
		if (0 == strcmp(parameter->GetContent(), name)) {
			return true;
		}
	}
	return false;
}

bool SyntaxNodeProcDefScope::IsVariableExistInner(const char *name)const {
	return SyntaxNodeScope::IsVariableExistInner(name) ||
		IsParamExistInner(name);
}

bool SyntaxNodeProcDefScope::IsParamExist(const char *name)const {
	if (IsParamExistInner(name)) {
		return true;
	}
	else if (IsOutermost()) {
		return false;
	}
	else {
		return m_outer->IsVariableExist(name);
	}
}

bool SyntaxNodeProcDefScope::IsVariableExist(const char *name) const {
	return SyntaxNodeScope::IsVariableExist(name) ||
		IsParamExist(name);
}

std::shared_ptr<SyntaxNodeVariable> SyntaxNodeProcDefScope::GetVariable(const char *name) {
	std::shared_ptr<SyntaxNodeVariable> variable(SyntaxNodeScope::GetVariable(name));
	if (variable) {
		return variable;
	}
	if (IsParamExistInner(name)) {
		for (std::shared_ptr<SyntaxNodeVariable> & parameter : m_parameters) {
			if (0 == strcmp(parameter->GetContent(), name)) {
				return parameter;
			}
		}
	}
	return std::shared_ptr<SyntaxNodeVariable>();
}

const size_t SyntaxNodeProcDefScope::GetCurrentPos() const {
	return m_base_pos + m_parameters.size() + m_arguments.size() +
	m_variables.size() + m_registers.size() + m_caches.size();
}

const size_t SyntaxNodeProcDefScope::GetParameterStackTopOffset(size_t index) const {
	size_t parametersCount = m_parameters.size();
	size_t count = 0;
	const size_t codePointer = 2;
	if (0 == m_outer->GetCurrentPos() % 2) {
		count = parametersCount - index + codePointer;
	}
	else {
		count = parametersCount - index + 1 + codePointer;
	}
	return count * 8;
}

const SyntaxNodeProcDef &SyntaxNodeProcDefScope::GetProcDef() const {
	return m_proc;
}

const DATA_TYPE_TYPE SyntaxNodeProcDefScope::GetProcRetType()const {
	return GetProcDef().GetDataType();
}
