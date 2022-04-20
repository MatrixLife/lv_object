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
bool IFloatImpl::_find_type(const char* id, lv::IInterface** inst)
{
	bool retv = IFloat::IInterface::_find_type(id, inst);
	if((!retv) && (id != NULL))
	{
		IInterface* inst_result = NULL;
		if(::strcmp(id, "IFloat") == 0)
		{
			inst_result = static_cast<lv::IInterface*>(static_cast<IFloat*>(this));
			retv = true;
		}
		else if(::strcmp(id, lv::IID_IClonable) == 0)
		{
			inst_result = static_cast<lv::IInterface*>(static_cast<lv::IClonable*>(this));
			retv = true;
		}
		else if(::strcmp(id, lv::IID_IClonableT("IFloat")) == 0)
		{
			inst_result = static_cast<lv::IInterface*>(static_cast<lv::IClonableT<IFloat>*>(this));
			retv = true;
		}
		if(retv && inst && ((*inst) == NULL))
		{
			(*inst) = inst_result;
			(*inst)->_add_ref();
		}
	}
	return retv;
}
bool IFloatImpl::_clone(lv::IInterface** inst)
{
	bool retv = false;
	if(inst && ((*inst) == NULL))
	{
		IFloatImpl* inst_t = new IFloatImpl();
		inst_t->_Value = this->_Value;
		inst_t->_IRefs = 1;
		(*inst) = static_cast<lv::IInterface*>(static_cast<IFloat*>(inst_t));
		retv = true;
	}
	return retv;
}
bool IFloatImpl::_clone(IFloat** inst)
{
	bool retv = false;
	if(inst && ((*inst) == NULL))
	{
		IFloatImpl* inst_t = new IFloatImpl();
		inst_t->_Value = this->_Value;
		inst_t->_IRefs = 1;
		(*inst) = static_cast<IFloat*>(inst_t);
		retv = true;
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