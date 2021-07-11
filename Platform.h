#ifndef __PLATFORMA_H__
#define __PLATFORMA_H__

#include <sstream>
#include <fstream>

class Platform {
public:
	explicit Platform();
	virtual ~Platform();

	virtual void PageHeaderGenerate(const char *fileName, std::ofstream &file) = 0;
	virtual void PageFooterGenerate(std::ofstream &file) = 0;

	virtual void ConstGenerate(std::ofstream &file) = 0;
	virtual void StringGenerate(const char *content, std::stringstream& output) = 0;

	virtual void ProcStatementGenerate(const char *name, std::stringstream& output) = 0;
	virtual void ProcSizeGenerate(const char *name, std::stringstream& output) = 0;
	virtual void ProcCallGenerate(const char *name, std::stringstream& output) = 0;
	virtual void ProcStringArgmentGenerate(int NO, const char *dst, std::stringstream& output) = 0;
};

#endif