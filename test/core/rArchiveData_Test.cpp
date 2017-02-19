#include "gtest/gtest.h"

#include "rArchive.hpp"

#include "test/testcommon/TestFilesystem.hpp"

class Core_rArchiveData : public ::testing::Test {
protected:
	virtual void SetUp() {
		testFileSystem = new TestFilesystem();
	}

	virtual void TearDown() {
		delete testFileSystem;
	}

	TestFilesystem* testFileSystem;
};

TEST_F(Core_rArchiveData, SetKey_string) {
	rString TEST_DATA1 = "test1";
	rString TEST_PATH1 = "/test/path1";

	recondite::ArchiveData archiveData;
	archiveData.SetKeyFromData(TEST_PATH1, TEST_DATA1.c_str(), TEST_DATA1.size());

	ASSERT_TRUE(archiveData.HasKey(TEST_PATH1));
	ASSERT_EQ(archiveData.GetNumKeys(), 1);
}

TEST_F(Core_rArchiveData, SetKey_File) {
	rString TEST_DATA1 = "test1";
	rString TEST_PATH1 = "/test/path1";
	testFileSystem->SetSavedSata(TEST_PATH1, TEST_DATA1);

	recondite::ArchiveData archiveData;
	archiveData.SetKeyFromFilePath(TEST_PATH1, TEST_PATH1, testFileSystem->GetFileSize(TEST_PATH1));

	ASSERT_TRUE(archiveData.HasKey(TEST_PATH1));
	ASSERT_EQ(archiveData.GetNumKeys(), 1);
}

TEST_F(Core_rArchiveData, SetKey_Override_Data) {
	rString TEST_DATA1 = "test1";
	rString TEST_PATH1 = "/test/path1";
	rString TEST_DATA2 = "test2";

	recondite::ArchiveData archiveData;
	archiveData.SetKeyFromData(TEST_PATH1, TEST_DATA1.c_str(), TEST_DATA1.size());

	ASSERT_TRUE(archiveData.HasKey(TEST_PATH1));
	ASSERT_EQ(archiveData.GetNumKeys(), 1);

	archiveData.SetKeyFromData(TEST_PATH1, TEST_DATA2.c_str(), TEST_DATA2.size());

	ASSERT_TRUE(archiveData.HasKey(TEST_PATH1));
	ASSERT_EQ(archiveData.GetNumKeys(), 1);
}

TEST_F(Core_rArchiveData, SetKey_Override_File) {
	rString TEST_DATA1 = "test1";
	rString TEST_PATH1 = "/test/path1";
	rString TEST_DATA2 = "test2";
	rString TEST_PATH2 = "/test/path2";

	testFileSystem->SetSavedSata(TEST_PATH1, TEST_DATA1);
	testFileSystem->SetSavedSata(TEST_PATH2, TEST_DATA2);

	recondite::ArchiveData archiveData;
	archiveData.SetKeyFromFilePath(TEST_PATH1, TEST_PATH1, testFileSystem->GetFileSize(TEST_PATH1));

	ASSERT_TRUE(archiveData.HasKey(TEST_PATH1));
	ASSERT_EQ(archiveData.GetNumKeys(), 1);

	archiveData.SetKeyFromFilePath(TEST_PATH1, TEST_PATH2, testFileSystem->GetFileSize(TEST_PATH2));

	ASSERT_TRUE(archiveData.HasKey(TEST_PATH1));
	ASSERT_FALSE(archiveData.HasKey(TEST_PATH2));
	ASSERT_EQ(archiveData.GetNumKeys(), 1);
}

TEST_F(Core_rArchiveData, GetNumKeys) {
	rString TEST_DATA1 = "test1";
	rString TEST_PATH1 = "/test/path1";
	rString TEST_DATA2 = "test2";
	rString TEST_PATH2 = "/test/path2";
	rString TEST_DATA3 = "test3";
	rString TEST_PATH3 = "/test/path3";

	recondite::ArchiveData archiveData;
	archiveData.SetKeyFromData(TEST_PATH1, TEST_DATA1.c_str(), TEST_DATA1.size());
	ASSERT_EQ(archiveData.GetNumKeys(), 1);

	archiveData.SetKeyFromData(TEST_PATH2, TEST_DATA1.c_str(), TEST_DATA1.size());
	ASSERT_EQ(archiveData.GetNumKeys(), 2);

	archiveData.SetKeyFromData(TEST_PATH3, TEST_DATA1.c_str(), TEST_DATA1.size());
	ASSERT_EQ(archiveData.GetNumKeys(), 3);
}

TEST_F(Core_rArchiveData, DeleteKey) {
	rString TEST_DATA1 = "test1";
	rString TEST_PATH1 = "/test/path1";

	recondite::ArchiveData archiveData;
	archiveData.SetKeyFromData(TEST_PATH1, TEST_DATA1.c_str(), TEST_DATA1.size());

	ASSERT_TRUE(archiveData.HasKey(TEST_PATH1));
	ASSERT_EQ(archiveData.GetNumKeys(), 1);

	archiveData.DeleteKey(TEST_PATH1);

	ASSERT_FALSE(archiveData.HasKey(TEST_PATH1));
	ASSERT_EQ(archiveData.GetNumKeys(), 0);
}


