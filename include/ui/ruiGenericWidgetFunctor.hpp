#ifndef RUI_GENERICWIDGETFUNCTOR_HPP
#define RUI_GENERICWIDGETFUNCTOR_HPP

#include <map>

#include "ui/ruiBase.hpp"

class ruiWidget;

class ruiWidgetFunctor{
public:
	virtual void Call(ruiWidget* widget) = 0;
	virtual ~ruiWidgetFunctor(){}
};

template <typename T>
struct ruiGenericFunctionPointer{
	typedef void (T::*Type) (ruiWidget*);
};

template <typename T>
class ruiGenericWidgetFunctor : public ruiWidgetFunctor{
public:
	ruiGenericWidgetFunctor(T* target, typename ruiGenericFunctionPointer<T>::Type method) : m_target(target), m_method(method) {}
	
	virtual void Call(ruiWidget* widget);
private:
	T* m_target;
	typename ruiGenericFunctionPointer<T>::Type m_method;
};

template <typename T>
void ruiGenericWidgetFunctor<T>::Call(ruiWidget* widget){
	(*m_target.*m_method)(widget);
}

typedef std::multimap<int, ruiWidgetFunctor*> ruiFunctorMap;

#endif