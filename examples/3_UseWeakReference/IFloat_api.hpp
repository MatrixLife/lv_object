#ifndef __LV_OBJECT_EXAMPLE_IFLOAT_INTERFACE
#define __LV_OBJECT_EXAMPLE_IFLOAT_INTERFACE
#include "lv_interface.hpp"

struct IFloat: public lv::IInterface, public lv::IWeakReference
{
	virtual float value() = 0;
	virtual void value(const float) = 0;
};

bool IFloatCreateInstance(IFloat**);

#endif