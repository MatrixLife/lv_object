#include "IFloat_impl.hpp"
void IFloatImpl::_add_ref()
{
	this->_IRefs+= 1;
}
void IFloatImpl::_release()
{
	if(this->_IRefs > 1) this->_IRefs-= 1; else delete this;
}
const char* IFloatImpl::_type_id()
{
	return "IFloat";
}
float IFloatImpl::value()
{
	return this->_Value;
}
float IFloatImpl::value(const float value)
{
	this->_Value = value;
	return this->_Value;
}
IFloatSP IFloatCreateInst()
{
	return IFloatSP(static_cast<IFloat*>(new IFloatImpl()));
}