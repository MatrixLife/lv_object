#include "IFloat_impl.hpp"
void IFloatImpl::_add_ref()
{
	this->_IRefs+= 1;
}
void IFloatImpl::_release()
{
	if(this->_IRefs > 1) this->_IRefs-= 1; else delete this;
}
const char* IFloatImpl::_type_id() const
{
	return "IFloat";
}
float IFloatImpl::value()
{
	return this->_Value;
}
void IFloatImpl::value(const float value)
{
	this->_Value = value;
}
bool IFloatCreateInstance(IFloat** inst)
{
	bool retv = false;
	if(inst)
	{
		if((*inst) == NULL)
		{
			(*inst) = static_cast<IFloat*>(new IFloatImpl());
			(*inst)->_add_ref();
			retv = true;
		}
	}
	return retv;
}