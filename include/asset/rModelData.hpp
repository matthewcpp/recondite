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
#include "rSkeleton.hpp"

namespace recondite {
	struct RECONDITE_API MaterialData {
		uint32_t id;
		uint32_t diffuseTextureId;
		rColor diffuseColor;

		MaterialData(uint32_t i) : id(i), diffuseTextureId(UINT_MAX), diffuseColor(rColor::White) {}
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
		Gets the material data id for this mesh.
		\returns the material data id.
		*/
		uint32_t GetMaterialDataId() const;

		/**
		Sets the material data id for this mesh.  This will instruct the model loader to use the material data at the specified index.
		\param id the material data id to use for this mesh.
		*/
		void SetMaterialDataId(uint32_t id);

		/**
		Sets the material that will be assigned to this mesh is created.  This material will take precidence over any material data id that is set.
		\param material the material to use for this mesh
		*/
		void SetMaterial(rMaterial* material);

		/**
		Gets the material that will be assigned to this mesh when it is created.
		\returns the material that will be used when the mesh is created
		*/
		rMaterial* GetMaterial() const;

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

		/**
		Returns a single element from the buffer.
		\param index the index of the element to get
		\returns the element at the given index
		*/
		uint16_t GetElement(size_t index) const;

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
		void DeleteTriangleMesh(size_t index);

		MeshData* CreateLineMesh();
		size_t GetLineMeshCount() const;
		MeshData* GetLineMesh(size_t index) const;
		void DeleteLineMesh(size_t index);

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
		void DeleteLastTexture();
		size_t GetNumTextures() const;
		rTextureData* GetTexture(size_t index) const;

		MaterialData* CreateMaterial();
		size_t GetNumMaterials() const;
		MaterialData* GetMaterial(size_t index) const;

		/**
		Creates a skeleton associated with this model data.  Calling this function will dete any skeleton currently associated with this model data.
		\returns the newly created skeleton object assocated with this model data.
		*/
		Skeleton* CreateSkeleton();

		/**
		Gets the skeleton object associated with this data.  Create a skeleton using CreateSkeleton().
		\returns the skeleton object.
		*/
		Skeleton* GetSkeleton() const;

		/**
		Relinquishes control of the skeleton object associated with this the model data.  The caller will be responsible for freeing the data.  
		After this call, GetSkeleton() will return null and CreateSkeleton will need to be called once more.
		\returns Skeleton pointer.
		*/
		Skeleton* DetachSkeleton();


		int Read(rIStream& stream);
		int Write(rOStream& stream) const;

	private:
		struct Impl;
		Impl* _impl;
	};
}

#endif
