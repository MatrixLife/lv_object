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
	void* ReferenceType::operator new[](const size_t) throw()
	{
		throw std::exception();
	}
	void ReferenceType::operator delete[](void*) throw()
	{
		throw std::exception();
	}
	ReferenceType::ReferenceType(const ReferenceType&) throw()
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
}