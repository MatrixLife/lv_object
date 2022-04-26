#ifndef __LV_OBJECT_EXAMPLE_HPNUMBER_IMPL
#define __LV_OBJECT_EXAMPLE_HPNUMBER_IMPL
#include "IFloat_api.hpp"
#include "IDouble_api.hpp"
#include <string.h>
struct HighPrecisionNumber: public IFloat, public IDouble
{
	size_t _IRefs;
	double _Value;

	explicit HighPrecisionNumber(): _IRefs(0), _Value(0.0) {};
	virtual ~HighPrecisionNumber(){};

//------------------------------------------------------------------------------
// Implement 'lv.IInterface'.
//------------------------------------------------------------------------------
	void _add_ref();
	void _release();
	const char* _type_id();
	bool _find_type(const char* id, lv::IInterface** inst);

//------------------------------------------------------------------------------
// Implement 'IFloat'.
//------------------------------------------------------------------------------
	float value();
	float value(const float);

//------------------------------------------------------------------------------
// Implement 'IDouble'.
//------------------------------------------------------------------------------
	double value_hp();
	double value_hp(const double);
};
#endif