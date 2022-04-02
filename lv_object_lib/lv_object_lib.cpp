#include "lv_object_api.hpp"
#include <exception>
namespace lv
{
	const char* object::_type_id() const
	{
		return "lv.object";
	}
	void* ValueType::operator new(size_t) throw()
	{
		throw std::exception();
	}
	void ValueType::operator delete(void*) throw()
	{
		throw std::exception();
	}
	const char* ValueType::_type_id() const
	{
		return "lv.ValueType";
	}
	ReferenceType::ReferenceType(const ReferenceType&) throw()
	{
		throw std::exception();
	}
	void* ReferenceType::operator new[](const size_t) throw()
	{
		throw std::exception();
	}
	void ReferenceType::operator delete[](void*) throw()
	{
		throw std::exception();
	}
	ReferenceType& ReferenceType::operator =(const ReferenceType&) throw()
	{
		throw std::exception();
	}
	const char* ReferenceType::_type_id() const
	{
		return "lv.ReferenceType";
	}
#if(__cplusplus >= 199711L)
	IObject::IObject(const IObject&) throw()
	{
		throw std::exception();
	}
	void* IObject::operator new[](size_t size) throw()
	{
		throw std::exception();
	}
	void IObject::operator delete[](void* inst) throw()
	{
		throw std::exception();
	}
	IObject& IObject::operator =(const IObject&) throw()
	{
		throw std::exception();
	}
	const char* IObject::_type_id()
	{
		return "lv.IObject";
	}
#endif
}