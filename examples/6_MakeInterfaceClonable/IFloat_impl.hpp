#ifndef __LV_OBJECT_EXAMPLE_IFLOAT_IMPL
#define __LV_OBJECT_EXAMPLE_IFLOAT_IMPL
#include "IFloat_api.hpp"
#include <set>
struct IFloatImpl: public IFloat, public lv::IClone, public lv::ICloneT<IFloat>
{
	size_t _IRefs;
	float _Value;

	explicit IFloatImpl();
	virtual ~IFloatImpl();

//------------------------------------------------------------------------------
	void _add_ref();
	void _release();
	const char* _type_id();
	bool _find_type(const char*, lv::IInterface**);

//------------------------------------------------------------------------------
	bool _clone(lv::IInterface**);

//------------------------------------------------------------------------------
	bool _clone(IFloat**);

//------------------------------------------------------------------------------
	float value();
	void value(const float);
};
#endif