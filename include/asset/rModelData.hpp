#ifndef R_MODELDATA_HPP
#define R_MODELDATA_HPP

#include <utility>
#include <memory>
#include <climits>
#include <vector>

#include "rBuild.hpp"
#include "rDefs.hpp"
#include "rString.hpp"
#include "rMaterial.hpp"

#include "rAlignedBox3.hpp"
#include "rGeometryData.hpp"
#include "rTextureData.hpp"

namespace recondite {
	struct RECONDITE_API MaterialData {
		uint32_t diffuseTextureId;
		rColor diffuseColor;

		MaterialData() : diffuseTextureId(UINT_MAX), diffuseColor(rColor::White) {}
	};

	class RECONDITE_API MeshData {
	public:
		MeshData(rGeometryType geometryType);
		~MeshData();

		/**
		Gets the name of this mesh.
		\returns the mesh name.
		*/
		rString GetName() const;

		/**
		Sets the name of this mesh.
		\param name the name for the mesh.
		*/
		void SetName(const rString& name);

		/**
		Gets the material Id for this mesh.
		\returns the material Id
		*/
		uint32_t GetMaterialId() const;
		void SetMaterialId(uint32_t id);

		/**
		Gets geometry type for this mesh.
		\returns the geometry type
		*/
		rGeometryType GetGeometryType() const;
		
		/**
		Gets the number of elements in this mesh.
		\returns the element type.
		*/
		size_t GetElementCount() const;

		/**
		Gets the buffer data for this mesh.  Useful to pass to a graphics device to create a buffer.
		\returns the element data.
		*/
		char* GetBufferData() const;

		/**
		Gets the size of the element buffer data.
		\returns the element buffer data size.
		*/
		size_t GetBufferDataSize() const;

		/**
		Adds an element to this mesh.
		\param element the element to add.
		*/
		void Push(uint16_t element);

		/**
		Adds an elements to this mesh.
		\param element1 the first element to add.
		\param element2 the second element to add.
		*/
		void Push(uint16_t element1, uint16_t element2);

		/**
		Adds an elements to this mesh.
		\param element1 the first element to add.
		\param element2 the second element to add.
		\param element3 the third element to add.
		*/
		void Push(uint16_t element1, uint16_t element2, uint16_t element3);

		void AllocateBuffer(size_t size);

		rAlignedBox3 GetBoundingBox() const;
		void SetBoundingBox(const rAlignedBox3& box);

	private:
		struct Impl;
		Impl* _impl;
	};

	class RECONDITE_API ModelData {
	public:
		ModelData();
		~ModelData();

		/**
		Creates a new mesh consisting of triangles.
		\returns the new mesh object.
		*/
		MeshData* CreateTriangleMesh();

		/**
		Gets the number of triangle meshes in this object.
		\returns the number of triangle meshes.
		*/
		size_t GetTriangleMeshCount() const;

		/**
		Gets a triangle mesh by index.
		\param index the index of the triangle mesh to retrieve.
		\returns the triangle mesh at the given index.
		*/
		MeshData* GetTriangleMesh(size_t index);

		MeshData* CreateLineMesh();
		size_t GetLineMeshCount() const;
		MeshData* GetLineMesh(size_t index) const;

		/**
		Gets a triangle mesh by index.
		\param index the index of the triangle mesh to retrieve.
		\returns the triangle mesh at the given index.
		*/
		const MeshData* GetTriangleMesh(size_t index) const;

		/**
		Gets the geometry data associated with this model.
		\returns the geometry data.
		*/
		GeometryData* GetGeometryData();

		/**
		Gets the geometry data associated with this model.
		\returns the geometry data.
		*/
		const GeometryData* GetGeometryData() const;

		/**
		Removes all data from the model.
		*/
		void Clear();

		void CalculateBoundings();
		rAlignedBox3 GetBoundingBox() const;

		rTextureData* CreateTexture();
		size_t GetNumTextures() const;
		rTextureData* GetTexture(size_t index) const;

		MaterialData* CreateMaterial();
		size_t GetNumMaterials() const;
		MaterialData* GetMaterial(size_t index) const;

		int Read(rIStream& stream);

		int Write(rOStream& stream);

	private:
		struct Impl;
		Impl* _impl;
	};
}

#endif
