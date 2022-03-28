#ifndef __LV_OBJECT_FRAMEWORK
#define __LV_OBJECT_FRAMEWORK
#include <stddef.h>
namespace lv
{
	struct object
	{
	public:
		explicit object(){};
		virtual ~object(){};
		virtual const char* _type_id() const;
	};
	struct ValueType: public object
	{
	private:
		void* operator new(const size_t) throw();
		void operator delete(void*) throw();
	protected:
		explicit ValueType(){};
	public:
		virtual ~ValueType(){};
		virtual const char* _type_id() const;
	};
	struct ReferenceType: public object
	{
	private:
		void* operator new[](const size_t) throw();
		void operator delete[](void*) throw();
		ReferenceType(const ReferenceType&) throw();
		ReferenceType& operator =(const ReferenceType&) throw();
	protected:
		explicit ReferenceType(){};
	public:
		virtual ~ReferenceType(){};
		virtual const char* _type_id() const;
	};
	struct IInterface
	{
		virtual void _add_ref() = 0;
		virtual void _release() = 0;
		virtual const char* _type_id() = 0;
	};
	struct IWeakReference
	{
		virtual bool _add_ref_var(IWeakReference**) = 0;
		virtual void _release_var(IWeakReference**) = 0;
	};
	struct IAssignable
	{
		virtual bool _assign(IInterface*) = 0;
	};
	struct IClonable
	{
		virtual bool _clone(IInterface**) = 0;
	};
	template<typename IType> struct IAssignableT
	{
		virtual bool _assign_t(IType*) = 0;
	};
	template<typename IType> struct IClonableT
	{
		virtual bool _clone_t(IType**) = 0;
	};
	template<typename IType> struct TInterfaceHandle: public ValueType
	{
	private:
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
		virtual ~TInterfaceHandle()
		{
			if(this->ip) this->ip->_release();
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
		size_t pointer() const
		{
			return (size_t)(dynamic_cast<IType*>(this->ip));
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
		IType* operator ->()
		{
			return dynamic_cast<IType*>(this->ip);
		};
	};
	template<typename IType> struct TWeakReferenceHandle: public ValueType
	{
	private:
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
		virtual ~TWeakReferenceHandle()
		{
			if(this->ip) this->ip->_release_var(&(this->ip));
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
		size_t pointer() const
		{
			return (size_t)(dynamic_cast<IType*>(this->ip));
		};
		TWeakReferenceHandle& operator =(const TWeakReferenceHandle& other)
		{
			if(this->ip) this->ip->_release_var(&(this->ip));
			if(other.ip) other.ip->_add_ref_var(&(this->ip));
			return (*this);
		};
		TWeakReferenceHandle& operator =(IType* inst_t)
		{
			IWeakReference* inst = dynamic_cast<IWeakReference*>(inst_t)
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
		IType* operator ->() const
		{
			return static_cast<IType*>(this->ip);
		};
	};
}
#endif