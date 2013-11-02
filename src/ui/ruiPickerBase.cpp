#include "ui/ruiPickerBase.hpp"

ruiPickerBase::ruiPickerBase(int id, const rPoint& position, const rSize& size)
:ruiWidget(id,position, size)
{
	Clear();
}

ruiPickerBase::ruiPickerBase(rArrayString& options, int id, const rPoint& position, const rSize& size)
:ruiWidget(id,position, size)
{
	SetOptions(options);
}

void ruiPickerBase::AddOption(const rString& option){
	m_options.push_back(option);
}

void ruiPickerBase::SetOptions(const rArrayString& options){
	m_selectionIndex = 0;
	m_options = options;
}

size_t ruiPickerBase::NumOptions() const{
	return m_options.size();
}

size_t ruiPickerBase::SelectionIndex() const{
	return m_selectionIndex;
}

bool ruiPickerBase::SetSelectionIndex(size_t index){
	if (index < m_options.size()){
		m_selectionIndex = index;
		return true;
	}
	else{
		return false;
	}
}

rString ruiPickerBase::SelectionText() const{
	if (m_options.size() > 0){
		return m_options[m_selectionIndex];
	}
	else{
		return "";
	}
}

void ruiPickerBase::Clear(){
	m_selectionIndex = 0;
	m_options.clear();
}

const rArrayString& ruiPickerBase::Options() const{
	return m_options;
}
