#include "IFloat_impl.hpp"
IFloatImpl::IFloatImpl(): _ISafeRefs(0), _Value(0.0f)
{
}
IFloatImpl::~IFloatImpl()
{
	for(std::set<lv::IWeakReferencable**>::iterator i = this->_IWeakRefs.begin(), i_end = this->_IWeakRefs.end(); i != i_end; i++)
	{
		if((**i) == static_cast<lv::IWeakReferencable*>(this))
		{
			(**i) = NULL;
		}
	}
}
void IFloatImpl::_add_ref()
{
	this->_ISafeRefs+= 1;
}
void IFloatImpl::_release()
{
	if(this->_ISafeRefs > 1) this->_ISafeRefs-= 1; else delete this;
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
			inst_base = static_cast<lv::IInterface*>(this);
			retv = true;
		}
		else if(::strcmp(id, lv::IID_IWeakReference) == 0)
		{
			inst_base = static_cast<lv::IInterface*>(this);
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
bool IFloatImpl::_add_ref_var(lv::IWeakReferencable** var_ptr)
{
	bool retv = false;
	if(var_ptr)
	{
		if((*var_ptr) == NULL)
		{
			(*var_ptr) = static_cast<lv::IWeakReferencable*>(this);
			this->_IWeakRefs.insert(var_ptr);
			retv = true;
		}
	}
	return retv;
}
void IFloatImpl::_release_var(lv::IWeakReferencable** var_ptr)
{
	if(var_ptr)
	{
		if((*var_ptr) == static_cast<lv::IWeakReferencable*>(this))
		{
			(*var_ptr) = NULL;
			this->_IWeakRefs.erase(var_ptr);
		}
	}
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