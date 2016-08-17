#ifndef R_MODELDATA_HPP
#define R_MODELDATA_HPP

#include <map>
#include <fstream>
#include <utility>
#include <memory>

#include "rBuild.hpp"
#include "rDefs.hpp"
#include "rString.hpp"
#include "rMaterial.hpp"

#include "rAlignedBox3.hpp"
#include "rGeometryData.hpp"

namespace recondite {
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
		Gets the material for this mesh.
		\returns the material
		*/
		rMaterial& GetMaterial();

		/**
		Gets the material for this mesh.
		\returns the material
		*/
		const rMaterial& GetMaterial() const;

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
		const uint16_t* GetBufferData() const;

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

	private:
		struct Impl;
		Impl* _impl;
	};
}

#endif
