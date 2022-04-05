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
		IType* operator ->() const { return static_cast<IType*>(this->ip); };
	};
	template<typename TObject> struct handle_t
	{
	private:
		struct _SafeRefCtx
		{
			size_t _refs;
			object* _inst;
			_SafeRefCtx(object* inst): _refs(0), _inst(inst) {};
			_SafeRefCtx(TObject* inst): _refs(0), _inst(dynamic_cast<object*>(inst)) {};
			~_SafeRefCtx(){ if(this->_inst) delete this->_inst; };
			void _add_ref(){ this->_refs+= 1; };
			void _release(){ if(this->_refs > 1) this->_refs-= 1; else delete this; };
		};
		_SafeRefCtx* cp;
	public:
		handle_t(): cp(NULL) {};
		handle_t(const handle_t& other): cp(other.cp)
		{
			if(this->cp) this->cp->_add_ref();
		};
		handle_t(object* inst): cp(NULL)
		{
			if(dynamic_cast<TObject*>(inst))
			{
				this->cp = new _SafeRefCtx(inst);
				this->cp->_add_ref();
			}
		};
		handle_t(TObject* inst): cp(NULL)
		{
			if(dynamic_cast<object*>(inst))
			{
				this->cp = new _SafeRefCtx(inst);
				this->cp->_add_ref();
			}
		};
		~handle_t()
		{
			if(this->cp) this->cp->_release();
		};
		size_t pointer() const
		{
			return (this->cp)? (size_t)(this->cp->_inst): NULL;
		};
		bool empty() const
		{
			return (this->cp == NULL);
		};
		bool valid() const
		{
			return (this->cp != NULL);
		};
		void clear()
		{
			if(this->cp)
			{
				this->cp->_release();
				this->cp = NULL;
			}
		};
		operator bool() const
		{
			return (this->cp != NULL);
		};
		handle_t& operator =(const handle_t& other)
		{
			if(other.cp) other.cp->_add_ref();
			if(this->cp) this->cp->_release();
			this->cp = other.cp;
			return (*this);
		};
		bool operator ==(const handle_t& other) const
		{
			return (this->pointer() == other.pointer());
		};
		bool operator !=(const handle_t& other) const
		{
			return (this->pointer() != other.pointer());
		};
		bool operator <(const handle_t& other) const
		{
			return (this->pointer() < other.pointer());
		};
		TObject* operator ->() const { return (this->cp)? dynamic_cast<TObject*>(this->cp->_inst): NULL; };
	};
}
#endif