#pragma once
#include "IFloatModern_api.h"
struct IFloatModernImpl: public IFloatModern
{
	float _Value;

	explicit IFloatModernImpl();
	virtual ~IFloatModernImpl();

//------------------------------------------------------------------------------
//Implement 'IFloatModern'.
//------------------------------------------------------------------------------
	float value();
	void value(const float);
};