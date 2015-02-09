#ifndef RE_PRIMITIVEPROPERTYCONNECTOR_HPP
#define RE_PRIMITIVEPROPERTYCONNECTOR_HPP

#include "reActorPropertyConnector.hpp"

#include "primitive/rPrimitiveBox.hpp"

class rPrimitivePropertyConnector : public reActorPropertyConnector{
public:
	rPrimitivePropertyConnector(rPrimitive* primitive);

public:
	virtual bool SetColorProperty(const wxString& name, wxColor val);

protected:
	virtual void SetClassPGProperties(wxPropertyGrid* grid) = 0;
	virtual void RefreshClassPGProperties(wxPropertyGrid* grid) = 0;

private:
	rPrimitive* m_primitive;

};

//--------------------------------

class rPrimitiveBoxPropertyConnector : public rPrimitivePropertyConnector {
public:
	rPrimitiveBoxPropertyConnector(rPrimitiveBox* box);

public:
	virtual bool SetIntProperty(const wxString& name, int val);

protected:
	virtual void SetClassPGProperties(wxPropertyGrid* grid);
	virtual void RefreshClassPGProperties(wxPropertyGrid* grid);

private:
	rPrimitiveBox* m_box;
};

#endif