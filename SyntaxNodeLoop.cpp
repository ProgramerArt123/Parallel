#include "SyntaxNodeLoop.h"
#include "common.h"

SyntaxNodeLoop::SyntaxNodeLoop(Scope &outter) :
	SyntaxNode(*static_cast<SyntaxNode *>(&outter), "LOOP"),
	m_body(std::shared_ptr<Scope>(new Scope(outter, "LOOP"))){
	m_type = SYNTAX_NODE_TYPE_LOOP;
}

SyntaxNodeLoop::~SyntaxNodeLoop() {

}

void SyntaxNodeLoop::FindEffectives(std::shared_ptr<SyntaxNode> &self, std::set<std::shared_ptr<SyntaxNode>> &effectives) {
	effectives.insert(self);
	m_body->FindEffectives();
}

GENERATE_PARALLEL_RESULT SyntaxNodeLoop::GenerateParallel(const std::shared_ptr<SyntaxNode> &self, Parallel &parallel) throw (std::exception) {
	m_body->GenerateParallel();
	return GENERATE_PARALLEL_RESULT_COMPLETED;
}

std::shared_ptr<Scope> &SyntaxNodeLoop::GetBody() {
	return m_body;
}


void SyntaxNodeLoop::OutputInstructions(std::unique_ptr<Output>& output) {
	unsigned int loopLabel0 = output->GetLabelNO();
	unsigned int loopLabel1 = output->GetLabelNO();
	output->GetStream() << '\t' << "movq    $1, %rcx" << std::endl;
	output->GetStream() << '\t' << "jmp	.LL" << std::to_string(loopLabel0) << std::endl;
	output->GetStream() << ".LL" << std::to_string(loopLabel1) << ":" << std::endl;
	output->GetStream() << '\t' << "addq    $1,  %rcx" << std::endl;
	output->GetStream() << ".LL" << std::to_string(loopLabel0) << ":" << std::endl;
	m_body->LoopGenerate(output);
	output->GetStream() << '\t' << "setl   %al" << std::endl;
	output->GetStream() << '\t' << "testb   %al, %al" << std::endl;
	output->GetStream() << '\t' << "jne	.LL" << std::to_string(loopLabel1) << "" << std::endl;
}
