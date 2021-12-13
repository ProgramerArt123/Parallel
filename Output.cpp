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
	ComputeOne(mul, "mulq");
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