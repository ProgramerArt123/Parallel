#include "GCC_X86_64.h"
#include "common.h"

const char *GCC_X86_64::registers[] = { "rdi", "rsi", "rdx", "rcx", "r8", "r9" };
size_t GCC_X86_64::registersCount = sizeof(registers) / sizeof(const char*);

GCC_X86_64 &GCC_X86_64::GetInstance() {
	static GCC_X86_64 instance;
	return instance;
}

void GCC_X86_64::PageHeaderGenerate(const char *fileName, std::ofstream &file) {
	file << '\t' << ".file \"" << fileName << "\"" << std::endl;
}

void GCC_X86_64::PageFooterGenerate(std::ofstream &file) {
	file << '\t' << ".ident	\"Parallelism Language: 1.0.0\"" << std::endl;
	file << '\t' << ".section	.note.GNU-Parallelism-stack, \"\", @progbits" << std::endl;
}

void GCC_X86_64::ConstGenerate(std::ofstream &file) {
	file << '\t' << ".section	.rodata" << std::endl;
}

void GCC_X86_64::StringGenerate(const char *content, std::stringstream& output) {
	consts << '\t' << ".string " << content << std::endl;
}

void GCC_X86_64::ProcStatementGenerate(const char *name, std::stringstream& output) {
	output << '\t' << ".globl " << name << std::endl;
	output << '\t' << ".type " << name << ", @function" << std::endl;
	output << name << ":" << std::endl;
}

void GCC_X86_64::ProcSizeGenerate(const char *name, std::stringstream& output) {
	output << '\t' << ".size " << name << ", .-" << name << std::endl;
}

void GCC_X86_64::ProcCallGenerate(const char *name, std::stringstream& output) {
	output << '\t' << "call" << '\t' << name << std::endl;
}

void GCC_X86_64::ProcStringArgmentGenerate(int NO, const char *dst, std::stringstream& output) {
	output << '\t' << "movq	$.LC" << NO
		<< ", " << dst << std::endl;
}