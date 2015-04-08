#include "rePalette.hpp"

rePalette::rePalette(reComponent* component, wxWindow* parent)
	:wxPanel(parent, wxID_ANY)
{
	m_nextPaletteId = 10000;

	CreateSceneView();
}

void rePalette::AddSceneActor(wxBitmap& icon, const wxString& label, const wxString createStr){
	int id = m_nextPaletteId++;

	wxStaticBitmap* bitmapIcon = new wxStaticBitmap(this, id, icon);
	bitmapIcon->Bind(wxEVT_LEFT_DOWN, &rePalette::StartItemDrag, this);
	GetSizer()->Add(bitmapIcon,0, wxALL, 5);

	m_actorMapping[id] = createStr;
}

void rePalette::CreateSceneView(){
	SetSizer(new wxBoxSizer(wxHORIZONTAL));

	AddSceneActor(wxBitmap("assets/tool-box.png", wxBITMAP_TYPE_PNG), "Box", "PrimitiveBox");
	AddSceneActor(wxBitmap("assets/tool-cone.png", wxBITMAP_TYPE_PNG), "Cone", "PrimitiveCone");
	AddSceneActor(wxBitmap("assets/tool-plane.png", wxBITMAP_TYPE_PNG), "Plane", "PrimitiveGrid");

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