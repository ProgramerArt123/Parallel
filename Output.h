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

	void Add(const SyntaxNodeAdd &add);
	void Sub(const SyntaxNodeSub &sub);
	void Mul(const SyntaxNodeMul &mul);
	void Div(const SyntaxNodeDiv &div);
	void Mod(const SyntaxNodeMod &mod);
	virtual void Assignment(const SyntaxNodeAssignment &assign, std::unique_ptr<Output>& output) = 0;

	virtual void ProcessScope(SyntaxNodeScope &scope, std::unique_ptr<Output>& output) = 0;

	unsigned int GetConstNO();
	unsigned int GetFuncNO();
	unsigned int GetLabelNO();

protected:
	std::string m_file_path;
	std::stringstream m_output;
	std::stringstream m_consts;

private:
	virtual void ComputeOne(const SyntaxNodeCompute &one, const char *instructions) = 0;
	void ComputeTwo(const SyntaxNodeCompute &two, const char *instructions);
private:
	unsigned int m_const_NO = 0;
	unsigned int m_func_NO = 0;
	unsigned int m_label_NO = 0;
};

#endif