#include "lv_object.hpp"
#include <exception>
#include <string>
namespace lv
{
	object::object(){}
	object::~object(){}
	const char* object::_type_id() const { return "lv.object"; }

	factory::factory(){}
	factory::~factory(){}
	const char* factory::_type_id() const { return "lv.factory"; }
	short factory::create(const char* type_id, object** inst)
	{
		short retv = -1;
		if(type_id && inst && ((*inst) == NULL))
		{
			if(::strcmp(type_id, "lv.object") == 0)
			{
				(*inst) = new object();
				retv = 0;
			}
		}
		return retv;
	}

	ValueType::ValueType(){}
	ValueType::~ValueType(){}
	const char* ValueType::_type_id() const { return "lv.ValueType"; }
	void* ValueType::operator new(size_t) throw()
	{
		throw std::exception();
	}
	void ValueType::operator delete(void*) throw()
	{
		throw std::exception();
	}
}