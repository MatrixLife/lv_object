#include "lv_interface.hpp"
#include "lv_object.hpp"
#include <exception>
#include <string>
namespace lv
{
	object::object(){}
	object::~object(){}

	ValueType::ValueType(){}
	void* ValueType::operator new(size_t){ return NULL; }
	void ValueType::operator delete(void*){}

	_Object_Ref_Ctx::_Object_Ref_Ctx(object* inst): _inst(inst), _srefs(0) {}
	_Object_Ref_Ctx::~_Object_Ref_Ctx()
	{
		for(std::set<_Object_Ref_Ctx**>::iterator i = this->_wrefs.begin(), i_end = this->_wrefs.end(); i != i_end; i++)
		{
			(*(*i)) = NULL;
		}
		if(this->_inst)
		{
			delete this->_inst;
		}
	}
	void _Object_Ref_Ctx::_add_safe_ref()
	{
		this->_srefs+= 1;
	}
	void _Object_Ref_Ctx::_add_weak_ref(_Object_Ref_Ctx** pvar)
	{
		if(pvar && ((*pvar) == NULL))
		{
			this->_wrefs.insert(pvar);
			(*pvar) = this;
		}
	}
	void _Object_Ref_Ctx::_safe_release()
	{
		if(this->_srefs > 1)
		{
			this->_srefs-= 1;
		}
		else
		{
			delete this;
		};
	}
	void _Object_Ref_Ctx::_weak_release(_Object_Ref_Ctx** pvar)
	{
		if(pvar && ((*pvar) == this))
		{
			this->_wrefs.erase(pvar);
			(*pvar) = NULL;
		}
	}
	object* _Object_Ref_Ctx::inst() const
	{
		return this->_inst;
	}
}