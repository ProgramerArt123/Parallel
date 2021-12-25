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


void Output::Add(SyntaxNodeAdd &add, std::unique_ptr<Output>& output) {
	ComputeOne(add, "addq", output);
	output->GetStream() << '\t' << "movq	%rax, -" << 
		add.SetResultPos(add.GetOuter()->PushCache()) << "(%rbp)" << std::endl;
}

void Output::Sub(SyntaxNodeSub &sub, std::unique_ptr<Output>& output) {
	ComputeOne(sub, "subq", output);
	output->GetStream() << '\t' << "movq	%rax, -" << 
		sub.SetResultPos(sub.GetOuter()->PushCache()) << "(%rbp)" << std::endl;
}

void Output::Mul(SyntaxNodeMul &mul, std::unique_ptr<Output>& output) {
	ComputeOne(mul, "imulq", output);
	output->GetStream() << '\t' << "movq	%rax, -" << 
		mul.SetResultPos(mul.GetOuter()->PushCache()) << "(%rbp)" << std::endl;
}

void Output::Div(SyntaxNodeDiv &div, std::unique_ptr<Output>& output) {
	ComputeTwo(div, "divq", output);
	output->GetStream() << '\t' << "movq	%rax, -" << 
		div.SetResultPos(div.GetOuter()->PushCache()) << "(%rbp)" << std::endl;
}

void Output::Mod(SyntaxNodeMod &mod, std::unique_ptr<Output>& output) {
	ComputeTwo(mod, "divq", output);
	output->GetStream() << '\t' << "movq	%rdx, -" << 
		mod.SetResultPos(mod.GetOuter()->PushCache()) << "(%rbp)" << std::endl;
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


void Output::ComputeTwo(const SyntaxNodeCompute &two, const char *instructions, std::unique_ptr<Output>& output) {
	two.m_children.front()->OutputInstructions(output);
	two.m_children.back()->OutputInstructions(output);
	m_output << '\t' << "xorl	%edx, %edx" << std::endl;
	m_output << '\t' << "movq	-" << 
		two.m_children.front()->GetResultPos() << "(%rbp), %rax" << std::endl;
	two.GetOuter()->PopCache();
	m_output << '\t' << instructions << "	-" << 
		two.m_children.back()->GetResultPos() << "(%rbp)" << std::endl;
	two.GetOuter()->PopCache();
}
