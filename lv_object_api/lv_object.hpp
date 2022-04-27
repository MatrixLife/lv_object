#ifndef __LV_OBJECT_FRAMEWORK
#define __LV_OBJECT_FRAMEWORK
#include <exception>
#include <map>
#include <set>
#include <string>
namespace lv
{
	struct object
	{
	protected:
		explicit object();
	public:
		virtual ~object();
	};
	struct ValueType: public object
	{
	private:
		void* operator new(const size_t);
		void operator delete(void*);
	protected:
		explicit ValueType();
	};

	struct _Object_Ref_Ctx
	{
	private:
		object*                     _inst;
		size_t                      _srefs;
		std::set<_Object_Ref_Ctx**> _wrefs;
	public:
		_Object_Ref_Ctx(object*);
		~_Object_Ref_Ctx();
		void _add_safe_ref();
		void _add_weak_ref(_Object_Ref_Ctx**);
		void _safe_release();
		void _weak_release(_Object_Ref_Ctx**);
		object* inst() const;
	};
	template<typename TObject> struct safe_ptr: public ValueType
	{
	private:
		_Object_Ref_Ctx* i;
	public:
		safe_ptr(): i(NULL) {};
		safe_ptr(const safe_ptr& other): i(other.i)
		{
			if(this->i) this->i->_add_safe_ref();
		};
		safe_ptr(TObject* inst): i(NULL)
		{
			if(static_cast<object*>(inst))
			{
				this->i = new _Object_Ref_Ctx(static_cast<object*>(inst));
				this->i->_add_safe_ref();
			}
		};
		~safe_ptr()
		{
			if(this->i) this->i->_safe_release();
		};
		size_t pointer() const
		{
			return (this->i)? (size_t)(this->i->inst()): NULL;
		};
		bool empty() const { return (this->i == NULL); };
		bool valid() const { return (this->i != NULL); };
		void clear()
		{
			if(this->i)
			{
				this->i->_safe_release();
				this->i = NULL;
			}
		};
		operator bool() const { return (this->i != NULL); };
		safe_ptr& operator =(const safe_ptr& other)
		{
			if(this->i) this->i->_safe_release();
			if(other.i) other.i->_add_safe_ref();
			this->i = other.i;
			return (*this);
		};
		bool operator ==(const safe_ptr& other) const { return (this->i == other.i); };
		bool operator !=(const safe_ptr& other) const { return (this->i != other.i); };
		bool operator <(const safe_ptr& other) const { return (this->i < other.i); };
		TObject* operator ->() const { return (this->i)? static_cast<TObject*>(this->i->inst()): NULL; };
		template<typename TOther> safe_ptr<TOther> cast() const
		{
			safe_ptr<TOther> retv;
			if(this->i && this->i->inst())
			{
				TOther* inst_t = dynamic_cast<TOther*>(this->i->inst());
				if(inst_t)
				{
					retv.i = this->i;
					retv.i->_add_safe_ref();
				}
			}
			return retv;
		};
	};
	template<typename TObject> struct weak_ptr: public ValueType
	{
	private:
		_Object_Ref_Ctx* i;
	public:
		weak_ptr(): i(NULL) {};
		weak_ptr(const weak_ptr& other): i(other.i)
		{
			if(this->i) other.i->_add_weak_ref(&(this->i))
		};
		weak_ptr(const safe_ptr<TObject>& sp): i(NULL)
		{
			_Object_Ref_Ctx** pp = (_Object_Ref_Ctx**)(&sp);
			this->i = (*pp);
			if(this->i) this->i->_add_weak_ref(&(this->i));
		};
		~weak_ptr()
		{
			if(this->i) this->i->_weak_release(&(this->i));
		};
		size_t pointer() const
		{
			return (this->i)? (size_t)(this->i->inst()): NULL;
		};
		bool empty() const { return (this->i == NULL); };
		bool valid() const { return (this->i != NULL); };
		void clear() { if(this->i) this->i->_weak_release(&(this->i)); };
		operator bool() const { return (this->i != NULL); };
		weak_ptr& operator =(const weak_ptr& other)
		{
			if(this->i) this->i->_weak_release(&(this->i));
			if(other.i) other.i->_add_weak_ref(&(this->i));
			return (*this);
		};
		bool operator ==(const weak_ptr& other) const { return (this->i == other.i); };
		bool operator !=(const weak_ptr& other) const { return (this->i != other.i); };
		bool operator <(const weak_ptr& other) const { return (this->i < other.i); };
		TObject* operator ->() const { return (this->i)? static_cast<TObject*>(this->i->inst()): NULL; };
		template<typename TOther> weak_ptr<TOther> cast() const
		{
			weak_ptr<TOther> retv;
			if(this->i && this->i->inst())
			{
				TOther* inst_t = dynamic_cast<TOther*>(this->i->inst());
				if(inst_t)
				{
					retv.i = this->i;
					retv.i->_add_weak_ref(&(retv.i));
				}
			}
			return retv;
		};
	};

	static const char* IID_IWeakReference = "lv.IWeakReference";
	static const char* IID_IAssign = "lv.IAssign";
	static const char* IID_IClone = "lv.IClone";
	static const char* IID_IEqual = "lv.IEqual";

	std::string IID_IAssignT(const char*);
	std::string IID_ICloneT(const char*);
	std::string IID_IEqualT(const char*);

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
	struct __declspec(novtable) IAssign: public IInterface
	{
		virtual bool _assign(IInterface*) = 0;
	};
	struct __declspec(novtable) IClone: public IInterface
	{
		virtual bool _clone(IInterface**) = 0;
	};
	struct __declspec(novtable) IEqual: public IInterface
	{
		virtual bool _equal(IInterface*) = 0;
	};
	struct __declspec(novtable) IWeakReference: public IInterface
	{
		virtual bool _add_ref_var(IWeakReference**) = 0;
		virtual void _release_var(IWeakReference**) = 0;
	};
	template<typename IType> struct __declspec(novtable) IAssignT: public IInterface
	{
		virtual bool _assign(IType*) = 0;
	};
	template<typename IType> struct __declspec(novtable) ICloneT: public IInterface
	{
		virtual bool _clone(IType**) = 0;
	};
	template<typename IType> struct __declspec(novtable) IEqualT: public IInterface
	{
		virtual bool _equal(IType*) = 0;
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
		IWeakReference* ip;
	public:
		TInterfaceWeakPtr(): ip(NULL) {};
		TInterfaceWeakPtr(const TInterfaceWeakPtr& other): ip(NULL)
		{
			if(other.ip) other.ip->_add_ref_var(&(this->ip));
		};
		TInterfaceWeakPtr(IType* inst_t): ip(NULL)
		{
			IWeakReference* inst = dynamic_cast<IWeakReference*>(inst_t);
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