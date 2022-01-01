#include "SyntaxNodeFor.h"
#include "common.h"

SyntaxNodeFor::SyntaxNodeFor(SyntaxNodeScope &outter, int line):
	SyntaxNode(outter, line, "FOR"),
	m_whole(std::shared_ptr<SyntaxNodeScope>(new SyntaxNodeScope(outter,line, "FOR"))){
	m_type = SYNTAX_NODE_TYPE_FOR;
}

SyntaxNodeFor::~SyntaxNodeFor() {

}

void SyntaxNodeFor::FindEffectives(std::shared_ptr<SyntaxNode> &self, std::set<std::shared_ptr<SyntaxNode>> &effectives) {
	effectives.insert(self);
	m_whole->FindEffectives();
}

GENERATE_PARALLEL_RESULT SyntaxNodeFor::GenerateParallel(const std::shared_ptr<SyntaxNode> &self, Parallel &parallel) throw (std::exception) {
	m_whole->GenerateParallel();
	return GENERATE_PARALLEL_RESULT_COMPLETED;
}

std::shared_ptr<SyntaxNodeScope> &SyntaxNodeFor::GetWhole() {
	return m_whole;
}


void SyntaxNodeFor::OutputInstructions(std::unique_ptr<Output>& output) {
	unsigned int loopLabel0 = output->GetLabelNO();
	unsigned int loopLabel1 = output->GetLabelNO();
	output->GetStream() << '\t' << "movq    $1, %rcx" << std::endl;
	output->GetStream() << '\t' << "jmp	.LL" << std::to_string(loopLabel0) << std::endl;
	output->GetStream() << ".LL" << std::to_string(loopLabel1) << ":" << std::endl;
	output->GetStream() << '\t' << "addq    $1,  %rcx" << std::endl;
	output->GetStream() << ".LL" << std::to_string(loopLabel0) << ":" << std::endl;
	m_whole->LoopGenerate(output);
	output->GetStream() << '\t' << "setl   %al" << std::endl;
	output->GetStream() << '\t' << "testb   %al, %al" << std::endl;
	output->GetStream() << '\t' << "jne	.LL" << std::to_string(loopLabel1) << "" << std::endl;
}
