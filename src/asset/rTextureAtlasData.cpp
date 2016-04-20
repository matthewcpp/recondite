#include "asset/rTextureAtlasData.hpp"

void rTextureAtlasData::AddEntry(const rString& name, const rSize& textureSize, const rVector2& uvOrigin, const rVector2& uvSize) {
	rTextureEntryRef textureEntry;
	textureEntry.reset(new rTextureAtlasEntry(name, textureSize, uvOrigin, uvSize));
	m_textureEntries.push_back(textureEntry);
}

size_t rTextureAtlasData::GetNumEntries() const {
	return m_textureEntries.size();
}

void rTextureAtlasData::Clear() {
	m_textureEntries.clear();
}

const rTextureAtlasData::rTextureAtlasEntry* rTextureAtlasData::GetEntry(size_t index) const{
	if (index >= m_textureEntries.size())
		return nullptr;
	else
		return m_textureEntries[index].get();
}

rContentError rTextureAtlasData::Read(rIStream& stream) {
	if (!stream.IsOk()) return rContentError::Error;

	rXMLDocument doc;
	int error = doc.LoadFromStream(stream);
	if (error) return rContentError::Error;

	rXMLElement* textures = doc.GetRoot()->GetChild(0);

	rTextureAtlasEntry entry;

	for (size_t i = 0; i < textures->NumChildren(); i++) {
		rXMLElement* textureEntry = textures->GetChild(i);

		textureEntry->GetChild(0)->GetText(entry.name);

		rXMLElement* textureSize = textureEntry->GetChild(1);
		textureSize->GetAttribute<int>("x", entry.textureSize.x);
		textureSize->GetAttribute<int>("y", entry.textureSize.y);

		rXMLElement* uvOrigin = textureEntry->GetChild(2);
		uvOrigin->GetAttribute<float>("x", entry.uvOrigin.x);
		uvOrigin->GetAttribute<float>("y", entry.uvOrigin.y);

		rXMLElement* uvSize = textureEntry->GetChild(3);
		uvSize->GetAttribute<float>("x", entry.uvSize.x);
		uvSize->GetAttribute<float>("y", entry.uvSize.y);

		AddEntry(entry.name, entry.textureSize, entry.uvOrigin, entry.uvSize);
	}

	return rContentError::None;
}

rContentError rTextureAtlasData::Write(rOStream& stream) {
	if (!stream.IsOk()) return rContentError::Error;

	rXMLDocument doc;
	rXMLElement* textures = doc.CreateRoot("TextureAtlas")->CreateChild("Textures");

	for (size_t i = 0; i < m_textureEntries.size(); i++) {
		rXMLElement* textureEntry = textures->CreateChild("Texture");

		rXMLElement* name = textureEntry->CreateChild("Name", m_textureEntries[i]->name);

		rXMLElement* textureSize = textureEntry->CreateChild("TextureSize");
		textureSize->AddAttribute("x", m_textureEntries[i]->textureSize.x);
		textureSize->AddAttribute("y", m_textureEntries[i]->textureSize.y);

		rXMLElement* uvOrigin = textureEntry->CreateChild("UVOrigin");
		uvOrigin->AddAttribute("x", m_textureEntries[i]->uvOrigin.x);
		uvOrigin->AddAttribute("y", m_textureEntries[i]->uvOrigin.y);

		rXMLElement* uvSize = textureEntry->CreateChild("UVSize");
		uvSize->AddAttribute("x", m_textureEntries[i]->uvSize.x);
		uvSize->AddAttribute("y", m_textureEntries[i]->uvSize.y);
	}

	doc.WriteToStream(stream);
	return rContentError::None;
}