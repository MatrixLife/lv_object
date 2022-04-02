#include <conio.h>
#include "IFloat_api.hpp"
void main()
{
	IFloat* inst = NULL;
	if(IFloatCreateInstance(&inst))
	{
		inst->value(1234.5678f);

		cprintf("inst->type_id() = %s.\r\n", inst->_type_id());
		cprintf("inst->value() = %f.\r\n", inst->value());

		inst->_release();
		inst = NULL;
	}
	getch();
};