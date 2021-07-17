#ifndef __PLATFORMA_H__
#define __PLATFORMA_H__

#include <sstream>
#include <fstream>

class Platform {
public:
	explicit Platform();
	virtual ~Platform();

	virtual void PageHeaderGenerateSerial(const char *fileName, std::ofstream &file) = 0;
	virtual void PageFooterGenerateSerial(std::ofstream &file) = 0;

	virtual void ConstGenerateSerial(std::ofstream &file) = 0;
	virtual void StringGenerateSerial(const char *content, std::stringstream& output) = 0;

	virtual void ProcStatementGenerateSerial(const char *name, std::stringstream& output) = 0;
	virtual void ProcSizeGenerateSerial(const char *name, std::stringstream& output) = 0;
	virtual void ProcCallGenerateSerial(const char *name, std::stringstream& output) = 0;
	virtual void ProcStringArgmentGenerateSerial(int NO, const char *dst, std::stringstream& output) = 0;
};

#endif