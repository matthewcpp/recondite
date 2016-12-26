#ifndef R_GEOMETRYDATA_HPP
#define R_GEOMETRYDATA_HPP

#include <map>
#include <fstream>
#include <cstring>
#include <utility>
#include <memory>

#include "rBuild.hpp"
#include "rDefs.hpp"
#include "rTypes.hpp"
#include "rString.hpp"

#include "rVector2.hpp"
#include "rVector3.hpp"
#include "rMatrix4.hpp"

#include "stream/rIStream.hpp"
#include "stream/rOStream.hpp"

namespace recondite {
	class RECONDITE_API GeometryData {
	public:
		GeometryData();
		~GeometryData();

		/**
		Gets the number of vertices in this object.
		\returns Vertex count.
		*/
		size_t VertexCount() const;

		/**
		Gets a pointer to the raw vertex data contained in this object.  Useful to pass to a graphics device to create a buffer.
		\returns Pointer to the vertex data contained in this object.
		*/
		char* VertexData() const;

		/**
		Gets the size (in bytes) of the vertex data.
		\returns the vertex data size
		*/
		size_t VertexDataSize() const;

		/**
		Gets a pointer to the raw normal data contained in this object.  Useful to pass to a graphics device to create a buffer.
		\returns Pointer to the normal data contained in this object.
		*/
		char* NormalData() const;

		/**
		Returns the size (in bytes) of the normal data
		\returns the normal data size
		*/
		size_t NormalDataSize() const;

		/**
		Gets a pointer to the raw tex coord data contained in this object.  Useful to pass to a graphics device to create a buffer.
		\returns Pointer to the tex coord data contained in this object.
		*/
		char* TexCoordData() const;

		/**
		Gets the size (in bytes) of the tex coord data
		\returns the tex coord data size
		*/
		size_t TexCoordDataSize() const;

		/**
		Reserves space to hold a given number of vertices.
		\param size the number of verticies to allocate memory for.
		*/
		void AllocateVertices(size_t size);

		/**
		Reserves space to hold a given number of tex coords.
		\param size the number of tex coords to allocate memory for.
		*/
		void AllocateTexCoords(size_t size);

		/**
		Reserves space to hold a given number of normals.
		\param size the number of normals to allocate memory for.
		*/
		void AllocateNormals(size_t size);

		/**
		Adds a vertex to the geometry data
		\param position the vertex position
		\param normal the vertex normal
		*/
		void PushVertex(const rVector3& position);

		/**
		Sets the value of a given vertex
		\param index the index of the vertex to set
		\param position the vertex position value to set
		*/
		void SetVertex(size_t index, const rVector3& position);

		/**
		Gets the value of a given index.
		\param index the index of the vertex to get.
		\param position pointer to vector that will (if not null) receive the vertex position.
		\param normal pointer to vector that will (if not null) receive the vertex normal.
		*/
		void GetVertex(size_t index, rVector3& position);

		/**
		Sets the vertex data for this object.
		\param vertices pointer to array of vertex data.  This data will be copied.
		\param count the number of vertieces to assign.
		*/
		void PushVertices(rVector3* vertices, size_t count);

		/**
		Transforms the range of vertices by the given matrix
		\param start the starting vertex index
		\param count the number of vertices to transform
		\param matrix the matrix to use for transforming vertices
		*/
		void TransformVertices(size_t start, size_t count, const rMatrix4& matrix);

		/**
		Adds a tex coord to the geometry data.
		\param texCoord the tex coord to add.
		*/
		void PushTexCoord(const rVector2& texCoord);

		/**
		Sets the value of a tex coord at a given index.
		\param index the index of the texCoord to set.
		\param texCoord the texCoord value to set.
		*/
		void SetTexCoord(size_t index, const rVector2& texCoord);

		/**
		Gets the value of a tex coord at a given index.
		\param index the index of the texCoord to get.
		\param texCoord pointer to vector that will (if not null) receive the tex coord value.
		*/
		void GetTextCoord(size_t index, rVector2& texCoord);

		/**
		Sets the tex coord data for this object.
		\param texCoords pointer to array of tex coord data.  This data will be copied.
		\param count the number of tex coords to assign.
		*/
		void PushTexCoords(const rVector2* texCoords, size_t count);

		/**
		Gets whether this geometry data contains tex coords
		\returns value whether this geometry contains tex coords
		*/
		bool HasTexCoords() const;

		/**
		Adds a normal to the geometry data.
		\param normal the tex coord to add.
		*/
		void PushNormal(const rVector3& normal);

		/**
		Sets the value of a normal at a given index.
		\param index the index of the texCoord to set.
		\param normal the normal value to set.
		*/
		void SetNormal(size_t index, const rVector3& normal);

		/**
		Gets the value of a normalat a given index.
		\param index the index of the normal to get.
		\param normal pointer to vector that will (if not null) receive the normal value
		*/
		void GetNormal(size_t index, rVector3& normal);

		/**
		Sets the normal data for this object
		\param normals pointer to array of normal data. This data will be copied.
		\param count the number of normals to assign.
		*/
		void PushNormals(const rVector3* normals, size_t count);

		/**
		Gets whether this geometry data contains normals
		\returns value whether this geometry contains normals 
		*/
		bool HasNormals() const;

		/**
		Gets whether this geometry data contains vertex bone weights
		\returns whether this geometry contains vertex bone weights
		*/
		bool HasVertexBoneWeights() const;

		void AllocateVertexWeightData(size_t numVertices);
		bool AddVertexWeight(size_t vertexIndex, size_t boneIndex, float weight);
		size_t VertexBoneWeightsDataSize() const;
		size_t VertexBoneIndicesDataSize() const;

		const char* VertexBoneWeightData() const;
		const char* VertexBoneIndicesData() const;

		int Read(rIStream& stream);
		int Write(rOStream& stream);

		/**
		Removes all data from the object.
		*/
		void Clear();

	private:
		struct Impl;
		Impl* _impl;
	};
}
#endif
