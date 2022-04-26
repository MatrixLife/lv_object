#include <conio.h>
#include "IFloat_api.hpp"
#include "IDouble_api.hpp"
void main()
{
	IFloat* inst = NULL;
	if(IFloatCreateInst(&inst))
	{
		inst->value(123.456f);

		_cprintf("inst->_type_id() = %s.\r\n", inst->_type_id());
		_cprintf("inst->value() = %f.\r\n", inst->value());

		IDouble* inst_hp = NULL;
		if(inst->_find_type("IDouble", (lv::IInterface**)(&inst_hp)))
		{
			inst_hp->value_hp(123.456789);
			_cprintf("inst_hp->_type_id() = %s.\r\n", inst_hp->_type_id());
			_cprintf("inst_hp->value_hp() = %lf.\r\n", inst_hp->value_hp());

			inst_hp->_release();
			inst_hp = NULL;
		}

		inst->_release();
		inst = NULL;
	}
	_getch();
};