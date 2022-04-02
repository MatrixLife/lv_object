#include "IFloatModern_impl.hpp"
IFloatModernImpl::IFloatModernImpl(): _Value(0.0f)
{
}
IFloatModernImpl::~IFloatModernImpl()
{
}
const char* IFloatModernImpl::_type_id()
{
	return "IFloatModern";
}
float IFloatModernImpl::value()
{
	return this->_Value;
}
void IFloatModernImpl::value(const float value)
{
	this->_Value = value;
}
IFloatModernHandle IFloatModernCreateInstance()
{
	return IFloatModernHandle(new IFloatModernImpl());
}