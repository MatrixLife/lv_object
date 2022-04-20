#ifndef __LV_OBJECT_EXAMPLE_IFLOAT_IMPL
#define __LV_OBJECT_EXAMPLE_IFLOAT_IMPL
#include "IFloat_api.hpp"
#include <set>
struct IFloatImpl: public IFloat
{
	size_t _ISafeRefs;
	std::set<lv::IWeakReferencable**> _IWeakRefs;
	float _Value;

	explicit IFloatImpl();
	virtual ~IFloatImpl();

//------------------------------------------------------------------------------
	void _add_ref();
	void _release();
	const char* _type_id();
	bool _find_type(const char*, lv::IInterface**);

//------------------------------------------------------------------------------
	bool _add_ref_var(lv::IWeakReferencable**);
	void _release_var(lv::IWeakReferencable**);

//------------------------------------------------------------------------------
	float value();
	void value(const float);
};
#endif