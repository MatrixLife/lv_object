#include <conio.h>
#include "IFloat_api.hpp"
void main()
{
	IFloat* inst1 = NULL;
	IFloat* inst2 = NULL;
	IFloat* inst3 = NULL;
	if(IFloatCreateInst(&inst1))
	{
		inst1->value(0.123f);

		_cprintf("inst1 = 0x%x, inst1->value() = %f.\r\n", inst1, inst1->value());
		_cprintf("inst2 = 0x%x.\r\n", inst2);
		_cprintf("inst3 = 0x%x.\r\n", inst3);

		lv::IClonable* inst_clone1 = NULL;
		if(inst1->_find_type<lv::IClonable>(lv::IID_IClonable, &inst_clone1))
		{
			inst_clone1->_clone((lv::IInterface**)(&inst2));
			inst_clone1->_release();
			inst_clone1 = NULL;
			_cprintf("After cloned to inst2, inst2 = 0x%x, inst2->value() = %f.\r\n", inst2, inst2->value());
		}

		lv::IClonableT<IFloat>* inst_clone2 = NULL;
		if(inst1->_find_type<lv::IClonableT<IFloat>>(lv::IID_IClonableT("IFloat"), &inst_clone2))
		{
			inst_clone2->_clone(&inst3);
			inst_clone2->_release();
			inst_clone2 = NULL;
			_cprintf("After cloned to inst3, inst3 = 0x%x, inst3->value() = %f.\r\n", inst3, inst3->value());
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