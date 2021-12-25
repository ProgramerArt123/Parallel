#include "SyntaxNodeReturn.h"
#include "common.h"

SyntaxNodeReturn::SyntaxNodeReturn(SyntaxNodeScope &outer):
	SyntaxNode(outer, "RETURN"){
	m_type = SYNTAX_NODE_TYPE_RETURN;
}

SyntaxNodeReturn::~SyntaxNodeReturn() {

}

void SyntaxNodeReturn::FindEffectives(std::shared_ptr<SyntaxNode> &self, std::set<std::shared_ptr<SyntaxNode>> &effectives) {
	effectives.insert(self);
}

void SyntaxNodeReturn::OutputInstructions(std::unique_ptr<Output>& output) {
	m_children.front()->OutputInstructions(output);
	output->GetStream() << '\t' << "movq	-" << 
		m_children.front()->GetResultPos() << "(%rbp), %rax" << std::endl;
	GetOuter()->PopCache();
	output->GetStream() << '\t' << "leave" << std::endl;
	output->GetStream() << '\t' << "ret" << std::endl;
}