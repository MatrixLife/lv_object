#include <conio.h>
#include "IFloatModern_api.h"
void main()
{
	IFloatModernHandle inst = IFloatModernCreateInstance();
	if(inst)
	{
		inst->value(1234.5678f);

		cprintf("inst->_type_id() = %s.\r\n", inst->_type_id());
		cprintf("inst->value() = %f.\r\n", inst->value());

		//inst.reset();//Can be ignored.
	}
	getch();
};