#include "gtest/gtest.h"

#include "rPath.hpp"
#include "rString.hpp"

class Core_rPath : public ::testing::Test {
};

TEST(Core_rPath, Directory) {
	rString path = "C:\\dir1\\dir2\\file.txt";
	rString directory = rPath::Directory(path);
	EXPECT_STREQ(directory.c_str(), "C:\\dir1\\dir2");

	path = "/usr/test/docs/file.txt";
	directory = rPath::Directory(path);
	EXPECT_STREQ(directory.c_str(), "/usr/test/docs");

	path = "dir1\\file.txt";
	directory = rPath::Directory(path);
	EXPECT_STREQ(directory.c_str(), "dir1");

	path = "file.txt";
	directory = rPath::Directory(path);
	EXPECT_STREQ(directory.c_str(), "");

	path = "";
	directory = rPath::Directory(path);
	EXPECT_STREQ(directory.c_str(), "");

	path = "C:/dir1/dir2/file.txt";
	directory = rPath::Directory(path);
	EXPECT_STREQ(directory.c_str(), "C:/dir1/dir2");

	path = "dir1/file.txt";
	directory = rPath::Directory(path);
	EXPECT_STREQ(directory.c_str(), "dir1");

	path = "file.txt";
	directory = rPath::Directory(path);
	EXPECT_STREQ(directory.c_str(), "");

	path = "";
	directory = rPath::Directory(path);
	EXPECT_STREQ(directory.c_str(), "");
}

TEST(Core_rPath, Filename) {
	rString path = "C:\\dir1\\dir2\\file.txt";
	rString filename = rPath::Filename(path);
	EXPECT_STREQ(filename.c_str(), "file");

	path = "/usr/test/docs/file.txt";
	filename = rPath::Filename(path);
	EXPECT_STREQ(filename.c_str(), "file");

	path = "dir1/file.txt";
	filename = rPath::Filename(path);
	EXPECT_STREQ(filename.c_str(), "file");

	path = "dir1\\file.foo.txt";
	filename = rPath::Filename(path);
	EXPECT_STREQ(filename.c_str(), "file.foo");

	path = "dir1/file";
	filename = rPath::Filename(path);
	EXPECT_STREQ(filename.c_str(), "file");

	path = "file.txt";
	filename = rPath::Filename(path);
	EXPECT_STREQ(filename.c_str(), "file");

	path = "file.foo.txt";
	filename = rPath::Filename(path);
	EXPECT_STREQ(filename.c_str(), "file.foo");

	path = "file";
	filename = rPath::Filename(path);
	EXPECT_STREQ(filename.c_str(), "file");

	path = "";
	filename = rPath::Filename(path);
	EXPECT_STREQ(filename.c_str(), "");
}

TEST(Core_rPath, FullFilename) {
	rString path = "C:\\dir1\\dir2\\file.txt";
	rString filename = rPath::FullFilename(path);
	EXPECT_STREQ(filename.c_str(), "file.txt");

	path = "/usr/test/docs/file.txt";
	filename = rPath::FullFilename(path);
	EXPECT_STREQ(filename.c_str(), "file.txt");

	path = "dir1/file.txt";
	filename = rPath::FullFilename(path);
	EXPECT_STREQ(filename.c_str(), "file.txt");

	path = "dir1\\file.foo.txt";
	filename = rPath::FullFilename(path);
	EXPECT_STREQ(filename.c_str(), "file.foo.txt");

	path = "dir1/file";
	filename = rPath::FullFilename(path);
	EXPECT_STREQ(filename.c_str(), "file");

	path = "file.txt";
	filename = rPath::FullFilename(path);
	EXPECT_STREQ(filename.c_str(), "file.txt");

	path = "file.foo.txt";
	filename = rPath::FullFilename(path);
	EXPECT_STREQ(filename.c_str(), "file.foo.txt");

	path = "file";
	filename = rPath::FullFilename(path);
	EXPECT_STREQ(filename.c_str(), "file");

	path = "";
	filename = rPath::FullFilename(path);
	EXPECT_STREQ(filename.c_str(), "");
}

TEST(Core_rPath, Extension) {
	rString path = "C:\\dir1\\dir2\\file.txt";
	rString ext = rPath::Extension(path);
	EXPECT_STREQ(ext.c_str(), "txt");

	path = "/usr/test/docs/file.txt";
	ext = rPath::Extension(path);
	EXPECT_STREQ(ext.c_str(), "txt");

	path = "dir1/file.txt";
	ext = rPath::Extension(path);
	EXPECT_STREQ(ext.c_str(), "txt");

	path = "dir1\\file.foo.txt";
	ext = rPath::Extension(path);
	EXPECT_STREQ(ext.c_str(), "txt");

	path = "dir1/file";
	ext = rPath::Extension(path);
	EXPECT_STREQ(ext.c_str(), "");

	path = "file.txt";
	ext = rPath::Extension(path);
	EXPECT_STREQ(ext.c_str(), "txt");

	path = "file.foo.txt";
	ext = rPath::Extension(path);
	EXPECT_STREQ(ext.c_str(), "txt");

	path = "file";
	ext = rPath::Extension(path);
	EXPECT_STREQ(ext.c_str(), "");

	path = "";
	ext = rPath::Extension(path);
	EXPECT_STREQ(ext.c_str(), "");
}

TEST(Core_rPath, Combine) {
	rString dir = "C:/temp";
	rString filename = "test.text";
	rString expect = dir + rPath::PathSeparator + filename;
	rString result = rPath::Combine(dir, filename);
	EXPECT_STREQ(expect.c_str(), result.c_str());

	dir = "C:/temp/";
	filename = "test.text";
	expect = dir + filename;
	result = rPath::Combine(dir, filename);
	EXPECT_STREQ(expect.c_str(), result.c_str());

	dir = "C:/temp\\";
	filename = "test.text";
	expect = dir + filename;
	result = rPath::Combine(dir, filename);
	EXPECT_STREQ(expect.c_str(), result.c_str());

	dir = "temp";
	filename = "test.text";
	expect = dir + rPath::PathSeparator + filename;
	result = rPath::Combine(dir, filename);
	EXPECT_STREQ(expect.c_str(), result.c_str());

	dir = "temp";
	filename = "";
	expect = dir;
	result = rPath::Combine(dir, filename);
	EXPECT_STREQ(expect.c_str(), result.c_str());

	dir = "";
	filename = "file";
	expect = filename;
	result = rPath::Combine(dir, filename);
	EXPECT_STREQ(expect.c_str(), result.c_str());

	dir = "";
	filename = "";
	expect = "";
	result = rPath::Combine(dir, filename);
	EXPECT_STREQ(expect.c_str(), result.c_str());
}

TEST(Core_rPath, Assemble) {
	rString dir = "C:/temp";
	rString filename = "test";
	rString ext = "text";
	rString expect = dir + rPath::PathSeparator + filename+ '.' + ext;
	rString result = rPath::Assemble(dir, filename, ext);
	EXPECT_STREQ(expect.c_str(), result.c_str());

	dir = "C:/temp/";
	filename = "test";
	ext = "text";
	expect = dir + filename + '.' + ext;
	result = rPath::Assemble(dir, filename, ext);
	EXPECT_STREQ(expect.c_str(), result.c_str());

	dir = "C:\\temp\\";
	filename = "test";
	ext = "text";
	expect = dir + filename + '.' + ext;
	result = rPath::Assemble(dir, filename, ext);
	EXPECT_STREQ(expect.c_str(), result.c_str());

	dir = "/temp/folder/";
	filename = "test";
	ext = "text";
	expect = dir + filename + '.' + ext;
	result = rPath::Assemble(dir, filename, ext);
	EXPECT_STREQ(expect.c_str(), result.c_str());

	dir = "/temp/folder/";
	filename = "test";
	ext = ".text";
	expect = dir + filename + ext;
	result = rPath::Assemble(dir, filename, ext);
	EXPECT_STREQ(expect.c_str(), result.c_str());

	dir = "folder";
	filename = "test";
	ext = ".text";
	expect = dir + rPath::PathSeparator+ + filename + ext;
	result = rPath::Assemble(dir, filename, ext);
	EXPECT_STREQ(expect.c_str(), result.c_str());
}

TEST(Core_rPath, Split) {
	rString path = "C:/users/admin/documents/important_file.doc";
	rString dir, filename, ext;
	rPath::Split(path, &dir, &filename, &ext);
	EXPECT_STREQ(dir.c_str(), "C:/users/admin/documents");
	EXPECT_STREQ(filename.c_str(), "important_file");
	EXPECT_STREQ(ext.c_str(), "doc");

	dir.clear(); filename.clear(); ext.clear();
	rPath::Split(path, nullptr, &filename, &ext);
	EXPECT_TRUE(dir.empty());
	EXPECT_STREQ(filename.c_str(), "important_file");
	EXPECT_STREQ(ext.c_str(), "doc");

	dir.clear(); filename.clear(); ext.clear();
	rPath::Split(path, nullptr, nullptr, &ext);
	EXPECT_TRUE(dir.empty());
	EXPECT_TRUE(filename.empty());
	EXPECT_STREQ(ext.c_str(), "doc");

	dir.clear(); filename.clear(); ext.clear();
	rPath::Split(path, nullptr, nullptr, nullptr);
	EXPECT_TRUE(dir.empty());
	EXPECT_TRUE(filename.empty());
	EXPECT_TRUE(ext.empty());

	dir.clear(); filename.clear(); ext.clear();
	path = "C:\\users\\admin\\documents\\important_file";
	rPath::Split(path, &dir, &filename, &ext);
	EXPECT_STREQ(dir.c_str(), "C:\\users\\admin\\documents");
	EXPECT_STREQ(filename.c_str(), "important_file");
	EXPECT_TRUE(ext.empty());

	dir.clear(); filename.clear(); ext.clear();
	path = "C:\\users\\admin\\documents\\important_file\\";
	rPath::Split(path, &dir, &filename, &ext);
	EXPECT_STREQ(dir.c_str(), "C:\\users\\admin\\documents\\important_file");
	EXPECT_TRUE(filename.empty());
	EXPECT_TRUE(ext.empty());

	dir.clear(); filename.clear(); ext.clear();
	path = "C:\\users\\admin\\documents/important file.doc.docx";
	rPath::Split(path, &dir, &filename, &ext);
	EXPECT_STREQ(dir.c_str(), "C:\\users\\admin\\documents");
	EXPECT_STREQ(filename.c_str(), "important file.doc");
	EXPECT_STREQ(ext.c_str(), "docx");
}

TEST(Core_rPath, PopComponent) {
	rString path = "/path/to/my/file.txt";
	rString result = rPath::PopComponent(path);

	EXPECT_STREQ(result.c_str(), "/path/to/my");

	result = rPath::PopComponent("");
	EXPECT_STREQ(result.c_str(), "");

	path = "/path/to/my";
	result = rPath::PopComponent(path);
	EXPECT_STREQ(result.c_str(), "/path/to");

	result = rPath::PopComponent("myfile.txt");
	EXPECT_STREQ(result.c_str(), "");
}