#ifndef __LV_OBJECT_EXAMPLE_IFLOAT_IMPL
#define __LV_OBJECT_EXAMPLE_IFLOAT_IMPL
#include "IFloat_api.hpp"
struct IFloatImpl: public IFloat
{
	size_t _IRefs;
	float _Value;

	explicit IFloatImpl(): _IRefs(0), _Value(0.0f) {};
	virtual ~IFloatImpl(){};

//------------------------------------------------------------------------------
// Implement 'lv.IInterface'.
//------------------------------------------------------------------------------
	void _add_ref();
	void _release();
	const char* _type_id();

//------------------------------------------------------------------------------
// Implement 'IFloat'.
//------------------------------------------------------------------------------
	float value();
	float value(const float);
};
#endif