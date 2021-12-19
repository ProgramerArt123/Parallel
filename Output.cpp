#include <fstream>
#include "common.h"
#include "Output.h"

Output::Output(const char *filePath):m_file_path(filePath){
}

Output::~Output() {
	std::ofstream file(m_file_path);
	if (file.is_open()) {
		PLATFORM.PageHeaderGenerateSerial(m_file_path.c_str(), file);
		const std::string &constContent = m_consts.str();
		if (!constContent.empty()) {
			PLATFORM.ConstGenerateSerial(file);
			file << constContent;
		}
		file << '\t' << ".text" << std::endl;
		file << m_output.str();
		PLATFORM.PageFooterGenerateSerial(file);
	}
	else {
		perror("output failed!\n");
	}
}


void Output::Add(const SyntaxNodeAdd &add) {
	ComputeOne(add, "addq");
}

void Output::Sub(const SyntaxNodeSub &sub) {
	ComputeOne(sub, "subq");
}

void Output::Mul(const SyntaxNodeMul &mul) {
	ComputeOne(mul, "imulq");
}

void Output::Div(const SyntaxNodeDiv &div) {
	ComputeTwo(div, "divq");
}

void Output::Mod(const SyntaxNodeMod &mod) {
	ComputeTwo(mod, "divq");
}

std::stringstream &Output::GetStream() {
	return m_output;
}

std::stringstream &Output::GetConstStream() {
	return m_consts;
}

unsigned int Output::GetConstNO() {
	return m_const_NO++;
}

unsigned int Output::GetFuncNO() {
	return m_func_NO++;
}

unsigned int Output::GetLabelNO() {
	return m_label_NO++;
}


void Output::ComputeTwo(const SyntaxNodeCompute &two, const char *instructions) {
	SYNTAX_NODE_TYPE leftType = two.m_children.front()->GetType();
	SYNTAX_NODE_TYPE rightType = two.m_children.back()->GetType();
	if (SYNTAX_NODE_TYPE_NUMBER == leftType &&
		SYNTAX_NODE_TYPE_NUMBER == rightType) {
		const int left = static_cast<SyntaxNodeNumber *>(two.m_children.front().get())->GetValue();
		const int right = static_cast<SyntaxNodeNumber *>(two.m_children.back().get())->GetValue();
		m_output << '\t' << "movq	$" << std::to_string(left + right) << ", %rax" << std::endl;
	}
	else {
		if (SYNTAX_NODE_TYPE_NUMBER == leftType) {
			const int rightOffset = static_cast<SyntaxNodeVariable *>(two.m_children.back().get())->GetScopeStackTopOffset();
			m_output << '\t' << "movq	-" << rightOffset << "(%rbp), %rax" << std::endl;
			const int left = static_cast<SyntaxNodeNumber *>(two.m_children.front().get())->GetValue();
			m_output << '\t' << "addq	$" << std::to_string(left) << ", %rax" << std::endl;
		}
		else if (SYNTAX_NODE_TYPE_NUMBER == rightType) {
			const int leftOffset = static_cast<SyntaxNodeVariable *>(two.m_children.front().get())->GetScopeStackTopOffset();
			m_output << '\t' << "movq	-" << leftOffset << "(%rbp), %rax" << std::endl;
			const int right = static_cast<SyntaxNodeNumber *>(two.m_children.back().get())->GetValue();
			m_output << '\t' << "addq	$" << std::to_string(right) << ", %rax" << std::endl;
		}
		else {
			const int leftOffset = static_cast<SyntaxNodeVariable *>(two.m_children.front().get())->GetScopeStackTopOffset();
			m_output << '\t' << "movq	-" << leftOffset << "(%rbp), %rax" << std::endl;
			m_output << '\t' << "xorl	%edx, %edx" << std::endl;
			const int rightOffset = static_cast<SyntaxNodeVariable *>(two.m_children.back().get())->GetScopeStackTopOffset();
			m_output << '\t' << instructions << "	-" << rightOffset << "(%rbp)" << std::endl;
		}
	}
}
