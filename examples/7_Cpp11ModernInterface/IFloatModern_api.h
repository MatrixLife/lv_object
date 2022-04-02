#pragma once
#if(__cplusplus >= 199711L)

#include <memory>
#include "lv_object_api.hpp"

struct IFloatModern: public lv::IObject
{
	virtual float value() = 0;
	virtual void value(const float) = 0;
};

typedef std::shared_ptr<IFloatModern> IFloatModernHandle;

IFloatModernHandle IFloatModernCreateInstance();

#endif