#ifndef __GCC_X86_64_H__
#define __GCC_X86_64_H__

#include "Platform.h"

class GCC_X86_64 : public Platform {
public:

	static const char *registers[];
	static size_t registersCount;

	static GCC_X86_64 &GetInstance();

	void PageHeaderGenerateSerial(const char *fileName, std::ofstream &file) override;
	void PageFooterGenerateSerial(std::ofstream &file) override;
	void ConstGenerateSerial(std::ofstream &file) override;
	void StringGenerate(const char *content, std::unique_ptr<Output>& output) override;
	void ProcStatementGenerateSerial(const char *name, std::stringstream& output) override;
	void ProcSizeGenerateSerial(const char *name, std::stringstream& output) override;
	void ProcCallGenerateSerial(const char *name, std::stringstream& output) override;
	void ProcStringArgmentGenerateSerial(int NO, const char *dst, std::stringstream& output) override;
};

#endif