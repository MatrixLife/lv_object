#include "IFloatModern_impl.hpp"
IFloatModernImpl::IFloatModernImpl(): _Value(0.0f)
{
}
IFloatModernImpl::~IFloatModernImpl()
{
}
float IFloatModernImpl::value()
{
	return this->_Value;
}
void IFloatModernImpl::value(const float value)
{
	this->_Value = value;
}
IFloatModernSP IFloatModernCreateInstance()
{
	return IFloatModernSP(static_cast<IFloatModern*>(new IFloatModernImpl()));
}