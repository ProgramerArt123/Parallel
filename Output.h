#ifndef __OUTPUT_H__
#define __OUTPUT_H__

#include <string>
#include <sstream>

class SyntaxNodeAdd;
class SyntaxNodeSub;
class SyntaxNodeAssignment;

class Output {
public:
	explicit Output(const char *filePath);
	virtual ~Output();

	std::stringstream &GetStream();

	virtual void Add(const SyntaxNodeAdd *add) = 0;
	//virtual void Sub(const SyntaxNodeSub *sub) = 0;
	virtual size_t Assignment(const SyntaxNodeAssignment *assign, std::unique_ptr<Output>& output) = 0;

protected:
	std::string m_file_path;
	std::stringstream m_output;
};

#endif