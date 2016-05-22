#include "ui/ruiLogText.hpp"

#include <deque>

struct ruiLogText::Impl{
	std::deque<rString> logMessages;
	size_t maxMessageSize;
	rSize cachesStringSize;
	rString cachedText;
	bool needsCache;

	void UpdateCachedString(Font::Face* font);
	void AddMessage(const rString& message);

	Impl() : maxMessageSize(10), needsCache(false) {}
};

ruiLogText::ruiLogText(const rString& id, ruiIDocument* document, rEngine* engine)
	:ruiWidget(id, document, engine)
{
	_impl = new Impl();
	Log::AddTarget(this);
}

ruiLogText::~ruiLogText(){
	Log::RemoveTarget(this);
	delete _impl;
}

void ruiLogText::Impl::UpdateCachedString(Font::Face* font){
	if (needsCache){
		cachedText.clear();

		for (size_t i = 0; i < logMessages.size(); i++){
			if (i) cachedText += '\n';
			cachedText += logMessages[i];
		}

		cachesStringSize = font->MeasureString(cachedText);
		needsCache = false;
	}
}

void ruiLogText::Impl::AddMessage(const rString& message){
	if (logMessages.size() >= maxMessageSize)
		logMessages.pop_front();

	logMessages.push_back(message);
	needsCache = true;
}

void ruiLogText::SetMaxMessageSize(size_t maxMessageSize){
	_impl->maxMessageSize = maxMessageSize;
}

size_t ruiLogText::MaxMessageSize(){
	return _impl->maxMessageSize;
}

void ruiLogText::Clear(){
	_impl->logMessages.clear();
	InvalidateSize();
}

void ruiLogText::Debug(const rString& message){
	_impl->AddMessage(message);
	InvalidateSize();
}

void ruiLogText::Warning(const rString& message){
	_impl->AddMessage(message);
	InvalidateSize();
}

void ruiLogText::Trace(const rString& message){
	_impl->AddMessage(message);
	InvalidateSize();
}

void ruiLogText::Info(const rString& message){
	_impl->AddMessage(message);
	InvalidateSize();
}

void ruiLogText::Error(const rString& message){
	_impl->AddMessage(message);
	InvalidateSize();
}

rString ruiLogText::GetWidgetType() const{
	return "logtext";
}

void ruiLogText::Draw(){
	ruiStyle* style = ComputedStyle();
	Font::Face* font = DetermineFont();
	_impl->UpdateCachedString(font);

	rColor color(255, 255, 255, 255);
	rRect boundingBox = BoundingBox();

	RenderWidgetBase(style, boundingBox);

	if (font){
		color.Set(255, 255, 255, 255);
		style->GetColor("color", color);

		m_engine->renderer->SpriteBatch()->RenderString(_impl->cachedText, font, ContentPosition(), color, 0.01);
	}
}

rSize ruiLogText::ComputeSize(){
	Font::Face* font = DetermineFont();
	_impl->UpdateCachedString(font);

	ruiStyle* style = ComputedStyle();

	rSize size(200, font->GetLineHeight());

	if (!style->GetInt("width", size.x)){
		size.x = _impl->cachesStringSize.x;
	}

	if (!style->GetInt("height", size.y)){
		size.y = font->GetLineHeight();

		if (_impl->logMessages.size() > 0)
			size.y *= _impl->logMessages.size();
	}

	return size;
}