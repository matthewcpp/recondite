#ifndef RE_PROPERTYINTERFACE_HPP
#define RE_PROPERTYINTERFACE_HPP

#include <locale>

#include "rActor3.hpp"
#include "interface/riSerialization.hpp"

#include <wx/wx.h>
#include <wx/sstream.h>
#include <wx/txtstrm.h>

#include <wx/propgrid/propgrid.h>
#include <wx/propgrid/property.h>
#include <wx/propgrid/advprops.h>

#include <wx/clntdata.h>

class reComponent;

//Base -> calculate display names

class rePropertyInterfaceBase : public riSerializationTarget{
public:
	virtual riSerializationTarget* SubObject(const rString& name) override;
	virtual bool Next() override;
	virtual bool Category(const rString& name) override;
};

//Reader -> Fills a property grid with actor properties

class rePropertyReader : public rePropertyInterfaceBase{
public:
	rePropertyReader(reComponent* component, wxPropertyGrid* grid);

public:
	void Read(rActor3* actor);

public:
	virtual bool Boolean(const rString& name, bool& val) override;
	virtual bool Int(const rString& name, int& val) override;
	virtual bool Float(const rString& name, float& val) override;
	virtual bool String(const rString& name, rString& val) override;
	virtual bool Vector3(const rString& name, rVector3& val) override;
	virtual bool Color(const rString& name, rColor& color) override;

	virtual bool Category(const rString& name) override;

private:
	wxString DisplayName(const wxString& name);


private:
	wxPropertyGrid* m_grid;
	reComponent* m_component;
};

//Updater Updates a property grid

class rePropertyUpdater : public rePropertyInterfaceBase{
public:
	rePropertyUpdater(wxPropertyGrid* grid);

public:
	void Read(rActor3* actor);

public:
	virtual bool Boolean(const rString& name, bool& val) override;
	virtual bool Int(const rString& name, int& val) override;
	virtual bool Float(const rString& name, float& val) override;
	virtual bool String(const rString& name, rString& val) override;
	virtual bool Vector3(const rString& name, rVector3& val) override;
	virtual bool Color(const rString& name, rColor& color) override;

private:
	wxPropertyGrid* m_grid;
};


//Writer Writes a property to the actor

class rePropertyWriter : public rePropertyInterfaceBase{
public:
	rePropertyWriter();

public:
	void Write(rActor3* actor);
	void SetProperty(const wxString& propertyName, const wxAny& anyVal);
	bool PropertySet() const;

public:
	virtual bool Boolean(const rString& name, bool& val) override;
	virtual bool Int(const rString& name, int& val) override;
	virtual bool Float(const rString& name, float& val) override;
	virtual bool String(const rString& name, rString& val) override;
	virtual bool Vector3(const rString& name, rVector3& val) override;
	virtual bool Color(const rString& name, rColor& val) override;

private:
	template <typename T>
	bool DoGetValue(const rString& name, T& val);

private:
	rString m_propertyName;
	wxAny m_value;
	bool m_propertySet;
};

template <typename T>
bool rePropertyWriter::DoGetValue(const rString& name, T& val){
	if (name == m_propertyName){
		val = m_value.As<T>();
		return true;
	}

	return false;
}

//Getter -> gets a property from the actor

class rePropertyGetter : public rePropertyInterfaceBase{
public:
	rePropertyGetter();
public:
	void GetProperty(const wxString& propertyName, rActor3* actor);
	const wxAny& GetValue() const;
	bool PropertySet() const;

public:
	virtual bool Boolean(const rString& name, bool& val) override;
	virtual bool Int(const rString& name, int& val) override;
	virtual bool Float(const rString& name, float& val) override;
	virtual bool String(const rString& name, rString& val) override;
	virtual bool Vector3(const rString& name, rVector3& val) override;
	virtual bool Color(const rString& name, rColor& val) override;

private:
	template <typename T>
	void DoSetValue(const rString& name, T& val);

private:
	rString m_propertyName;
	wxAny m_value;
	bool m_propertySet;
};

template <typename T>
void rePropertyGetter::DoSetValue(const rString& name, T& val){
	if (name == m_propertyName){
		m_value = val;
		m_propertySet = true;
	}
}

#endif