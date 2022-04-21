#include <conio.h>
#include "IFloat_api.hpp"
void main()
{
	IFloatSP inst_sp = IFloatCreateInst();
	if(inst_sp)// = "if(inst_sp.valid())"
	{
		inst_sp->value(123.456f);

		_cprintf("inst->_type_id() = %s.\r\n", inst_sp->_type_id());
		_cprintf("inst->value() = %f.\r\n", inst_sp->value());

		//inst_sp.clear();//Can be ignored.
	}
	_getch();
};