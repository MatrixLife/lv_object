#ifndef __LV_OBJECT_EXAMPLE_IFLOAT_MODERN_INTERFACE
#define __LV_OBJECT_EXAMPLE_IFLOAT_MODERN_INTERFACE
#include "lv_object.hpp"

struct IFloatModern: public lv::object
{
	virtual float value() = 0;
	virtual void value(const float) = 0;
};

#if (__cplusplus >= 201103L) || (_MSC_VER >= 1600)
typedef std::shared_ptr<IFloatModern> PFloatModern;
#else
typedef lv::handle_t<IFloatModern> PFloatModern;
#endif

PFloatModern IFloatModernCreateInstance();

#endif