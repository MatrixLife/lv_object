#include <conio.h>
#include "IFloat_api.hpp"
void main()
{
	IFloat* inst1 = NULL;
	IFloat* inst2 = NULL;
	IFloat* inst3 = NULL;
	if(IFloatCreateInstance(&inst1) &&
		IFloatCreateInstance(&inst2) &&
		IFloatCreateInstance(&inst3))
	{
		inst1->value(0.123f);
		inst2->value(0.456f);
		inst3->value(0.789f);

		_cprintf("inst1->value() = %f.\r\n", inst1->value());
		_cprintf("inst2->value() = %f.\r\n", inst2->value());
		_cprintf("inst3->value() = %f.\r\n", inst3->value());

		inst1->_assign(static_cast<lv::IInterface*>(inst2));
		_cprintf("After assigned from inst2, inst1->value() = %f.\r\n", inst1->value());

		inst1->_assign_t(inst3);
		_cprintf("After assigned from inst3, inst1->value() = %f.\r\n", inst1->value());
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
	_getch();
};