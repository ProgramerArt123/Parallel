#include "DataTypeInt.h"
DataTypeInt::DataTypeInt(bool isConst, bool isStatic, bool isVolatile)
	: DataType(isConst, isStatic, isVolatile) {
	m_type = DATA_TYPE_TYPE_INT;
}
DataTypeInt::~DataTypeInt(){
}