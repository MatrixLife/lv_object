#pragma once
#include "IFloatModern_api.h"
struct IFloatModernImpl: public IFloatModern
{
	float _Value;

	explicit IFloatModernImpl();
	virtual ~IFloatModernImpl();

//------------------------------------------------------------------------------
//Implement 'IFloat'.
//------------------------------------------------------------------------------
	const char* _type_id() const;
	float value();
	void value(const float);
};