#include "IFloat_impl.hpp"
IFloatImpl::IFloatImpl(): _ISafeRefs(0), _Value(0.0f)
{
}
IFloatImpl::~IFloatImpl()
{
	for(std::set<lv::IWeakReference**>::iterator i = this->_IWeakRefs.begin(), i_end = this->_IWeakRefs.end(); i != i_end; i++)
	{
		if((**i) == static_cast<lv::IWeakReference*>(this))
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
bool IFloatImpl::_add_ref_var(lv::IWeakReference** var_ptr)
{
	bool retv = false;
	if(var_ptr)
	{
		if((*var_ptr) == NULL)
		{
			(*var_ptr) = static_cast<lv::IWeakReference*>(this);
			this->_IWeakRefs.insert(var_ptr);
			retv = true;
		}
	}
	return retv;
}
void IFloatImpl::_release_var(lv::IWeakReference** var_ptr)
{
	if(var_ptr)
	{
		if((*var_ptr) == static_cast<lv::IWeakReference*>(this))
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