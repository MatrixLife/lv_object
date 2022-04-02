#pragma once
#include "IFloatModern_api.h"
struct IFloatModernImpl: public IFloatModern
{
	float _Value;

	explicit IFloatModernImpl();
	virtual ~IFloatModernImpl();

//------------------------------------------------------------------------------
//Implement 'lv.IObject'.
//------------------------------------------------------------------------------
	virtual const char* _type_id();

//------------------------------------------------------------------------------
//Implement 'IFloat'.
//------------------------------------------------------------------------------
	float value();
	void value(const float);
};