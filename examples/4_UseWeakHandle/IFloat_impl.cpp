#include "IFloat_impl.hpp"
IFloatImpl::IFloatImpl(): _ISafeRefs(0), _Value(0.0f)
{
}
IFloatImpl::~IFloatImpl()
{
	for(std::set<lv::IWeakReferencable**>::iterator i = this->_IWeakRefs.begin(), i_end = this->_IWeakRefs.end(); i != i_end; i++)
	{
		if((**i) == static_cast<IFloat*>(this))
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
const char* IFloatImpl::_type_id() const
{
	return "IFloat";
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