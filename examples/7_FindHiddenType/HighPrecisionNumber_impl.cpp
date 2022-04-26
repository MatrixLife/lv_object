#include "HighPrecisionNumber_impl.hpp"
void HighPrecisionNumber::_add_ref()
{
	this->_IRefs+= 1;
}
void HighPrecisionNumber::_release()
{
	if(this->_IRefs > 1) this->_IRefs-= 1; else delete this;
}
const char* HighPrecisionNumber::_type_id()
{
	return "IFloatHP";
}
bool HighPrecisionNumber::_find_type(const char* id, lv::IInterface** inst)
{
	bool retv = IInterface::_find_type(id, inst);
	if(IInterface::_find_type(id, inst))
	{
		retv = true;
	}
	else if(::strcmp(id, "IFloat") == 0)
	{
		if(inst && ((*inst) == NULL))
		{
			(*inst) = static_cast<lv::IInterface*>(static_cast<IFloat*>(this));
			(*inst)->_add_ref();
		}
		retv = true;
	}
	else if(::strcmp(id, "IDouble") == 0)
	{
		if(inst && ((*inst) == NULL))
		{
			(*inst) = static_cast<lv::IInterface*>(static_cast<IDouble*>(this));
			(*inst)->_add_ref();
		}
		retv = true;
	}
	return retv;
}
float HighPrecisionNumber::value()
{
	return (float)(this->_Value);
}
float HighPrecisionNumber::value(const float value)
{
	this->_Value = (double)value;
	return (double)(this->_Value);
}
double HighPrecisionNumber::value_hp()
{
	return this->_Value;
}
double HighPrecisionNumber::value_hp(const double value)
{
	this->_Value = value;
	return this->_Value;
}
bool IFloatCreateInst(IFloat** inst)
{
	bool retv = false;
	if(inst)
	{
		if((*inst) == NULL)
		{
			(*inst) = static_cast<IFloat*>(new HighPrecisionNumber());
			(*inst)->_add_ref();
			retv = true;
		}
	}
	return retv;
}