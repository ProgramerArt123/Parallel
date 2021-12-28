#ifndef __OUTPUT_H__
#define __OUTPUT_H__

#include <string>
#include <sstream>
#include <memory>

class SyntaxNodeAdd;
class SyntaxNodeSub;
class SyntaxNodeMul;
class SyntaxNodeDiv;
class SyntaxNodeMod;
class SyntaxNodeAssignment;
class SyntaxNode;
class SyntaxNodeCompute;
class SyntaxNodeScope;
class Parallel;


class Output {
public:
	explicit Output(const char *filePath);
	virtual ~Output();

	std::stringstream &GetStream();
	std::stringstream &GetConstStream();

	void Add(SyntaxNodeAdd &add, std::unique_ptr<Output>& output);
	void Sub(SyntaxNodeSub &sub, std::unique_ptr<Output>& output);
	void Mul(SyntaxNodeMul &mul, std::unique_ptr<Output>& output);
	void Div(SyntaxNodeDiv &div, std::unique_ptr<Output>& output);
	void Mod(SyntaxNodeMod &mod, std::unique_ptr<Output>& output);
	virtual void Assignment(SyntaxNodeAssignment &assign, std::unique_ptr<Output>& output) = 0;

	virtual void ProcessScope(SyntaxNodeScope &scope, std::unique_ptr<Output>& output) = 0;

	unsigned int GetConstNO();
	unsigned int GetFuncNO();
	unsigned int GetLabelNO();

protected:
	std::string m_file_path;
	std::stringstream m_output;
	std::stringstream m_consts;

private:
	virtual void ComputeOne(const SyntaxNodeCompute &one, const char *instructions, std::unique_ptr<Output>& output) = 0;
	void ComputeTwo(const SyntaxNodeCompute &two, const char *instructions, std::unique_ptr<Output>& output);
private:
	unsigned int m_const_NO = 0;
	unsigned int m_func_NO = 0;
	unsigned int m_label_NO = 0;
};

#endif