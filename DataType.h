#ifndef __DATA_TYPE_H__
#define __DATA_TYPE_H__

#include "DataTypeType.h"
class DataType{
public:
	explicit DataType();
	virtual ~DataType();
	DATA_TYPE_TYPE GetType();
protected:
	DATA_TYPE_TYPE m_type = DATA_TYPE_TYPE_NONE;
};

#endif