#pragma once

#include "rBuild.hpp"
#include "rDefs.hpp"

#include "interface/riResourceManager.hpp"
#include "rFileSystem.hpp"



namespace recondite {
	class RECONDITE_API ResourceManager : public iResourceManager {
	public:
		ResourceManager(rFileSystem* fileSystem);
		~ResourceManager();

	public:
		virtual rIStream* Open(const rString& handle) override;
		virtual bool Close(rIStream* stream) override;

		void SetFilesystemBasePath(const rString& basePath);

		bool OpenArchive(const rString& path);

	private:
		struct Impl;
		Impl* _impl;
	};
}
