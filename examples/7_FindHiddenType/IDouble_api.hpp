#ifndef __LV_OBJECT_EXAMPLE_IDOUBLE_INTERFACE
#define __LV_OBJECT_EXAMPLE_IDOUBLE_INTERFACE
#include "lv_interface.hpp"

struct __declspec(novtable) IDouble: public lv::IInterface
{
	virtual double value_hp() = 0;
	virtual double value_hp(const double) = 0;
};

#endif