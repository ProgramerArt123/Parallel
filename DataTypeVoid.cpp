#include "DataTypeVoid.h"
DataTypeVoid::DataTypeVoid(bool isConst, bool isStatic, bool isVolatile)
	: DataType(isConst, isStatic, isVolatile) {
	m_type = DATA_TYPE_TYPE_VOID;
}
DataTypeVoid::~DataTypeVoid(){
}