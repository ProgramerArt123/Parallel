#ifndef __SOURCE_CODE_FILE_H__
#define __SOURCE_CODE_FILE_H__

#include <string>
#include <memory>

class Config;
class Lexical;
class SyntaxNodeScope;

class SourceCodeFile {
public:
	explicit SourceCodeFile(const char *fileName);
	virtual ~SourceCodeFile();

	void Parse() throw (std::string);

	void OutputFile(std::unique_ptr<Output>& output) throw (std::exception);

	static std::shared_ptr<DataType> ProduceDataType(const Lexical &lexical);
	std::stack<std::shared_ptr<SyntaxNodeScope>> m_scopes;
private:
	static bool SearchKeyWord(const std::string keyWord, const Lexical &lexical);
	const std::string m_file_name;
	std::shared_ptr<Config> m_config;
	SyntaxNodeScope m_implicit;
};

#endif