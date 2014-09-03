#include "rEventHandler.hpp"

rEventHandler::~rEventHandler(){
	Clear();
}

void rEventHandler::Clear(){
	rFunctorMap::iterator functorMapEnd = m_functorMap.end();
	for (rFunctorMap::iterator functorMapIterator = m_functorMap.begin(); functorMapIterator != functorMapEnd; ++functorMapIterator){
		rFunctorList& functorList = functorMapIterator->second;

		rFunctorList::iterator functorListEnd = functorList.end();
		for (rFunctorList::iterator functorListIterator = functorList.begin(); functorListIterator != functorListEnd; ++functorListIterator)
			delete *functorListIterator;
	}
}

void rEventHandler::BindFunctor(int eventType, rFunctorBase* functor){
	rFunctorList& functorList = m_functorMap[eventType];
	functorList.push_back(functor);
}

void rEventHandler::Bind(int eventType, rEventFunctionPointer function){
	BindFunctor(eventType, new GloablFunctor(function));
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

void rEventHandler::Unbind(int eventType, rEventFunctionPointer function){
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