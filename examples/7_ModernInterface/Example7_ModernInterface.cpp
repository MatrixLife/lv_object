#include <conio.h>
#include "IFloatModern_api.h"
void main()
{
	IFloatModernSP inst_sp = IFloatModernCreateInstance();
	IFloatModernWP inst_wp(inst_sp);
	if(inst_sp)
	{
		inst_sp->value(0.123f);
		_cprintf("inst_sp->value() = %f.\r\n", inst_sp->value());

#if (__cplusplus >= 201103L) || (_MSC_VER >= 1600)
		inst_wp.lock()->value(0.456f);
		_cprintf("inst_wp->value() = %f.\r\n", inst_wp.lock()->value());

		inst_sp.reset();
		if(inst_wp.expired()) _cprintf("inst_wp is invalid now.\r\n");
#else
		inst_wp->value(0.456f);
		_cprintf("inst_wp->value() = %f.\r\n", inst_wp->value());

		inst_sp.clear();
		if(inst_wp.empty()) _cprintf("inst_wp is invalid now.\r\n");
#endif
	}
	_getch();
};