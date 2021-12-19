#ifndef __PARALLE_OUTPUT_H__
#define __PARALLE_OUTPUT_H__

#include "Output.h"

typedef struct _ParallelElement ParallelElement;

class ParallelOutput : public Output {
public:
	explicit ParallelOutput(const char *filePath);

	void Assignment(const SyntaxNodeAssignment &assign, std::unique_ptr<Output>& output) override;

	void ProcessScope(SyntaxNodeScope &scope, std::unique_ptr<Output>& output) override;

	void ElementAdd(ParallelElement &element, std::unique_ptr<Output>& output);

	void ElementSub(ParallelElement &element, std::unique_ptr<Output>& output);

	void ElementMul(ParallelElement &element, std::unique_ptr<Output>& output);

	void ElementDiv(ParallelElement &element, std::unique_ptr<Output>& output);

	void ElementMod(ParallelElement &element, std::unique_ptr<Output>& output);
private:

	void ComputeOne(const SyntaxNodeCompute &one, const char *instructions) override;

};

#endif