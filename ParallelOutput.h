#ifndef __PARALLE_OUTPUT_H__
#define __PARALLE_OUTPUT_H__

#include "Output.h"

class ParallelOutput : public Output {
public:
	explicit ParallelOutput(const char *filePath);

	void Add(const SyntaxNodeAdd *add) override;

	size_t Assignment(const SyntaxNodeAssignment *assign, std::unique_ptr<Output>& output) override;
};

#endif