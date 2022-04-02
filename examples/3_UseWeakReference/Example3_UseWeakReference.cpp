#include <conio.h>
#include "IFloat_api.hpp"
void main()
{
	IFloat* inst = NULL;
	if(IFloatCreateInstance(&inst))
	{
		inst->value(1234.5678f);

		lv::IWeakReference* weak_ptr = NULL;
		if(inst->_add_ref_var(&weak_ptr))
		{
			cprintf("weak_ptr->_type_id() = %s.\r\n", static_cast<IFloat*>(weak_ptr)->_type_id());
			cprintf("weak_ptr->value() = %f.\r\n", static_cast<IFloat*>(weak_ptr)->value());
		}

		inst->_release();
		inst = NULL;

		if(weak_ptr == NULL) cprintf("IFloat weak-reference is invalid.\r\n");
	}
	getch();
};