#include <conio.h>
#include "IFloat_api.hpp"
void main()
{
	IFloat* inst1 = NULL;
	IFloat* inst2 = NULL;
	IFloat* inst3 = NULL;
	if(IFloatCreateInstance(&inst1))
	{
		inst1->value(0.123f);
		cprintf("inst1.value() = %f.\r\n", inst1->value());

		inst1->_clone((lv::IInterface**)(&inst2));
		cprintf("After cloned to inst2, inst2.value() = %f.\r\n", inst2->value());

		inst1->_clone_t(&inst3);
		cprintf("After cloned to inst3, inst3.value() = %f.\r\n", inst3->value());
	}
	if(inst1)
	{
		inst1->_release();
		inst1 = NULL;
	}
	if(inst2)
	{
		inst2->_release();
		inst2 = NULL;
	}
	if(inst3)
	{
		inst3->_release();
		inst3 = NULL;
	}
	getch();
};