#ifndef __DATA_TYPE_INT_H__
#define __DATA_TYPE_INT_H__

#include "DataType.h"

class DataTypeInt : public DataType {
public:
	explicit DataTypeInt(bool isConst, bool isStatic, bool isVolatile);
	virtual ~DataTypeInt();
};

#endif