#ifndef __CLANG_X86_64_H__
#define __CLANG_X86_64_H__

#include "Platform.h"

class CLANG_X86_64 : public Platform {
public:

	static const char *registers[];
	static size_t registersCount;

	static CLANG_X86_64 &GetInstance();

	void PageHeaderGenerate(const char *fileName, std::ofstream &file) override;
	void PageFooterGenerate(std::ofstream &file) override;
	void ConstGenerate(std::ofstream &file) override;
	void StringGenerate(const char *content, std::stringstream& output) override;
	void ProcStatementGenerate(const char *name, std::stringstream& output) override;
	void ProcSizeGenerate(const char *name, std::stringstream& output) override;
	void ProcCallGenerate(const char *name, std::stringstream& output) override;
	void ProcStringArgmentGenerate(int NO, const char *dst, std::stringstream& output) override;
};


#endif