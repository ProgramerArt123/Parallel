#ifndef __DATA_TYPE_DOUBLE_H__
#define __DATA_TYPE_DOUBLE_H__

#include "DataType.h"

class DataTypeDouble : public DataType {
public:
	explicit DataTypeDouble(bool isConst, bool isStatic, bool isVolatile);
	virtual ~DataTypeDouble();
};

#endif