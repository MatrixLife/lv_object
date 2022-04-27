#ifndef __LV_OBJECT_EXAMPLE_IFLOAT_INTERFACE
#define __LV_OBJECT_EXAMPLE_IFLOAT_INTERFACE
#include "lv_object.hpp"

struct IFloat: public lv::IWeakReference
{
	virtual float value() = 0;
	virtual void value(const float) = 0;
};

bool IFloatCreateInst(IFloat**);

#endif