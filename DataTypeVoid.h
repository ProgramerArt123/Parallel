#ifndef __DATA_TYPE_VOID_H__
#define __DATA_TYPE_VOID_H__

#include "DataType.h"

class DataTypeVoid : public DataType {
public:
	explicit DataTypeVoid(bool isConst, bool isStatic, bool isVolatile);
	virtual ~DataTypeVoid();
};

#endif