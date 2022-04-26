#ifndef __LV_OBJECT_EXAMPLE_IFLOAT_INTERFACE
#define __LV_OBJECT_EXAMPLE_IFLOAT_INTERFACE
#include "lv_interface.hpp"

struct __declspec(novtable) IFloat: public lv::IInterface
{
	virtual float value() = 0;
	virtual float value(const float) = 0;
};

bool IFloatCreateInst(IFloat**);

#endif