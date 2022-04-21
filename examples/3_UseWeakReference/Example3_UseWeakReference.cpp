#include <conio.h>
#include "IFloat_api.hpp"
void main()
{
	IFloat* inst = NULL;
	if(IFloatCreateInst(&inst))
	{
		inst->value(123.456f);

		lv::IWeakReferencable* inst_wp = NULL;
		if(inst->_add_ref_var(&inst_wp))
		{
			_cprintf("inst_wp->_type_id() = %s.\r\n", static_cast<IFloat*>(inst_wp)->_type_id());
			_cprintf("inst_wp->value() = %f.\r\n", static_cast<IFloat*>(inst_wp)->value());
		}

		inst->_release();
		inst = NULL;

		if(inst_wp == NULL) _cprintf("IFloat weak-reference is invalid.\r\n");
	}
	_getch();
};