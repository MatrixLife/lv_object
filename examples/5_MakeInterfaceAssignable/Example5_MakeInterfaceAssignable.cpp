#include <conio.h>
#include "IFloat_api.hpp"
void main()
{
	IFloat* inst1 = NULL;
	IFloat* inst2 = NULL;
	IFloat* inst3 = NULL;
	if(IFloatCreateInstance(&inst1) && IFloatCreateInstance(&inst2) && IFloatCreateInstance(&inst3))
	{
		inst1->value(0.123f);
		inst2->value(0.456f);
		inst3->value(0.789f);

		_cprintf("inst1 = 0x%x, inst1->value() = %f.\r\n", inst1, inst1->value());
		_cprintf("inst2 = 0x%x, inst2->value() = %f.\r\n", inst2, inst2->value());
		_cprintf("inst3 = 0x%x, inst3->value() = %f.\r\n", inst3, inst3->value());

		lv::IAssignable* inst_assign1 = NULL;
		if(inst1->_find_type<lv::IAssignable>("lv.IAssignable", &inst_assign1))
		{
			inst_assign1->_assign(static_cast<lv::IInterface*>(inst2));
			inst_assign1->_release();
			inst_assign1 = NULL;
			_cprintf("After assigned by inst2, inst1->value() = %f.\r\n", inst1->value());
		}

		lv::IAssignableT<IFloat>* inst_assign2 = NULL;
		if(inst1->_find_type<lv::IAssignableT<IFloat>>("lv.IAssignableT<IFloat>", &inst_assign2))
		{
			inst_assign2->_assign(inst3);
			inst_assign2->_release();
			inst_assign2 = NULL;
			_cprintf("After assigned by inst3, inst1->value() = %f.\r\n", inst1->value());
		}
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