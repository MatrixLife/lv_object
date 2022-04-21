#include <conio.h>
#include "IFloat_api.hpp"
void main()
{
	IFloat* inst = NULL;
	if(IFloatCreateInst(&inst))
	{
		inst->value(123.456f);

		_cprintf("inst->_type_id() = %s.\r\n", inst->_type_id());
		_cprintf("inst->value() = %f.\r\n", inst->value());

		inst->_release();
		inst = NULL;
	}
	_getch();
};