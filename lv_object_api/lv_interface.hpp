#ifndef __LV_INTERFACE_FRAMEWORK
#define __LV_INTERFACE_FRAMEWORK
#include <stddef.h>
namespace lv
{
	struct IInterface
	{
		virtual void _add_ref() = 0;
		virtual void _release() = 0;
		virtual const char* _type_id() const = 0;
	};
	struct IWeakReferencable
	{
		virtual bool _add_ref_var(IWeakReferencable**) = 0;
		virtual void _release_var(IWeakReferencable**) = 0;
	};
	struct IAssignable
	{
		virtual bool assign(IInterface*) = 0;
	};
	struct IClonable
	{
		virtual bool clone(IInterface**) = 0;
	};
	template<typename IType> struct IAssignableT
	{
		virtual bool assign_t(IType*) = 0;
	};
	template<typename IType> struct IClonableT
	{
		virtual bool clone_t(IType**) = 0;
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
		TInterfaceHandle(IType* inst_t): ip(dynamic_cast<IInterface*>(inst_t))
		{
			if(this->ip) this->ip->_add_ref();
		};
		~TInterfaceHandle()
		{
			if(this->ip) this->ip->_release();
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
				this->ip->_release();
				this->ip = NULL;
			}
		};
		template<typename IOther> TInterfaceHandle<IOther> cast_t()
		{
			TInterfaceHandle<IOther> retv;
			if(this->cp)
			{
				IOther* idst = dynamic_cast<IOther*>(dynamic_cast<IType*>(this->ip));
				if(idst)
				{
					retv.ip = dynamic_cast<IInterface*>(idst);
					retv.ip->_add_ref();
				}
			}
			return retv;
		};
		operator bool() const
		{
			return (this->ip != NULL);
		};
		TInterfaceHandle& operator =(const TInterfaceHandle& other)
		{
			if(other.ip) other.ip->_add_ref();
			if(this->ip) this->ip->_release();
			this->ip = other.ip;
			return (*this);
		};
		TInterfaceHandle& operator =(IType* inst_t)
		{
			IInterface* inst = dynamic_cast<IInterface*>(inst_t);
			if(inst) inst->_add_ref();
			if(this->ip) this->ip->_release();
			this->ip = inst;
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
	};
	template<typename IType> struct TWeakReferenceHandle
	{
	private:
		void* operator new(const size_t) throw();
		void operator delete(void*) throw();
		IWeakReferencable* ip;
	public:
		TWeakReferenceHandle(): ip(NULL) {};
		TWeakReferenceHandle(const TWeakReferenceHandle& other): ip(NULL)
		{
			if(other.ip) other.ip->_add_ref_var(&(this->ip));
		};
		TWeakReferenceHandle(IType* inst_t): ip(NULL)
		{
			IWeakReferencable* inst = dynamic_cast<IWeakReferencable*>(inst_t);
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
		TWeakReferenceHandle& operator =(IType* inst_t)
		{
			IWeakReferencable* inst = dynamic_cast<IWeakReferencable*>(inst_t)
			if(this->ip) this->ip->_release_var(&(this->ip));
			if(inst) inst->_add_ref_var(&(this->ip));
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