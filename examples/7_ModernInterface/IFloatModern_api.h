#ifndef __LV_OBJECT_EXAMPLE_IFLOAT_MODERN_INTERFACE
#define __LV_OBJECT_EXAMPLE_IFLOAT_MODERN_INTERFACE
#include "lv_object_api.hpp"

struct IFloatModern: public lv::object
{
	virtual float value() = 0;
	virtual void value(const float) = 0;
};

#if (__cplusplus >= 201103L) || (_MSC_VER >= 1600)
#include <memory>
typedef std::shared_ptr<IFloatModern> IFloatModernHandle;
#else
typedef lv::handle_t<IFloatModern> IFloatModernHandle;
#endif

IFloatModernHandle IFloatModernCreateInstance();

#endif