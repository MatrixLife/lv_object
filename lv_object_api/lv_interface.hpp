#ifndef __LV_INTERFACE_FRAMEWORK
#define __LV_INTERFACE_FRAMEWORK
#include <stddef.h>
#include <string>
namespace lv
{
	struct IInterface;
	struct IWeakReference;
	struct IAssignable;
	struct IClonable;

	static const char* IID_IInterface = "lv.IInterface";
	static const char* IID_IWeakReference = "lv.IWeakReference";
	static const char* IID_IAssignable = "lv.IAssignable";
	static const char* IID_IClonable = "lv.IClonable";

	const char* IID_IAssignableT(const char* type_name);
	const char* IID_IClonableT(const char* type_name);

	struct IInterface
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
	struct IWeakReference
	{
		virtual bool _add_ref_var(IWeakReference**) = 0;
		virtual void _release_var(IWeakReference**) = 0;
	};
	struct IAssignable: public IInterface
	{
		virtual bool _assign(IInterface*) = 0;
	};
	struct IClonable: public IInterface
	{
		virtual bool _clone(IInterface**) = 0;
	};
	template<typename IType> struct IAssignableT: public IInterface
	{
		virtual bool _assign(IType*) = 0;
	};
	template<typename IType> struct IClonableT: public IInterface
	{
		virtual bool _clone(IType**) = 0;
	};
	template<typename IType> struct TInterfaceHandle
	{
	private:
		void* operator new(const size_t) throw();
		void operator delete(void*) throw();
		IInterface* ip;
	public:
		TInterfaceHandle(): ip(NULL) {};
		TInterfaceHandle(const TInterfaceHandle& other): ip(other.ip)
		{
			if(this->ip) this->ip->_add_ref();
		};
		TInterfaceHandle(IType* inst_t): ip(static_cast<IInterface*>(inst_t))
		{
			if(this->ip) this->ip->_add_ref();
		};
		~TInterfaceHandle()
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
		TInterfaceHandle& operator =(const TInterfaceHandle& other)
		{
			if(this->ip) this->ip->_release();
			if(other.ip) other.ip->_add_ref();
			this->ip = other.ip;
			return (*this);
		};
		bool operator ==(const TInterfaceHandle& other) const
		{
			return (this->ip == other.ip);
		};
		bool operator !=(const TInterfaceHandle& other) const
		{
			return (this->ip != other.ip);
		};
		bool operator <(const TInterfaceHandle& other) const
		{
			return ((size_t)(this->ip) < (size_t)(other.ip));
		};
		IType* operator ->() const { return dynamic_cast<IType*>(this->ip); };
		template<typename TOther> TInterfaceHandle<TOther> cast() const
		{
			TInterfaceHandle<TOther> retv;
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
	template<typename IType> struct TWeakReferenceHandle
	{
	private:
		void* operator new(const size_t) throw();
		void operator delete(void*) throw();
		IWeakReference* ip;
	public:
		TWeakReferenceHandle(): ip(NULL) {};
		TWeakReferenceHandle(const TWeakReferenceHandle& other): ip(NULL)
		{
			if(other.ip) other.ip->_add_ref_var(&(this->ip));
		};
		TWeakReferenceHandle(IType* inst_t): ip(NULL)
		{
			IWeakReference* inst = dynamic_cast<IWeakReference*>(inst_t);
			if(inst)
			{
				inst->_add_ref_var(&(this->ip));
			}
		};
		~TWeakReferenceHandle()
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
		TWeakReferenceHandle& operator =(const TWeakReferenceHandle& other)
		{
			if(this->ip) this->ip->_release_var(&(this->ip));
			if(other.ip) other.ip->_add_ref_var(&(this->ip));
			return (*this);
		};
		bool operator ==(const TWeakReferenceHandle& other) const
		{
			return (this->ip == other.ip);
		};
		bool operator !=(const TWeakReferenceHandle& other) const
		{
			return (this->ip != other.ip);
		};
		bool operator <(const TWeakReferenceHandle& other) const
		{
			return (this->ip < other.ip);
		};
		IType* operator ->() const { return static_cast<IType*>(this->ip); };
		template<typename TOther> TWeakReferenceHandle<TOther> cast() const
		{
			TWeakReferenceHandle<TOther> retv;
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
		template<typename IType> TInterfaceHandle<IType> create_t(const char* iid, short* error_value)
		{
			TInterfaceHandle<IType> retv;
			if(iid)
			{
				IInterface* inst = NULL;
				short err_val = this->create(iid, &inst);
				if(err_val == 0)
				{
					retv = TInterfaceHandle<TInterface>(static_cast<IType*>(inst));
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
	typedef TInterfaceHandle<IFactory> HFactory;
}
#endif