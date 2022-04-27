#ifndef __LV_OBJECT_EXAMPLE_IFLOAT_IMPL
#define __LV_OBJECT_EXAMPLE_IFLOAT_IMPL
#include "IFloat_api.hpp"
#include <set>
#include <string>
struct IFloatImpl: public IFloat, public lv::IAssign, public lv::IAssignT<IFloat>
{
	size_t _IRefs;
	float _Value;

	explicit IFloatImpl();
	virtual ~IFloatImpl();

//------------------------------------------------------------------------------
	void _add_ref();
	void _release();
	const char* _type_id();
	bool _find_type(const char*, IInterface**);

//------------------------------------------------------------------------------
	bool _assign(lv::IInterface*);

//------------------------------------------------------------------------------
	bool _assign(IFloat*);

//------------------------------------------------------------------------------
	float value();
	void value(const float);
};
#endif