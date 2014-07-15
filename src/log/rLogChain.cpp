#include "log/rLogChain.hpp"

rLogChain::rLogChain(rLogTarget* target){
	AddTarget(target);
}

rLogChain::rLogChain(rLogTarget* target1, rLogTarget* target2){
	AddTarget(target1);
	AddTarget(target2);
}

rLogChain::~rLogChain(){
	DeleteAllTargets();
}

void rLogChain::AddTarget(rLogTarget* target){
	m_targets.push_back(target);
}

void rLogChain::DeleteTarget(size_t index){
	if (index < m_targets.size()){
		rLogTargetList::iterator it = m_targets.begin();
		std::advance(it, index);
		
		delete *it;
		m_targets.erase(it);
	}
}

rLogTarget* rLogChain::GetTarget(size_t index) const{
	rLogTarget* target = NULL;
	
	if (index < m_targets.size()){
		rLogTargetList::const_iterator it = m_targets.begin();
		std::advance(it, index);
		
		target = *it;
	}
	
	return target;
}

void rLogChain::DeleteAllTargets(){
	rLogTargetList::iterator end = m_targets.end();
	
	for (rLogTargetList::iterator it = m_targets.begin(); it != end; ++it){
		delete (*it);
	}
	
	m_targets.clear();
}

size_t rLogChain::NumTargets() const{
	return m_targets.size();
}

void rLogChain::Debug(const rString& message){
	rLogTargetList::iterator end = m_targets.end();
	
	for (rLogTargetList::iterator it = m_targets.begin(); it != end; ++it){
		(*it)->Debug(message);
	}
}

void rLogChain::Warning(const rString& message){
	rLogTargetList::iterator end = m_targets.end();
	
	for (rLogTargetList::iterator it = m_targets.begin(); it != end; ++it){
		(*it)->Warning(message);
	}
}

void rLogChain::Trace(const rString& message){
	rLogTargetList::iterator end = m_targets.end();
	
	for (rLogTargetList::iterator it = m_targets.begin(); it != end; ++it){
		(*it)->Trace(message);
	}
}

void rLogChain::Info(const rString& message){
	rLogTargetList::iterator end = m_targets.end();
	
	for (rLogTargetList::iterator it = m_targets.begin(); it != end; ++it){
		(*it)->Info(message);
	}
}

void rLogChain::Error(const rString& message){
	rLogTargetList::iterator end = m_targets.end();
	
	for (rLogTargetList::iterator it = m_targets.begin(); it != end; ++it){
		(*it)->Error(message);
	}
}

void rLogChain::Shutdown(){
	rLogTargetList::iterator end = m_targets.end();

	for (rLogTargetList::iterator it = m_targets.begin(); it != end; ++it){
		(*it)->Shutdown();
	}
}