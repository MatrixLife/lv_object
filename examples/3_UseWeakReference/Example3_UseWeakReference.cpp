#include <conio.h>
#include "IFloat_api.hpp"
void main()
{
	IFloat* test_inst = NULL;
	if(IFloatCreateInstance(&test_inst))
	{
		test_inst->value(1234.5678f);

		lv::IWeakReference* weak_inst = NULL;
		if(test_inst->_add_ref_var(&weak_inst))
		{
			cprintf("IFloat._type_id() = %s.\r\n", static_cast<IFloat*>(weak_inst)->_type_id());
			cprintf("IFloat.value() = %f.\r\n", static_cast<IFloat*>(weak_inst)->value());
		}

		test_inst->_release();
		test_inst = NULL;

		if(weak_inst == NULL) cprintf("IFloat weak-reference is invalid.\r\n");
	}
	getch();
};