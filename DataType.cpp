#include "DataType.h"

DataType::DataType(bool isConst):m_is_const(isConst) {
}

DataType::~DataType(){
}
DATA_TYPE_TYPE DataType::GetType(){
	return m_type;
}
bool DataType::IsConst(){
	return m_is_const;
}