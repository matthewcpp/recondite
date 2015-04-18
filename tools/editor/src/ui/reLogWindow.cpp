#include "reLogWindow.hpp"

reLogWindow::reLogWindow(reComponent* component, wxWindow* parent, wxWindowID id)
	:wxPanel(parent, id)
{
	m_component = component;

	InitControls();

	rLog::SetLogTarget(this);
}

void reLogWindow::Debug(const rString& message){
	AddItem(LogTypeIndex::Debug, message);
}

void reLogWindow::Warning(const rString& message){
	AddItem(LogTypeIndex::Warning, message);
}

void reLogWindow::Trace(const rString& message){
	AddItem(LogTypeIndex::Trace, message);
}

void reLogWindow::Info(const rString& message){
	AddItem(LogTypeIndex::Info, message);
}

void reLogWindow::Error(const rString& message){
	AddItem(LogTypeIndex::Error, message);
}

void reLogWindow::Shutdown(){

}

void reLogWindow::AddItem(LogTypeIndex logType, const rString& message){
	wxListItem messageItem;
	messageItem.SetColumn(0);
	messageItem.SetId(m_logList->GetItemCount());
	messageItem.SetImage((int)logType);
	messageItem.SetText(message.c_str());

	long rowId = m_logList->InsertItem(messageItem);

	wxListItem dateItem;
	dateItem.SetColumn(1);
	dateItem.SetText(wxDateTime::Now().FormatTime());

	dateItem.SetId(rowId);
	m_logList->SetItem(dateItem);
}

void reLogWindow::InitControls(){
	m_logList = new wxListView(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT);
	m_logList->AppendColumn("Message");
	m_logList->SetColumnWidth(0, 200);
	m_logList->AppendColumn("Time");
	
	wxSize imageSize(16,16);
	wxImageList* imageList = new wxImageList(imageSize.x, imageSize.y, false);

	imageList->Add(wxArtProvider::GetBitmap(wxART_QUESTION, wxART_OTHER, imageSize));
	imageList->Add(wxArtProvider::GetBitmap(wxART_WARNING, wxART_OTHER, imageSize));
	imageList->Add(wxArtProvider::GetBitmap(wxART_TICK_MARK, wxART_OTHER, imageSize));
	imageList->Add(wxArtProvider::GetBitmap(wxART_INFORMATION, wxART_OTHER, imageSize));
	imageList->Add(wxArtProvider::GetBitmap(wxART_ERROR, wxART_OTHER, imageSize));

	m_logList->AssignImageList(imageList, wxIMAGE_LIST_SMALL);

	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
	sizer->Add(m_logList, 1, wxEXPAND);
	SetSizerAndFit(sizer);
}