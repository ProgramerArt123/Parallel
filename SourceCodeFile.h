#ifndef __SOURCE_CODE_FILE_H__
#define __SOURCE_CODE_FILE_H__

#include <string>
#include <memory>

class SyntaxNodeScope;

class SourceCodeFile {
public:
	explicit SourceCodeFile(const char *fileName);
	virtual ~SourceCodeFile();

	void Parse() throw (std::string);

	void OutputFile(std::unique_ptr<Output>& output) throw (std::exception);

	std::stack<std::shared_ptr<SyntaxNodeScope>> m_scopes;
private:
	const std::string m_file_name;
};

#endif