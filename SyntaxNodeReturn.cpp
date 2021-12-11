#include "SyntaxNodeReturn.h"
#include "common.h"

SyntaxNodeReturn::SyntaxNodeReturn():
	SyntaxNode("RETURN"){
	m_type = SYNTAX_NODE_TYPE_RETURN;
}

SyntaxNodeReturn::~SyntaxNodeReturn() {

}

void SyntaxNodeReturn::FindEffectives(std::shared_ptr<SyntaxNode> &self, std::set<std::shared_ptr<SyntaxNode>> &effectives) {
	effectives.insert(self);
}

void SyntaxNodeReturn::OutputInstructions(std::unique_ptr<Output>& output) {
	SYNTAX_NODE_TYPE value = m_children.front()->GetType();
	if (SYNTAX_NODE_TYPE_NUMBER == value) {
		const int intValue = static_cast<SyntaxNodeNumber *>(m_children.front().get())->GetValue();
		output->GetStream() << '\t' << "movq	$" << std::to_string(intValue) << ", %rax" << std::endl;
	}
	else {
		
	}
}