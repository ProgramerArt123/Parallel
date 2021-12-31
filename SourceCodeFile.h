#ifndef __SOURCE_CODE_FILE_H__
#define __SOURCE_CODE_FILE_H__

#include <string>
#include <memory>

class Config;
class Lexical;
class SyntaxNodeScope;
class SyntaxContent;

class SourceCodeFile {
public:
	explicit SourceCodeFile(const char *fileName);
	virtual ~SourceCodeFile();

	void Parse() throw (std::string);

	void OutputFile(std::unique_ptr<Output>& output) throw (std::exception);

private:
	const std::string m_file_name;
	std::shared_ptr<Config> m_config;
	std::unique_ptr<SyntaxContent> m_content;
};

#endif