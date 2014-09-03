#ifndef R_EVENTHANDLER_HPP
#define R_EVENTHANDLER_HPP

#include <map>
#include <list>

class rEvent {
public:
	rEvent() : m_handled(false) {}
	void SetHandled(bool handled = true) {m_handled = handled;}
	bool Handled() const { return m_handled; }

private:
	bool m_handled;
};

class rFunctorBase{
public:
	rFunctorBase(int type) : m_type(type) {}

	virtual void Call(rEvent& event) = 0;
	virtual bool Compare(const rFunctorBase& other) const = 0;
	virtual int Type() const {return m_type;}
	virtual ~rFunctorBase(){}

private:
	int m_type;
};

typedef std::list<rFunctorBase*> rFunctorList;
typedef std::map<int, rFunctorList> rFunctorMap;

class rTargetFunctorBase : public rFunctorBase{
public:
	rTargetFunctorBase(int type) : rFunctorBase(type) {}
	virtual void* Target() const = 0;
};

template <typename TargetType>
struct rGenericTargetFunctionPointer{
	typedef void (TargetType::*Type) (rEvent&);
};

template <typename TargetType>
class TargetFunctor : public rTargetFunctorBase{
public:
	TargetFunctor(TargetType* target, typename rGenericTargetFunctionPointer<TargetType>::Type method): rTargetFunctorBase(0), m_target(target), m_method(method){}
	virtual void Call(rEvent& event){(*m_target.*m_method)(event);}
	virtual void* Target() const { return (void*)m_target; }
	virtual bool Compare(const rFunctorBase& other) const {
		if (Type() == other.Type()){
			const rTargetFunctorBase& otherTarget = static_cast<const rTargetFunctorBase&>(other);
			return Target() == otherTarget.Target();
		}
		else{
			return false;
		}
	}

private:
	TargetType* m_target;
	typename rGenericTargetFunctionPointer<TargetType>::Type m_method;
};

typedef void(*FunctionPointerType)(rEvent&);

class GloablFunctor: public rFunctorBase{
public:
	GloablFunctor(FunctionPointerType function) : rFunctorBase(1), m_function(function){}
	virtual void Call(rEvent& event){(*m_function)(event);}
	virtual bool Compare(const rFunctorBase& other) const {
		if (Type() == other.Type()){
			const GloablFunctor& otherFunctor = static_cast<const GloablFunctor&>(other);
			return m_function == otherFunctor.m_function;
		}
		else{
			return false;
		}
	}

private:
	FunctionPointerType m_function;
};

class rEventHandler{

public:
	template <typename TargetType>
	void Bind(int eventType, TargetType* target, typename rGenericTargetFunctionPointer<TargetType>::Type method);
	void Bind(int eventType, FunctionPointerType function);

	template <typename TargetType>
	void Unbind(int eventType, TargetType* target, typename rGenericTargetFunctionPointer<TargetType>::Type method);
	void Unbind(int eventType, FunctionPointerType function);

	void Trigger(int eventType, rEvent& event);

private:
	void BindFunctor(int eventType, rFunctorBase* functor);
	void UnbindFunctor(int eventType, rFunctorBase& functor);

private:
	rFunctorMap m_functorMap;
};

void rEventHandler::BindFunctor(int eventType, rFunctorBase* functor){
	rFunctorList& functorList = m_functorMap[eventType];
	functorList.push_back(functor);
}

void rEventHandler::UnbindFunctor(int eventType, rFunctorBase& functor){
	rFunctorList& functorList = m_functorMap[eventType];

	rFunctorList::iterator iter = functorList.begin();
	rFunctorList::iterator end = functorList.end();

	while (iter != end)
	{
		rFunctorBase* item = *iter;

		if (item->Compare(functor)){
			delete item;
			iter = functorList.erase(iter);
		}
		else{
			++iter;
		}
	}
}

template <typename TargetType>
void rEventHandler::Bind(int eventType, TargetType* target, typename rGenericTargetFunctionPointer<TargetType>::Type method){
	BindFunctor(eventType, new TargetFunctor<TargetType>(target, method));
}

void rEventHandler::Bind(int eventType, FunctionPointerType function){
	BindFunctor(eventType, new GloablFunctor(function));
}


template <typename TargetType>
void rEventHandler::Unbind(int eventType, TargetType* target, typename rGenericTargetFunctionPointer<TargetType>::Type method){
	TargetFunctor<TargetType> functor(target, method);
	UnbindFunctor(eventType, functor);
}

void rEventHandler::Unbind(int eventType, FunctionPointerType function){
	GloablFunctor functor(function);
	UnbindFunctor(eventType, functor);
}

void rEventHandler::Trigger(int eventType, rEvent& event){
	rFunctorList& functorList = m_functorMap[eventType];

	rFunctorList::iterator end = functorList.end();
	for (rFunctorList::iterator it = functorList.begin(); it != end; ++it){
		rFunctorBase* functor = *it;
		functor->Call(event);
		if (event.Handled()) break;
	}
}

#endif
