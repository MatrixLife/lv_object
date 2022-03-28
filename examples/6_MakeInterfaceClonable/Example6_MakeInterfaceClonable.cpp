#include <conio.h>
#include "IFloat_api.hpp"
void main()
{
	IFloat* test_inst1 = NULL;
	IFloat* test_inst2 = NULL;
	IFloat* test_inst3 = NULL;
	if(IFloatCreateInstance(&test_inst1))
	{
		test_inst1->value(0.123f);
		cprintf("inst1.value() = %f.\r\n", test_inst1->value());

		test_inst1->_clone((lv::IInterface**)(&test_inst2));
		cprintf("After clone to inst2, inst2.value() = %f.\r\n", test_inst2->value());

		test_inst1->_clone_t(&test_inst3);
		cprintf("After clone to inst3, inst3.value() = %f.\r\n", test_inst3->value());
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