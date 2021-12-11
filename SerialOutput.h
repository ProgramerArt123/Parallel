#ifndef __SERIAL_OUTPUT_H__
#define __SERIAL_OUTPUT_H__

#include "Output.h"

class SerialOutput : public Output {
public:
	explicit SerialOutput(const char *filePath);

	void Add(const SyntaxNodeAdd *add) override;

	size_t Assignment(const SyntaxNodeAssignment *assign, std::unique_ptr<Output>& output) override;
};

#endif