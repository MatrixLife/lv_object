#include <conio.h>
#include "IFloat_api.hpp"
void main()
{
	IFloatHandle inst = IFloatCreateInstance();
	if(inst)// = "if(inst.valid())"
	{
		inst->value(123.456f);

		_cprintf("inst->_type_id() = %s.\r\n", inst->_type_id());
		_cprintf("inst->value() = %f.\r\n", inst->value());

		//inst.clear();//Can be ignored.
	}
	_getch();
};