#include "rePrimitivePropertyConnector.hpp"

rPrimitivePropertyConnector::rPrimitivePropertyConnector(rPrimitive* primitive)
	:reActorPropertyConnector(primitive)
{
	m_primitive = primitive;
}

void rPrimitivePropertyConnector::SetClassPGProperties(wxPropertyGrid* grid){
	grid->Append(new wxPropertyCategory("Primitive", wxPG_LABEL));
	grid->Append(new wxColourProperty("Edge Color", wxPG_LABEL));
	grid->Append(new wxColourProperty("Face Color", wxPG_LABEL));
}

void rPrimitivePropertyConnector::RefreshClassPGProperties(wxPropertyGrid* grid){
	rColor c = m_primitive->EdgeColor();
	wxColor color(c.red, c.green, c.blue);
	grid->SetPropertyValue("Edge Color", color);

	c = m_primitive->FaceColor();
	color.Set(c.red, c.green, c.blue);
	grid->SetPropertyValue("Face Color", color);
}

bool rPrimitivePropertyConnector::SetColorProperty(const wxString& name, wxColor val){
	bool refresh = false;
	rColor color(val.Red(), val.Green(), val.Blue(), 255);

	if (name == "Edge Color"){
		m_primitive->SetEdgeColor(color);
		refresh = true;
	}
	else if (name == "Face Color"){
		m_primitive->SetFaceColor(color);
		refresh = true;
	}

	return refresh;
}

//--------------------------------

rPrimitiveBoxPropertyConnector::rPrimitiveBoxPropertyConnector(rPrimitiveBox* box)
	:rPrimitivePropertyConnector(box)
{
	m_box = box;
}

void rPrimitiveBoxPropertyConnector::SetClassPGProperties(wxPropertyGrid* grid){
	grid->Append(new wxPropertyCategory("Primitive Box", wxPG_LABEL));
	grid->Append(new wxUIntProperty("Width", wxPG_LABEL));
	grid->Append(new wxUIntProperty("Width Segments", wxPG_LABEL));
	grid->Append(new wxUIntProperty("Height", wxPG_LABEL));
	grid->Append(new wxUIntProperty("Height Segments", wxPG_LABEL));
	grid->Append(new wxUIntProperty("Depth", wxPG_LABEL));
	grid->Append(new wxUIntProperty("Depth Segments", wxPG_LABEL));

	rPrimitivePropertyConnector::SetClassPGProperties(grid);
}

void rPrimitiveBoxPropertyConnector::RefreshClassPGProperties(wxPropertyGrid* grid){
	grid->SetPropertyValue("Width", m_box->Width());
	grid->SetPropertyValue("Width Segments", m_box->WidthSegments());
	grid->SetPropertyValue("Height", m_box->Width());
	grid->SetPropertyValue("Height Segments", m_box->HeightSegments());
	grid->SetPropertyValue("Depth", m_box->Width());
	grid->SetPropertyValue("Depth Segments", m_box->DepthSegments());

	rPrimitivePropertyConnector::RefreshClassPGProperties(grid);
}

bool rPrimitiveBoxPropertyConnector::SetIntProperty(const wxString& name, int val){
	bool refresh = false;

	if (name == "Width"){
		m_box->SetWidth(val);
		refresh = true;
	}
	if (name == "Width Segments"){
		m_box->SetWidthSegments(val);
		refresh = true;
	}
	else if (name == "Height"){
		m_box->SetHeight(val);
		refresh = true;
	}
	if (name == "Height Segments"){
		m_box->SetHeightSegments(val);
		refresh = true;
	}
	else if (name == "Depth"){
		m_box->SetDepth(val);
		refresh = true;
	}
	if (name == "Depth Segments"){
		m_box->SetDepthSegments(val);
		refresh = true;
	}

	return refresh;
}

wxString rPrimitiveBoxPropertyConnector::GetConnectionClass(){
	return m_box->ClassName().c_str();
}