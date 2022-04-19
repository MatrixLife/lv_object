#include "IFloat_impl.hpp"
IFloatImpl::IFloatImpl(): _IRefs(0), _Value(0.0f)
{
}
IFloatImpl::~IFloatImpl()
{
}
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
bool IFloatImpl::clone(lv::IInterface** result)
{
	bool retv = false;
	if(result && (*result) == NULL)
	{
		IFloatImpl* inst_t = new IFloatImpl();
		inst_t->_Value = this->_Value;
		inst_t->_IRefs = 1;
		(*result) = static_cast<lv::IInterface*>(inst_t);
		retv = true;
	}
	return retv;
}
bool IFloatImpl::clone_t(IFloat** result)
{
	return this->clone((lv::IInterface**)(result));
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
	if(inst && (*inst) == NULL)
	{
		(*inst) = static_cast<IFloat*>(new IFloatImpl());
		(*inst)->_add_ref();
		retv = true;
	}
	return retv;
}