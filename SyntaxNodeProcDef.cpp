#include "SyntaxNodeProcDef.h"
#include "common.h"

SyntaxNodeProcDef::SyntaxNodeProcDef(SyntaxNodeScope &outter, const char *name):
	SyntaxNode(name),m_body(std::shared_ptr<SyntaxNodeScope>(new SyntaxNodeScope(outter, name))) {
	m_type = SYNTAX_NODE_TYPE_PROC_DEF;
}

SyntaxNodeProcDef::~SyntaxNodeProcDef() {

}

std::shared_ptr<SyntaxNodeScope> &SyntaxNodeProcDef::GetBody() {
	return m_body;
}

void SyntaxNodeProcDef::FindEffectives(std::shared_ptr<SyntaxNode> &self, std::set<std::shared_ptr<SyntaxNode>> &effectives) {
	effectives.insert(self);
	m_body->FindEffectives();
}

GENERATE_PARALLEL_RESULT SyntaxNodeProcDef::GenerateParallel(const std::shared_ptr<SyntaxNode> &self, Parallel &parallel) throw (std::exception) {
	m_body->GenerateParallel();
	return GENERATE_PARALLEL_RESULT_COMPLETED;
}

void SyntaxNodeProcDef::OutputInstructions(std::unique_ptr<Output>& output) {
	m_NO = output->GetFuncNO();
	OutputHead(output->GetStream());
	m_body->DefGenerate(output);
	OutputTail(output->GetStream());
}

void SyntaxNodeProcDef::OutputHead(std::stringstream& output) {
	
	PLATFORM.ProcStatementGenerateSerial(m_content.c_str(), output);

	output << ".LFB" << m_NO << ":" << std::endl;
	output << '\t' << ".cfi_startproc" << std::endl;
	output << '\t' << "pushq %rbp" << std::endl;

	output << '\t' << ".cfi_def_cfa_offset 16" << std::endl;

	output << '\t' << ".cfi_offset 6, -16" << std::endl;
	output << '\t' << "movq	%rsp, %rbp" << std::endl;
	output << '\t' << ".cfi_def_cfa_register 6" << std::endl;
}

void SyntaxNodeProcDef::OutputTail(std::stringstream& output) {
	output << '\t' << "leave" << std::endl;

	output << '\t' << ".cfi_def_cfa 7, 8" << std::endl;
	output << '\t' << "ret" << std::endl;
	output << '\t' << ".cfi_endproc" << std::endl;

	output << ".LFE" << m_NO << ":" << std::endl;

	PLATFORM.ProcSizeGenerateSerial(m_content.c_str(), output);

}

std::ostream &operator<<(std::ostream &out, SyntaxNodeProcDef &def) {
	out << *(SyntaxNode*)&def << std::endl;
	out << def.m_body;
	return out;
}