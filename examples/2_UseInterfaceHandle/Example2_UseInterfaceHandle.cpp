#include <conio.h>
#include "IFloat_api.hpp"
void main()
{
	IFloatHandle inst = IFloatCreateInstance();
	if(inst)// = "if(inst.valid())"
	{
		inst->value(1234.5678f);

		cprintf("IFloat._type_id() = %s.\r\n", inst->_type_id());
		cprintf("IFloat.value() = %f.\r\n", inst->value());

		//inst.clear();//Can be ignored.
	}
	getch();
};