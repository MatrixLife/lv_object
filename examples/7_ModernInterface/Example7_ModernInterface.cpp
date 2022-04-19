#include <conio.h>
#include "IFloatModern_api.h"
void main()
{
	PFloatModern inst = IFloatModernCreateInstance();
	if(inst)
	{
		inst->value(123.456f);

		_cprintf("inst->_type_id() = %s.\r\n", inst->_type_id());
		_cprintf("inst->value() = %f.\r\n", inst->value());

#if (__cplusplus >= 201103L) || (_MSC_VER >= 1600)
		//inst.reset();//Can be ignored.
#else
		//inst.clear();//Can be ignored.
#endif
	}
	_getch();
};