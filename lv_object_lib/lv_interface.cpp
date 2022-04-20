#include "lv_interface.hpp"
#include "lv_object.hpp"
#include <exception>
#include <string>
namespace lv
{
	const char* IID_IAssignableT(const char* type_name)
	{
		const char* retv = NULL;
		static std::string retv_inst;
		if(type_name && ::strlen(type_name))
		{
			retv_inst.clear();
			retv_inst.append("lv.IAssignableT");
			retv_inst.append(1, '<');
			retv_inst.append(type_name);
			retv_inst.append(1, '>');
			retv = retv_inst.c_str();
		}
		return retv;
	}
	const char* IID_IClonableT(const char* type_name)
	{
		const char* retv = NULL;
		static std::string retv_inst;
		if(type_name && ::strlen(type_name))
		{
			retv_inst.clear();
			retv_inst.append("lv.IClonableT");
			retv_inst.append(1, '<');
			retv_inst.append(type_name);
			retv_inst.append(1, '>');
			retv = retv_inst.c_str();
		}
		return retv;
	}
	bool IInterface::_find_type(const char* id, IInterface** inst)
	{
		bool retv = (id == NULL) || (::strlen(id) == 0) || (::strcmp(id, IID_IInterface) == 0);
		if(retv && inst && ((*inst) == NULL))
		{
			(*inst) = this;
			(*inst)->_add_ref();
		}
		return retv;
	}
}