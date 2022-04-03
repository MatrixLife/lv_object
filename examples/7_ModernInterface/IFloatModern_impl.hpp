#pragma once
#include "IFloatModern_api.h"
struct IFloatModernImpl: public IFloatModern
{
	float _Value;

	explicit IFloatModernImpl();
	virtual ~IFloatModernImpl();

//------------------------------------------------------------------------------
//Implement 'lv.object'.
//------------------------------------------------------------------------------
	virtual const char* _type_id() const;

//------------------------------------------------------------------------------
//Implement 'IFloat'.
//------------------------------------------------------------------------------
	float value();
	void value(const float);
};