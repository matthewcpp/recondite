#include "primitive/rPrimitiveBox.hpp"

rPrimitiveBox::rPrimitiveBox(const rString& id, rEngine* engine)
	:rPrimitive(id, engine)
{
	m_width = 1.0f;
	m_height = 1.0f;
	m_depth = 1.0f;
}


void rPrimitiveBox::Draw(){
	rImmediateBuffer geometry(rGEOMETRY_LINES, 3, false);

	unsigned short indicies[] = { 0,1,1,2,2,3,3,0,4,5,5,6,6,7,7,4,0,4,1,5,2,6,3,7 };
	geometry.SetIndexBuffer(indicies, 24);

	float halfWidth = m_width / 2.0f;
	float halfDepth = m_depth / 2.0f;

	geometry.PushVertex(-halfWidth, m_height, halfDepth);
	geometry.PushVertex(halfWidth, m_height, halfDepth);
	geometry.PushVertex(halfWidth, 0.0f, halfDepth);
	geometry.PushVertex(-halfWidth, 0.0f, halfDepth);

	geometry.PushVertex(-halfWidth, m_height, -halfDepth);
	geometry.PushVertex(halfWidth, m_height, -halfDepth);
	geometry.PushVertex(halfWidth, 0.0f, -halfDepth);
	geometry.PushVertex(-halfWidth, 0.0f, -halfDepth);

	rMatrix4 transform = TransformMatrix();
	m_engine->renderer->Render3dBuffer(geometry, transform, m_color);
}



rString rPrimitiveBox::ClassName() const{
	return "PrimitiveBox";
}

float rPrimitiveBox::Width() const{
	return m_width;
}

void rPrimitiveBox::SetWidth(float width){
	m_width = width;
}

float rPrimitiveBox::Height() const{
	return m_height;
}

void rPrimitiveBox::SetHeight(float height){
	m_height = height;
}

float rPrimitiveBox::Depth() const{
	return m_depth;
}

void rPrimitiveBox::SetDepth(float depth){
	m_depth = depth;
}