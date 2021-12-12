#ifndef __OUTPUT_H__
#define __OUTPUT_H__

#include <string>
#include <sstream>
#include <memory>

class SyntaxNodeAdd;
class SyntaxNodeSub;
class SyntaxNodeAssignment;
class SyntaxNode;
class SyntaxNodeCompute;
class Scope;
class Parallel;


class Output {
public:
	explicit Output(const char *filePath);
	virtual ~Output();

	std::stringstream &GetStream();
	std::stringstream &GetConstStream();

	void Add(const SyntaxNodeAdd &add);
	void Sub(const SyntaxNodeSub &sub);
	virtual size_t Assignment(const SyntaxNodeAssignment &assign, std::unique_ptr<Output>& output) = 0;

	virtual void ProcessScope(Scope &scope, std::unique_ptr<Output>& output) = 0;

	unsigned int GetConstNO();
	unsigned int GetFuncNO();
	unsigned int GetLabelNO();

protected:
	std::string m_file_path;
	std::stringstream m_output;
	std::stringstream m_consts;


private:
	virtual void ComputeOne(const SyntaxNodeCompute &one, const char *instructions) = 0;

private:
	unsigned int m_const_NO = 0;
	unsigned int m_func_NO = 0;
	unsigned int m_label_NO = 0;
};

#endif