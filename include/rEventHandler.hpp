#ifndef R_EVENTHANDLER_HPP
#define R_EVENTHANDLER_HPP

#include <map>
#include <list>

#include "rBuild.hpp"

#include "rEvent.hpp"

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
class rTargetFunctor : public rTargetFunctorBase{
public:
	rTargetFunctor(TargetType* target, typename rGenericTargetFunctionPointer<TargetType>::Type method): rTargetFunctorBase(0), m_target(target), m_method(method){}
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

class GloablFunctor: public rFunctorBase{
public:
	GloablFunctor(rEventFunctionPointer function) : rFunctorBase(1), m_function(function){}
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
	rEventFunctionPointer m_function;
};

class RECONDITE_API rEventHandler{
public:
	~rEventHandler();

public:
	template <typename TargetType>
	void Bind(int eventType, TargetType* target, typename rGenericTargetFunctionPointer<TargetType>::Type method);
	void Bind(int eventType, rEventFunctionPointer function);

	template <typename TargetType>
	void Unbind(int eventType, TargetType* target, typename rGenericTargetFunctionPointer<TargetType>::Type method);
	void Unbind(int eventType, rEventFunctionPointer function);

	void Trigger(int eventType, rEvent& event);

private:
	void BindFunctor(int eventType, rFunctorBase* functor);
	void UnbindFunctor(int eventType, rFunctorBase& functor);

	void Clear();

private:
	rFunctorMap m_functorMap;
};


template <typename TargetType>
void rEventHandler::Bind(int eventType, TargetType* target, typename rGenericTargetFunctionPointer<TargetType>::Type method){
	BindFunctor(eventType, new rTargetFunctor<TargetType>(target, method));
}

template <typename TargetType>
void rEventHandler::Unbind(int eventType, TargetType* target, typename rGenericTargetFunctionPointer<TargetType>::Type method){
	rTargetFunctor<TargetType> functor(target, method);
	UnbindFunctor(eventType, functor);
}

#endif
