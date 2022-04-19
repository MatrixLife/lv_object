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
bool IFloatImpl::assign(lv::IInterface* other)
{
	bool retv = false;
	if(other)
	{
		IFloatImpl* other_t = static_cast<IFloatImpl*>(other);
		if(other_t)
		{
			this->_Value = other_t->_Value;
			retv = true;
		}
	}
	return retv;
}
bool IFloatImpl::assign_t(IFloat* other)
{
	return this->assign(static_cast<lv::IInterface*>(other));
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