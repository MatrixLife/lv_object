#ifndef __LV_OBJECT_EXAMPLE_IFLOAT_IMPL
#define __LV_OBJECT_EXAMPLE_IFLOAT_IMPL
#include "IFloat_api.hpp"
#include <set>
struct IFloatImpl: public IFloat
{
	size_t _IRefs;
	float _Value;

	explicit IFloatImpl();
	virtual ~IFloatImpl();

//------------------------------------------------------------------------------
	void _add_ref();
	void _release();
	const char* _type_id() const;

//------------------------------------------------------------------------------
	bool assign(lv::IInterface*);
	bool assign_t(IFloat*);

//------------------------------------------------------------------------------
	float value();
	void value(const float);
};
#endif