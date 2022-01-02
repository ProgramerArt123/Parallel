#include "DataTypeInt.h"
DataTypeInt::DataTypeInt(bool isConst):
	DataType(isConst){
	m_type = DATA_TYPE_TYPE_INT;
}
DataTypeInt::~DataTypeInt(){
}