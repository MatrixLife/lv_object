#include <conio.h>
#include "IFloat_api.hpp"
void main()
{
	IFloat* test_inst = NULL;
	if(IFloatCreateInstance(&test_inst))
	{
		test_inst->value(1234.5678f);

		IFloatWP weak_inst(test_inst);
		if(weak_inst.valid())
		{
			cprintf("IFloat._type_id() = %s.\r\n", weak_inst->_type_id());
			cprintf("IFloat.value() = %f.\r\n", weak_inst->value());
		}

		test_inst->_release();
		test_inst = NULL;

		if(weak_inst.empty()) cprintf("IFloat weak-reference is invalid.\r\n");
	}
	getch();
};