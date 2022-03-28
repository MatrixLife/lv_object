#include <conio.h>
#include "IFloat_api.hpp"
void main()
{
	IFloat* test_inst1 = NULL;
	IFloat* test_inst2 = NULL;
	IFloat* test_inst3 = NULL;
	if(IFloatCreateInstance(&test_inst1) &&
		IFloatCreateInstance(&test_inst2) &&
		IFloatCreateInstance(&test_inst3))
	{
		test_inst1->value(0.123f);
		test_inst2->value(0.456f);
		test_inst3->value(0.789f);

		cprintf("inst1.value() = %f.\r\n", test_inst1->value());
		cprintf("inst2.value() = %f.\r\n", test_inst2->value());
		cprintf("inst3.value() = %f.\r\n", test_inst3->value());

		test_inst1->_assign(test_inst2);
		cprintf("After assign with inst2, inst1.value() = %f.\r\n", test_inst1->value());

		test_inst1->_assign_t(test_inst3);
		cprintf("After assign with inst3, inst1.value() = %f.\r\n", test_inst1->value());
	}
	if(test_inst1)
	{
		test_inst1->_release();
		test_inst1 = NULL;
	}
	if(test_inst2)
	{
		test_inst2->_release();
		test_inst2 = NULL;
	}
	if(test_inst3)
	{
		test_inst3->_release();
		test_inst3 = NULL;
	}
	getch();
};