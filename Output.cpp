#include <fstream>

#include "common.h"
#include "Output.h"

Output::Output(const char *filePath):m_file_path(filePath){
}

Output::~Output() {
	std::ofstream file(m_file_path);
	if (file.is_open()) {
		PLATFORM.PageHeaderGenerateSerial(m_file_path.c_str(), file);
		const std::string &constContent = consts.str();
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

std::stringstream &Output::GetStream() {
	return m_output;
}