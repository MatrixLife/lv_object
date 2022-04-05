#ifndef __LV_OBJECT_EXAMPLE_IFLOAT_IMPL
#define __LV_OBJECT_EXAMPLE_IFLOAT_IMPL
#include "IFloat_api.hpp"
#include <set>
struct IFloatImpl: public IFloat
{
	size_t _ISafeRefs;
	std::set<lv::IWeakReference**> _IWeakRefs;
	float _Value;

	explicit IFloatImpl();
	virtual ~IFloatImpl();

//------------------------------------------------------------------------------
	void _add_ref();
	void _release();
	const char* _type_id() const;

//------------------------------------------------------------------------------
	bool _add_ref_var(lv::IWeakReference**);
	void _release_var(lv::IWeakReference**);

//------------------------------------------------------------------------------
	float value();
	void value(const float);
};
#endif