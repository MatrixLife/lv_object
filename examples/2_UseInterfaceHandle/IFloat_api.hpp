#ifndef __LV_OBJECT_EXAMPLE_IFLOAT_INTERFACE
#define __LV_OBJECT_EXAMPLE_IFLOAT_INTERFACE
#include "lv_object_api.hpp"

struct IFloat: public lv::IInterface
{
	virtual float value() = 0;
	virtual void value(const float) = 0;
};

typedef lv::TInterfaceHandle<IFloat> IFloatHandle;

IFloatHandle IFloatCreateInstance();

#endif