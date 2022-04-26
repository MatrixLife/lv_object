#ifndef __LV_OBJECT_FRAMEWORK
#define __LV_OBJECT_FRAMEWORK
#include <exception>
#include <set>
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
}
#endif