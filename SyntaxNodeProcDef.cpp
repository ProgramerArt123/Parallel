#include "SyntaxNodeProcDef.h"
#include "common.h"

SyntaxNodeProcDef::SyntaxNodeProcDef(const char *name, Scope &outter):
	SyntaxNode(name) {
	Scope *scope = new Scope(outter);
	m_body = std::shared_ptr<Scope>(scope);
	m_type = SYNTAX_NODE_TYPE_PROC_DEF;
}

SyntaxNodeProcDef::~SyntaxNodeProcDef() {

}

std::shared_ptr<Scope> &SyntaxNodeProcDef::GetBody() {
	return m_body;
}

void SyntaxNodeProcDef::FindEffectives(std::shared_ptr<SyntaxNode> &self, std::set<std::shared_ptr<SyntaxNode>> &effectives) {
	std::shared_ptr<SyntaxNode> body = m_body;
	SyntaxNode::FindEffectives(body, effectives);
}

void SyntaxNodeProcDef::generate(std::stringstream& output) {
	static unsigned int NO = 0;
	
	PLATFORM.ProcStatementGenerate(m_content.c_str(), output);
	
	output << ".LFB" << NO << ":" << std::endl;
	output << '\t' << ".cfi_startproc" << std::endl;
	output << '\t' << "pushq %rbp" << std::endl;
	
	output << '\t' << ".cfi_def_cfa_offset 16" << std::endl;

	output << '\t' << ".cfi_offset 6, -16" << std::endl;
	output << '\t' << "movq	%rsp, %rbp" << std::endl;
	output << '\t' << ".cfi_def_cfa_register 6" << std::endl;

	m_body->DefGenerate(output);
	
	output << '\t' << "leave" << std::endl;

	output << '\t' << ".cfi_def_cfa 7, 8" << std::endl;
	output << '\t' << "ret" << std::endl;
	output << '\t' << ".cfi_endproc" << std::endl;

	output << ".LFE" << NO << ":" << std::endl;

	PLATFORM.ProcSizeGenerate(m_content.c_str(), output);
	
	NO++;
}

std::ostream &operator<<(std::ostream &out, SyntaxNodeProcDef &def) {
	out << *(SyntaxNode*)&def << std::endl;
	out << def.m_body;
	return out;
}