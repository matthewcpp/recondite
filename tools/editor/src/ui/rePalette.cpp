#include "rePalette.hpp"

rePalette::rePalette(reComponent* component, wxWindow* parent)
	:wxPanel(parent, wxID_ANY)
{
	m_nextPaletteId = 10000;
	m_component = component;

	SetSizer(new wxBoxSizer(wxVERTICAL));
	CreateSceneView();
}

void rePalette::AddSceneActor(const wxString& category, const wxBitmap& icon, const wxString& label, const wxString createStr){
	wxSizer* categorySizer = nullptr;

	if (m_categories.count(category)){
		categorySizer = m_categories[category];
	}
	else{
		wxBoxSizer* boxSizer = new wxBoxSizer(wxVERTICAL);
		GetSizer()->Add(boxSizer, 0, wxALL, 5);
		boxSizer->Add(new wxStaticText(this, wxID_ANY, category), 0, wxALL, 5);

		wxBoxSizer* itemSizer = new wxBoxSizer(wxHORIZONTAL);
		boxSizer->Add(itemSizer, 0, wxALL, 5);
		m_categories[category] = itemSizer;
		categorySizer = itemSizer;
	}
	
	int id = m_nextPaletteId++;

	wxStaticBitmap* bitmapIcon = new wxStaticBitmap(this, id, icon);
	bitmapIcon->Bind(wxEVT_LEFT_DOWN, &rePalette::StartItemDrag, this);
	categorySizer->Add(bitmapIcon, 0, wxALL, 5);
	GetSizer()->Layout();

	m_actorMapping[id] = createStr;
}

void rePalette::CreateSceneView(){
	AddSceneActor("Primitives", wxBitmap("assets/tool-box.png", wxBITMAP_TYPE_PNG), "Box", "PrimitiveBox");
	AddSceneActor("Primitives", wxBitmap("assets/tool-cone.png", wxBITMAP_TYPE_PNG), "Cone", "PrimitiveCone");
	AddSceneActor("Primitives", wxBitmap("assets/tool-plane.png", wxBITMAP_TYPE_PNG), "Plane", "PrimitiveGrid");
	AddSceneActor("Primitives", wxBitmap("assets/tool-cylinder.png", wxBITMAP_TYPE_PNG), "Cylinder", "PrimitiveCylinder");
	AddSceneActor("Primitives", wxBitmap("assets/tool-sphere.png", wxBITMAP_TYPE_PNG), "Sphere", "PrimitiveSphere");
}

void rePalette::StartItemDrag(wxMouseEvent& event){
	int id = event.GetId();

	if (m_actorMapping.count(id)){
		wxTextDataObject actorData(m_actorMapping[id]);

		wxDropSource dragSource(this);
		dragSource.SetData(actorData);
		wxDragResult result = dragSource.DoDragDrop(true);
	}
}

void rePalette::OnProjectOpen() {
	const recondite::AssetManifest* assets = m_component->GetProject()->Assets()->Manifest();

	size_t modelCount = assets->Count(rAssetType::Model);
	rString name, path;

	for (size_t i = 0; i < modelCount; i++) {
		assets->Get(rAssetType::Model, i, name, path);

		wxString previewIconPath = m_component->GetProject()->Assets()->GetAssetPreviewIcon(rAssetType::Model, name.c_str());
		rString createString = "rProp:" + name;
		AddSceneActor("Models", wxBitmap(previewIconPath, wxBITMAP_TYPE_PNG), name.c_str(), createString.c_str());
	}
}