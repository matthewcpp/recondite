#include "gtest/gtest.h"

#include "rArchive.hpp"

#include "test/testcommon/TestFilesystem.hpp"

#include <map>

class Core_rArchive : public ::testing::Test {
protected:
	TestFilesystem* testFileSystem;

	virtual void SetUp() {
		testFileSystem = new TestFilesystem();
	}

	virtual void TearDown() {
		delete testFileSystem;
	}

	typedef std::map<rString, rString> ArchiveMap;
	void CreateArchive(const rString& path, const ArchiveMap& archiveMap) {
		recondite::ArchiveData archiveData;

		for (auto& item : archiveMap) {
			archiveData.SetKeyFromData(item.first, item.second.c_str(), item.second.size());
		}

		auto archiveOut = testFileSystem->OpenWriteFileRef(path);
		archiveData.Write(*archiveOut);

		testFileSystem->CloseWriteFileRef(archiveOut);
	}
	
};

TEST_F(Core_rArchive, OpenArchive) {
	rString ARCHIVE_PATH = "/test/archive1";
	rString TEST_DATA1 = "test1";
	rString TEST_PATH1 = "/test/path1";
	ArchiveMap archiveMap;
	archiveMap[TEST_PATH1] = TEST_DATA1;
	CreateArchive(ARCHIVE_PATH, archiveMap);

	recondite::Archive archive(testFileSystem);

	EXPECT_TRUE(archive.LoadFromFilesystem(ARCHIVE_PATH));
}

TEST_F(Core_rArchive, OpenArchiveEmpty) {
	rString ARCHIVE_PATH = "/test/archive1";
	ArchiveMap archiveMap;
	CreateArchive(ARCHIVE_PATH, archiveMap);

	recondite::Archive archive(testFileSystem);

	EXPECT_TRUE(archive.LoadFromFilesystem(ARCHIVE_PATH));
}

TEST_F(Core_rArchive, IsOpen) {
	rString ARCHIVE_PATH = "/test/archive1";
	ArchiveMap archiveMap;
	CreateArchive(ARCHIVE_PATH, archiveMap);

	recondite::Archive archive(testFileSystem);
	EXPECT_FALSE(archive.IsOpen());

	EXPECT_TRUE(archive.LoadFromFilesystem(ARCHIVE_PATH));
	EXPECT_TRUE(archive.IsOpen());

	archive.Close();
	EXPECT_FALSE(archive.IsOpen());
}

TEST_F(Core_rArchive, HasKey) {
	rString ARCHIVE_PATH = "/test/archive1";
	ArchiveMap archiveMap;

	for (size_t i = 0; i < 10; i++) {
		rOStringStream path;
		path << "/test/file" << i;
		archiveMap[path.Str()] = "data";
	}

	CreateArchive(ARCHIVE_PATH, archiveMap);

	recondite::Archive archive(testFileSystem);
	archive.LoadFromFilesystem(ARCHIVE_PATH);

	for (size_t i = 0; i < 10; i++) {
		rOStringStream path;
		path << "/test/file" << i;
		EXPECT_TRUE(archive.HasKey(path.Str()));
	}
}


TEST_F(Core_rArchive, GetNumKeys) {
	rString ARCHIVE_PATH = "/test/archive1";
	ArchiveMap archiveMap;

	for (size_t i = 0; i < 3; i++) {
		rOStringStream path;
		path << "/test/file" << i;
		archiveMap[path.Str()] = "data";
	}

	CreateArchive(ARCHIVE_PATH, archiveMap);

	recondite::Archive archive(testFileSystem);
	archive.LoadFromFilesystem(ARCHIVE_PATH);

	EXPECT_EQ(archive.GetNumKeys(), 3);
}

TEST_F(Core_rArchive, GetKeyByIndex) {
	rString ARCHIVE_PATH = "/test/archive1";
	ArchiveMap archiveMap;

	for (size_t i = 0; i < 10; i++) {
		rOStringStream path;
		path << "/test/file" << i;
		archiveMap[path.Str()] = "data";
	}

	CreateArchive(ARCHIVE_PATH, archiveMap);

	recondite::Archive archive(testFileSystem);
	archive.LoadFromFilesystem(ARCHIVE_PATH);

	for (size_t i = 0; i < 10; i++) {
		rString key;
		EXPECT_TRUE(archive.GetKeyByIndex(i, key));
		EXPECT_GT(archiveMap.count(key), 0U);
	}
}

TEST_F(Core_rArchive, OpenStreamValid) {
	rString ARCHIVE_PATH = "/test/archive1";
	rString TEST_DATA1 = "test1";
	rString TEST_PATH1 = "/test/path1";
	ArchiveMap archiveMap;
	archiveMap[TEST_PATH1] = TEST_DATA1;
	CreateArchive(ARCHIVE_PATH, archiveMap);

	recondite::Archive archive(testFileSystem);
	archive.LoadFromFilesystem(ARCHIVE_PATH);
	rIStream* archiveStream = archive.OpenStream(TEST_PATH1);
	EXPECT_NE(archiveStream, nullptr);
	EXPECT_EQ(archiveStream->Pos(), 0);
}

TEST_F(Core_rArchive, OpenStreamInvalid) {
	rString ARCHIVE_PATH = "/test/archive1";
	rString TEST_DATA1 = "test1";
	rString TEST_PATH1 = "/test/path1";
	ArchiveMap archiveMap;
	archiveMap[TEST_PATH1] = TEST_DATA1;
	CreateArchive(ARCHIVE_PATH, archiveMap);

	recondite::Archive archive(testFileSystem);
	archive.LoadFromFilesystem(ARCHIVE_PATH);
	rIStream* archiveStream = archive.OpenStream("/invalid/path");
	EXPECT_EQ(archiveStream, nullptr);
}