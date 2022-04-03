#pragma once
#if (__cplusplus >= 201103L) || (_MSC_VER >= 1600)
#include "lv_object_api.hpp"

struct IFloatModern: public lv::IObject
{
	virtual float value() = 0;
	virtual void value(const float) = 0;
};

typedef std::shared_ptr<IFloatModern> IFloatModernHandle;

IFloatModernHandle IFloatModernCreateInstance();

#endif