#ifndef R_MODEL_HPP
#define R_MODEL_HPP

#include <map>
#include <memory>
#include <functional>

#include "rBuild.hpp"
#include "rTypes.hpp"
#include "rDefs.hpp"
#include "rString.hpp"

#include "rGeometry.hpp"
#include "rMaterial.hpp"
#include "rSkeleton.hpp"
#include "rAlignedBox3.hpp"

namespace recondite {
	class RECONDITE_API Mesh {
	public:
		Mesh(uint32_t bufferId, uint32_t bufferSize, rGeometryType geometryType, rMaterial* material) 
		: _elementBufferId(bufferId), _bufferCount(bufferSize),  _geometryType(geometryType), _material(material){}

	public:
		/**
		Gets the graphics device element buffer id associated with this mesh
		\returns the element buffer Id for this mesh
		*/
		inline uint32_t GetElementBufferId() const;

		/**
		Gets the number of elements in the buffer
		\returns the element buffer size
		*/
		inline uint32_t GetElementBufferCount() const;

		/**
		Gets the type of geometry of this mesh
		\returns the geometry type
		*/
		inline rGeometryType GetGeometryType() const;

		/**
		Gets the material associated with this mesh
		\returns the material for this mesh
		*/
		inline rMaterial* GetMaterial() const;

		/**
		Sets the material associated with this mesh
		\param material the material to associate with this mesh
		*/
		inline void SetMaterial(rMaterial* material);

		/**
		Gets the name of this mesh.  Names are optional.
		\returns the mesh name
		*/
		inline rString GetName() const;

		/**
		Sets the name of this mesh.  Names are optional
		\param name the name to set for this mesh
		*/
		inline void SetName(const rString& name);

		inline rAlignedBox3 GetBoundingBox() const;
		inline void SetBoundingBox(const rAlignedBox3& box);

	private:
		uint32_t _elementBufferId;
		uint32_t _bufferCount;
		rGeometryType _geometryType;
		rMaterial* _material;
		rString _name;
		rAlignedBox3 _boundingBox;
	};

	inline uint32_t Mesh::GetElementBufferId() const {
		return _elementBufferId;
	}

	inline uint32_t Mesh::GetElementBufferCount() const {
		return _bufferCount;
	}

	inline rGeometryType Mesh::GetGeometryType() const {
		return _geometryType;
	}

	inline rMaterial* Mesh::GetMaterial() const{
		return _material;
	}

	inline void Mesh::SetMaterial(rMaterial* material) {
		_material = material;
	}

	inline rString Mesh::GetName() const {
		return _name;
	}

	inline void Mesh::SetName(const rString& name) {
		_name = name;
	}

	inline rAlignedBox3 Mesh::GetBoundingBox() const {
		return _boundingBox;
	}

	inline void Mesh::SetBoundingBox(const rAlignedBox3& box) {
		_boundingBox = box;
	}

	class RECONDITE_API Model {
	public:
		Model(const rString& name, const Geometry& geometry);
		~Model();

	public:
		/**
		Creates a new triangle mesh in this model.
		\param bufferId the graphics device buffer id associated with this mesh
		\param bufferSize the number of elements in the device buffer
		\param material the material to associate with this mesh
		\returns new mesh object
		*/
		Mesh* CreateTriangleMesh(uint32_t bufferId, uint32_t bufferSize, rMaterial* material);

		/**
		Gets the number of triangle meshes in this model
		\returns the triangle mesh count
		*/
		size_t GetTriangleMeshCount() const;

		/**
		Gets a triangle mesh from this model
		\param index the index of the triangle mesh to retreive
		\returns the triangle mesh at the given index
		*/
		Mesh* GetTriangleMesh(size_t index) const;

		/**
		Creates a new line mesh in this model.
		\param bufferId the graphics device buffer id associated with this mesh
		\param bufferSize the number of elements in the device buffer
		\param material the material to associate with this mesh
		\returns new mesh object
		*/
		Mesh* CreateLineMesh(uint32_t bufferId, uint32_t bufferSize, rMaterial* material);

		/**
		Gets the number of line meshes in this model
		\returns the line mesh count
		*/
		size_t GetLineMeshCount() const;

		/**
		Gets a line mesh from this model
		\param index the index of the line mesh to retreive
		\returns the line mesh at the given index
		*/
		Mesh* GetLineMesh(size_t index) const;


		/**
		Gets the geometry for this model
		\returns the geometry associated with this model
		*/
		const Geometry* GetGeometry() const;

		/**
		Gets the model name
		\returns the name of the model
		*/
		rString GetName() const;

		/**
		Gets the bounding box for this model
		\returns the model bounding box
		*/
		rAlignedBox3 GetBoundingBox() const;

		void SetBoundingBox(const rAlignedBox3& box);
	private:
		struct Impl;
		Impl* _impl;
	};
}

#endif
