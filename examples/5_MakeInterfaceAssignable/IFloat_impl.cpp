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
		else if(::strcmp(id, lv::IID_IAssignable) == 0)
		{
			inst_base = static_cast<lv::IInterface*>(static_cast<lv::IAssignable*>(this));
			retv = true;
		}
		else if(::strcmp(id, lv::IID_IAssignableT("IFloat")) == 0)
		{
			inst_base = static_cast<lv::IInterface*>(static_cast<lv::IAssignableT<IFloat>*>(this));
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
bool IFloatImpl::_assign(lv::IInterface* other)
{
	bool retv = false;
	if(other)
	{
		IFloatImpl* other_t = static_cast<IFloatImpl*>(static_cast<IFloat*>(other));
		if(other_t)
		{
			this->_Value = other_t->_Value;
			retv = true;
		}
	}
	return retv;
}
bool IFloatImpl::_assign(IFloat* other)
{
	return this->_assign(static_cast<lv::IInterface*>(other));
}
float IFloatImpl::value()
{
	return this->_Value;
}
void IFloatImpl::value(const float value)
{
	this->_Value = value;
}
bool IFloatCreateInst(IFloat** inst)
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