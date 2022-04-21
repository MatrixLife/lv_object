#include <conio.h>
#include "IFloat_api.hpp"
void main()
{
	IFloat* inst = NULL;
	if(IFloatCreateInst(&inst))
	{
		inst->value(123.456f);

		IFloatWP inst_wp(inst);
		if(inst_wp)// = "if(inst_wp.valid())"
		{
			_cprintf("inst_wp->_type_id() = %s.\r\n", inst_wp->_type_id());
			_cprintf("inst_wp->value() = %f.\r\n", inst_wp->value());
		}

		inst->_release();
		inst = NULL;

		if(inst_wp.empty()) _cprintf("IFloat weak-reference is invalid.\r\n");
	}
	_getch();
};