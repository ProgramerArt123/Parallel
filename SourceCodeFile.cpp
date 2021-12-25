void yyerror(char* e);

#include "lex.yy.c"
#include "y.tab.c"

#include "SyntaxNodeScope.h"
#include "SourceCodeFile.h"

void yyerror(char* e) {
	throw std::string("Error=>line:") +
		std::to_string(yyget_lineno()) + "," + e;
};

SourceCodeFile::SourceCodeFile(const char *fileName):
	m_file_name(fileName){
	m_scopes.push(std::shared_ptr<SyntaxNodeScope>(new SyntaxNodeScope));

}

SourceCodeFile::~SourceCodeFile() {
	m_scopes.pop();
}

void SourceCodeFile::Parse() throw (std::string) {
	FILE *in = fopen(m_file_name.c_str(), "r");
	if (in) {
		yyin = in;
		yyparse();
		fclose(in);
	}
	else {
		throw "Error:" + m_file_name + " Open Failed!";
	}
}

void SourceCodeFile::OutputFile(std::unique_ptr<Output>& output) throw (std::exception) {
	m_scopes.top()->OutputFile(output);
}