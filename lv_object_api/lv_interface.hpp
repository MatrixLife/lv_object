#ifndef __LV_INTERFACE_FRAMEWORK
#define __LV_INTERFACE_FRAMEWORK
#include <stddef.h>
#include <string>
namespace lv
{
	struct IInterface;
	struct IWeakReferencable;
	struct IAssignable;
	struct IClonable;

	static const char* IID_IWeakReference = "lv.IWeakReferencable";
	static const char* IID_IAssignable = "lv.IAssignable";
	static const char* IID_IClonable = "lv.IClonable";

	const char* IID_IAssignableT(const char* type_name);
	const char* IID_IClonableT(const char* type_name);

	struct __declspec(novtable) IInterface
	{
		virtual void _add_ref() = 0;
		virtual void _release() = 0;
		virtual const char* _type_id() = 0;
		virtual bool _find_type(const char* id, IInterface** inst);
		template<typename IType> bool _find_type(const char* id, IType** inst)
		{
			bool retv = false;
			if(inst && ((*inst) == NULL))
			{
				IInterface* inst_base = NULL;
				if(this->_find_type(id, &inst_base) && inst_base)
				{
					if(static_cast<IType*>(inst_base))
					{
						(*inst) = static_cast<IType*>(inst_base);
						retv = true;
					}
					else
					{
						inst_base->_release();
						inst_base = NULL;
					}
				}
			}
			return retv;
		};
	};
	struct __declspec(novtable) IAssignable: public IInterface
	{
		virtual bool _assign(IInterface*) = 0;
	};
	struct __declspec(novtable) IClonable: public IInterface
	{
		virtual bool _clone(IInterface**) = 0;
	};
	struct __declspec(novtable) IWeakReferencable: public IInterface
	{
		virtual bool _add_ref_var(IWeakReferencable**) = 0;
		virtual void _release_var(IWeakReferencable**) = 0;
	};
	template<typename IType> struct __declspec(novtable) IAssignableT: public IInterface
	{
		virtual bool _assign(IType*) = 0;
	};
	template<typename IType> struct __declspec(novtable) IClonableT: public IInterface
	{
		virtual bool _clone(IType**) = 0;
	};
	template<typename IType> struct TInterfaceSafePtr
	{
	private:
		void* operator new(const size_t) throw();
		void operator delete(void*) throw();
		IInterface* ip;
	public:
		TInterfaceSafePtr(): ip(NULL) {};
		TInterfaceSafePtr(const TInterfaceSafePtr& other): ip(other.ip)
		{
			if(this->ip) this->ip->_add_ref();
		};
		TInterfaceSafePtr(IType* inst_t): ip(static_cast<IInterface*>(inst_t))
		{
			if(this->ip) this->ip->_add_ref();
		};
		~TInterfaceSafePtr()
		{
			if(this->ip) this->ip->_release();
		};
		size_t pointer() const
		{
			return (size_t)(this->ip);
		};
		bool empty() const
		{
			return (this->ip == NULL);
		};
		bool valid() const
		{
			return (this->ip != NULL);
		};
		void clear()
		{
			if(this->ip)
			{
				this->ip->_release();
				this->ip = NULL;
			}
		};
		operator bool() const
		{
			return (this->ip != NULL);
		};
		TInterfaceSafePtr& operator =(const TInterfaceSafePtr& other)
		{
			if(this->ip) this->ip->_release();
			if(other.ip) other.ip->_add_ref();
			this->ip = other.ip;
			return (*this);
		};
		bool operator ==(const TInterfaceSafePtr& other) const
		{
			return (this->ip == other.ip);
		};
		bool operator !=(const TInterfaceSafePtr& other) const
		{
			return (this->ip != other.ip);
		};
		bool operator <(const TInterfaceSafePtr& other) const
		{
			return ((size_t)(this->ip) < (size_t)(other.ip));
		};
		IType* operator ->() const { return dynamic_cast<IType*>(this->ip); };
		template<typename TOther> TInterfaceSafePtr<TOther> cast() const
		{
			TInterfaceSafePtr<TOther> retv;
			if(this->ip)
			{
				TOther* inst_t = dynamic_cast<TOther*>(this->ip);
				if(inst_t)
				{
					retv.ip = this->ip;
					retv.ip->_add_ref();
				}
			}
			return retv;
		};
	};
	template<typename IType> struct TInterfaceWeakPtr
	{
	private:
		void* operator new(const size_t) throw();
		void operator delete(void*) throw();
		IWeakReferencable* ip;
	public:
		TInterfaceWeakPtr(): ip(NULL) {};
		TInterfaceWeakPtr(const TInterfaceWeakPtr& other): ip(NULL)
		{
			if(other.ip) other.ip->_add_ref_var(&(this->ip));
		};
		TInterfaceWeakPtr(IType* inst_t): ip(NULL)
		{
			IWeakReferencable* inst = dynamic_cast<IWeakReferencable*>(inst_t);
			if(inst)
			{
				inst->_add_ref_var(&(this->ip));
			}
		};
		~TInterfaceWeakPtr()
		{
			if(this->ip) this->ip->_release_var(&(this->ip));
		};
		size_t pointer() const
		{
			return (size_t)(dynamic_cast<IType*>(this->ip));
		};
		bool empty() const
		{
			return (this->ip == NULL);
		};
		bool valid() const
		{
			return (this->ip != NULL);
		};
		void clear()
		{
			if(this->ip)
			{
				this->ip->_release_var(&(this->ip));
				this->ip = NULL;
			}
		};
		operator bool() const
		{
			return (this->ip != NULL);
		};
		TInterfaceWeakPtr& operator =(const TInterfaceWeakPtr& other)
		{
			if(this->ip) this->ip->_release_var(&(this->ip));
			if(other.ip) other.ip->_add_ref_var(&(this->ip));
			return (*this);
		};
		bool operator ==(const TInterfaceWeakPtr& other) const
		{
			return (this->ip == other.ip);
		};
		bool operator !=(const TInterfaceWeakPtr& other) const
		{
			return (this->ip != other.ip);
		};
		bool operator <(const TInterfaceWeakPtr& other) const
		{
			return (this->ip < other.ip);
		};
		IType* operator ->() const { return static_cast<IType*>(this->ip); };
		template<typename TOther> TInterfaceWeakPtr<TOther> cast() const
		{
			TInterfaceWeakPtr<TOther> retv;
			if(this->ip)
			{
				TOther* inst_t = dynamic_cast<TOther*>(this->ip);
				if(inst_t)
				{
					retv.ip = this->ip;
					retv.ip->_add_ref_var(&(retv.ip));
				}
			}
			return retv;
		};
	};
	struct IFactory: public IInterface
	{
		virtual short create(const char* iid, IInterface**) = 0;
		template<typename IType> TInterfaceSafePtr<IType> create(const char* iid, short* error_value)
		{
			TInterfaceSafePtr<IType> retv;
			if(iid)
			{
				IInterface* inst = NULL;
				short err_val = this->create(iid, &inst);
				if(err_val == 0)
				{
					retv = TInterfaceSafePtr<TInterface>(static_cast<IType*>(inst));
					if(retv.empty())
					{
						inst->_release();
						inst = NULL;
					}
				}
				if(error_value) (*error_value) = err_val;
			}
			return retv;
		};
	};
	typedef TInterfaceSafePtr<IFactory> HFactory;
}
#endif