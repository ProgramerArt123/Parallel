#include "DataType.h"

DataType::DataType(bool isConst, bool isStatic, bool isVolatile)
	: m_is_const(isConst), m_is_static(isStatic), m_is_volatile(isVolatile) {
}

DataType::~DataType(){
}
DATA_TYPE_TYPE DataType::GetType(){
	return m_type;
}
bool DataType::IsConst()const {
	return m_is_const;
}
bool DataType::IsStatic() const {
	return m_is_static;
}
bool DataType::IsVolatile() const {
	return m_is_volatile;
}