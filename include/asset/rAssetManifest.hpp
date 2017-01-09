#pragma once

#include <vector>

#include "rBuild.hpp"
#include "rDefs.hpp"

#include "rString.hpp"

#include "stream/rIStream.hpp"
#include "stream/rOStream.hpp"

#include "xml/rXMLDocument.hpp"


namespace recondite {
	/**
	Encapsulates a set of Assets
	*/
	class RECONDITE_API AssetManifest {
	public:
		/**
		Adds an asset into the manifest
		\param type the type of asset
		\param name the name of this asset
		\param the path to the asset
		*/
		void Add(rAssetType type, const rString& name, const rString& path);
		
		/**
		Removes an asset by name
		\param type the type of asset to remove
		\param name the name of this asset to remove
		\returns boolean indicating if an asset with the given name was removed
		*/
		bool RemoveByName(rAssetType type, const rString& name);

		/**
		Removes an asset by index
		\param type the type of asset to remove
		\param index the index of the asset to remove
		\returns boolean indicating if the operation was sucessfull
		*/
		bool RemoveByIndex(rAssetType type, size_t index);

		/**
		Gets the number of assets of a particular type
		\param type the type of asset
		\returns the number of assets for the given type
		*/
		size_t Count(rAssetType type) const;

		/**
		Gets information about a particular asset
		\param type the type of asset
		\param index the index of the asset
		\param name string which will receive the asset's name
		\param path string which will receive the asset's path
		\returns boolean indicating if the operation was sucessfull
		*/
		bool Get(rAssetType type, size_t index, rString& name, rString& path) const;

		/**
		Removes all entries from the manifest
		*/
		void Clear();

		/**
		Removes all entries of a particular asset type
		\param type the type of asset
		*/
		void Clear(rAssetType type);

		/**
		Reads manifest data from an input stream
		\param stream an input stream to read from
		\returns 0 on success, non 0 on failure
		*/
		int Read(rIStream& stream);

		/**
		Reads manifest data from an XML Document.  This method assumes that that the supplied document's root element has a child element named <assets>.
		\param document XML document to read from.
		\returns 0 on success, non 0 on failure
		*/
		int Read(const rXMLDocument& document);

		/**
		Writes manifest data to an output stream
		\param stream an output stream to write to
		\returns 0 on success, non 0 on failure
		*/
		int Write(rOStream& stream) const;

		/**
		Writes manifest data to an XML Document.  This method assumes that the document already has a root node created.  
		A new element titles <assets> will be created to contain asset data.
		\param stream an output stream to write to
		\returns 0 on success, non 0 on failure
		*/
		int Write(rXMLDocument& document) const;
	
		struct ContentEntry {
			rString name;
			rString path;

			ContentEntry(const rString& n, const rString& p) : name(n), path(p) {}
		};

	private:
		typedef std::vector<ContentEntry> ContentVector;
		const ContentVector& _Content(rAssetType type) const;

		void WriteNodes(const std::vector<AssetManifest::ContentEntry>& contentVector, const rString& type, rXMLElement* assetsNode) const;
		void ReadNodes(rXMLElement* parentElement);

	private:
		std::vector<ContentEntry> _models;
	};
}
