#include <conio.h>
#include "IFloat_api.hpp"
void main()
{
	IFloat* inst = NULL;
	if(IFloatCreateInstance(&inst))
	{
		inst->value(123.456f);

		lv::IWeakReferencable* weak_ptr = NULL;
		if(inst->_add_ref_var(&weak_ptr))
		{
			_cprintf("weak_ptr->_type_id() = %s.\r\n", static_cast<IFloat*>(weak_ptr)->_type_id());
			_cprintf("weak_ptr->value() = %f.\r\n", static_cast<IFloat*>(weak_ptr)->value());
		}

		inst->_release();
		inst = NULL;

		if(weak_ptr == NULL) _cprintf("IFloat weak-reference is invalid.\r\n");
	}
	_getch();
};