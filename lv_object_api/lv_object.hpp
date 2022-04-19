#ifndef __LV_OBJECT_FRAMEWORK
#define __LV_OBJECT_FRAMEWORK
#include <stddef.h>
namespace lv
{
	struct object
	{
		explicit object();
		virtual ~object();
		virtual const char* _type_id() const;
	};
	struct factory: public object
	{
		explicit factory();
		virtual ~factory();
		virtual const char* _type_id() const;
		virtual short create(const char* iid, object**);
	};
	struct ValueType: public object
	{
	private:
		void* operator new(const size_t) throw();
		void operator delete(void*) throw();
	public:
		explicit ValueType();
		virtual ~ValueType();
		virtual const char* _type_id() const;
	};
}
#if (__cplusplus >= 201103L) || (_MSC_VER >= 1600)
#include <memory>
namespace lv
{
	struct factory_t: public factory
	{
		template<typename IType> std::shared_ptr<IType> create_t(const char* iid, short* error_value)
		{
			std::shared_ptr<IType> retv;
			if(iid)
			{
				object* inst = NULL;
				short err_val = this->create(iid, &inst);
				if(inst) retv = std::shared_ptr<IType>(static_cast<IType*>(inst))
				if(error_value) (*error_value) = err_val;
			}
			return retv;
		};
	};
	typedef std::shared_ptr<factory_t> PFactory;
}
#else
namespace lv
{
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
		template<typename TOther> handle_t<TOther> cast_t()
		{
			handle_t<TOther> retv;
			if(this->cp)
			{
				TOther* idst = dynamic_cast<TOther*>(dynamic_cast<TObject*>(this->cp->_inst));
				if(idst)
				{
					retv.cp = this->cp;
					retv.cp->_add_ref();
				}
			}
			return retv;
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
	struct factory_t: public factory
	{
		template<typename IType> handle_t<IType> create_t(const char* iid, short* error_value)
		{
			handle_t<IType> retv;
			if(iid)
			{
				object* inst = NULL;
				short err_val = this->create(iid, &inst);
				if(inst) retv = handle_t<IType>(static_cast<IType*>(inst));
				if(error_value) (*error_value) = err_val;
			}
			return retv;
		};
	};
	typedef handle_t<factory_t> PFactory;
}
#endif
#endif