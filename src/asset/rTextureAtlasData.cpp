#include "asset/rTextureAtlasData.hpp"

#include "xml/rXMLDocument.hpp"

struct rTextureAtlasData::Impl{
	std::vector<std::shared_ptr<rTextureAtlasData::Entry>> textureEntries;
};

rTextureAtlasData::rTextureAtlasData(){
	_impl.reset(new Impl());
}

rTextureAtlasData::~rTextureAtlasData(){}

void rTextureAtlasData::AddEntry(const rString& name, const rSize& textureSize, const rVector2& uvOrigin, const rVector2& uvSize) {
	std::shared_ptr<rTextureAtlasData::Entry> textureEntry;
	textureEntry.reset(new Entry(name, textureSize, uvOrigin, uvSize));
	_impl->textureEntries.push_back(textureEntry);
}

size_t rTextureAtlasData::GetNumEntries() const {
	return _impl->textureEntries.size();
}

void rTextureAtlasData::Clear() {
	_impl->textureEntries.clear();
}

const rTextureAtlasData::Entry* rTextureAtlasData::GetEntry(size_t index) const{
	if (index >= _impl->textureEntries.size())
		return nullptr;
	else
		return _impl->textureEntries[index].get();
}

int rTextureAtlasData::Read(rIStream& stream) {
	if (!stream.IsOk()) return 1;

	rXMLDocument doc;
	int error = doc.LoadFromStream(stream);
	if (error) return 1;

	rXMLElement* textures = doc.GetRoot()->GetChild(0);

	Entry entry;

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

	return 0;
}

int rTextureAtlasData::Write(rOStream& stream) {
	if (!stream.IsOk()) return 1;

	rXMLDocument doc;
	rXMLElement* textures = doc.CreateRoot("TextureAtlas")->CreateChild("Textures");

	for (size_t i = 0; i < _impl->textureEntries.size(); i++) {
		rTextureAtlasData::Entry* atlasDataEntry= _impl->textureEntries[i].get();
		rXMLElement* textureEntry = textures->CreateChild("Texture");

		rXMLElement* name = textureEntry->CreateChild("Name", atlasDataEntry->name);

		rXMLElement* textureSize = textureEntry->CreateChild("TextureSize");
		textureSize->AddAttribute("x", atlasDataEntry->textureSize.x);
		textureSize->AddAttribute("y", atlasDataEntry->textureSize.y);

		rXMLElement* uvOrigin = textureEntry->CreateChild("UVOrigin");
		uvOrigin->AddAttribute("x", atlasDataEntry->uvOrigin.x);
		uvOrigin->AddAttribute("y", atlasDataEntry->uvOrigin.y);

		rXMLElement* uvSize = textureEntry->CreateChild("UVSize");
		uvSize->AddAttribute("x", atlasDataEntry->uvSize.x);
		uvSize->AddAttribute("y", atlasDataEntry->uvSize.y);
	}

	doc.WriteToStream(stream);
	return 0;
}

rTextureAtlasData::Entry::Entry() {}

rTextureAtlasData::Entry::Entry(const rString& _name, const rSize& _textureSize, const rVector2& _uvOrigin, const rVector2& _uvSize){
	name = _name;
	textureSize = _textureSize;
	uvOrigin = _uvOrigin;
	uvSize = _uvSize;
}