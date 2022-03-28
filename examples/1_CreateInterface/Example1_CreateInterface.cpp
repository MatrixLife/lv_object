#include <conio.h>
#include "IFloat_api.hpp"
void main()
{
	IFloat* test_inst = NULL;
	if(IFloatCreateInstance(&test_inst))
	{
		test_inst->value(1234.5678f);

		cprintf("IFloat.type_id() = %s.\r\n", test_inst->_type_id());
		cprintf("IFloat.value() = %f.\r\n", test_inst->value());

		test_inst->_release();
		test_inst = NULL;
	}
	getch();
};