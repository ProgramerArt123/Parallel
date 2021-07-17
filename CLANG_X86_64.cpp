#include "CLANG_X86_64.h"
#include "common.h"

const char *CLANG_X86_64::registers[] = { "rdi", "rsi", "rdx", "rcx", "r8", "r9" };
size_t CLANG_X86_64::registersCount = sizeof(registers) / sizeof(const char*);

CLANG_X86_64 &CLANG_X86_64::GetInstance() {
	static CLANG_X86_64 instance;
	return instance;
}

void CLANG_X86_64::PageHeaderGenerateSerial(const char *fileName, std::ofstream &file) {
	file << '\t' << ".section	__TEXT,__text,regular,pure_instructions" << std::endl;
	file << '\t' << ".macosx_version_min 10, 11" << std::endl;
}

void CLANG_X86_64::PageFooterGenerateSerial(std::ofstream &file) {
	file << '\t' << ".subsections_via_symbols" << std::endl;
}

void CLANG_X86_64::ConstGenerateSerial(std::ofstream &file) {
	file << '\t' << ".section	__TEXT,__cstring,cstring_literals" << std::endl;
}

void CLANG_X86_64::StringGenerateSerial(const char *content, std::stringstream& output) {
	consts << '\t' << ".asciz " << content << std::endl;
}

void CLANG_X86_64::ProcStatementGenerateSerial(const char *name, std::stringstream& output) {
	output << '\t' << ".globl _" << name << std::endl;
	output << '\t' << ".align	4, 0x90" << std::endl;
	output << '_' << name << ":" << std::endl;
}

void CLANG_X86_64::ProcSizeGenerateSerial(const char *name, std::stringstream& outputSerial) {
}

void CLANG_X86_64::ProcCallGenerateSerial(const char *name, std::stringstream& output) {
	output << '\t' << "call" << "\t_" << name << std::endl;
}

void CLANG_X86_64::ProcStringArgmentGenerateSerial(int NO, const char *dst, std::stringstream& output) {
	output << '\t' << "leaq	.LC" << NO
		<< "(%rip), " << dst << std::endl;
}