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
bool IFloatImpl::_find_type(const char* id, IInterface** inst)
{
	bool retv = IFloat::IInterface::_find_type(id, inst);
	if((!retv) && (id != NULL))
	{
		IInterface* inst_base = NULL;
		if(::strcmp(id, "IFloat") == 0)
		{
			inst_base = static_cast<lv::IInterface*>(static_cast<IFloat*>(this));
			retv = true;
		}
		if(retv && inst && ((*inst) == NULL))
		{
			(*inst) = inst_base;
			(*inst)->_add_ref();
		}
	}
	return retv;
}
float IFloatImpl::value()
{
	return this->_Value;
}
void IFloatImpl::value(const float value)
{
	this->_Value = value;
}
IFloatHandle IFloatCreateInstance()
{
	return IFloatHandle(static_cast<IFloat*>(new IFloatImpl()));
}