#include "IFloatModern_impl.hpp"
IFloatModernImpl::IFloatModernImpl(): _Value(0.0f)
{
}
IFloatModernImpl::~IFloatModernImpl()
{
}
const char* IFloatModernImpl::_type_id() const
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
PFloatModern IFloatModernCreateInstance()
{
	return PFloatModern(new IFloatModernImpl());
}