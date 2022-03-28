#include <conio.h>
#include "IFloat_api.hpp"
void main()
{
	IFloatHandle test_inst = IFloatCreateInstance();
	if(test_inst.valid())
	{
		test_inst->value(1234.5678f);

		cprintf("IFloat._type_id() = %s.\r\n", test_inst->_type_id());
		cprintf("IFloat.value() = %f.\r\n", test_inst->value());

		//test_inst.clear();//Can be ignored.
	}
	getch();
};