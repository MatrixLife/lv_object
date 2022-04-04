#include <conio.h>
#include "IFloat_api.hpp"
void main()
{
	IFloat* inst = NULL;
	if(IFloatCreateInstance(&inst))
	{
		inst->value(1234.5678f);

		IFloatWP weak_ref(inst);
		if(weak_ref)// = "if(weak_ref.valid())"
		{
			_cprintf("weak_ref->_type_id() = %s.\r\n", weak_ref->_type_id());
			_cprintf("weak_ref->value() = %f.\r\n", weak_ref->value());
		}

		inst->_release();
		inst = NULL;

		if(weak_ref.empty()) _cprintf("IFloat weak-reference is invalid.\r\n");
	}
	_getch();
};