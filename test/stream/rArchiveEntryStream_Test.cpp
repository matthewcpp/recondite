#include "gtest/gtest.h"

#include "stream/rIStringStream.hpp"
#include "stream/rArchiveStream.hpp"

#include <vector>

TEST(Stream_rArchiveEntryStream, Construct) {
	rString SAMPLE_DATA = "1234567890abcdef";
	size_t DATA_OFFSET = 7;
	rIStringStream* stringstream = new rIStringStream(SAMPLE_DATA);

	recondite::ArchiveEntryStream archviveEntry(stringstream, DATA_OFFSET, 7);
	EXPECT_EQ(archviveEntry.Pos(), 0);
	EXPECT_TRUE(archviveEntry.IsOk());
	EXPECT_EQ(stringstream->Pos(), DATA_OFFSET);
}

TEST(Stream_rArchiveEntryStream, SeekBeginning) {
	rString SAMPLE_DATA = "1234567890abcdef";
	size_t DATA_OFFSET = 7;
	size_t DATA_SIZE = 7;
	rIStringStream* stringstream = new rIStringStream(SAMPLE_DATA);

	recondite::ArchiveEntryStream archviveEntry(stringstream, DATA_OFFSET, DATA_SIZE);

	size_t SEEK_AMOUNT = 3;
	archviveEntry.Seek(SEEK_AMOUNT, rSeekMode::Beginning);
	EXPECT_EQ(archviveEntry.Pos(), SEEK_AMOUNT);
	EXPECT_EQ(stringstream->Pos(), DATA_OFFSET + SEEK_AMOUNT);
	EXPECT_EQ(archviveEntry.Peek(), SAMPLE_DATA[DATA_OFFSET + SEEK_AMOUNT]);

	SEEK_AMOUNT = 5;
	archviveEntry.Seek(SEEK_AMOUNT, rSeekMode::Beginning);
	EXPECT_EQ(archviveEntry.Pos(), SEEK_AMOUNT);
	EXPECT_EQ(stringstream->Pos(), DATA_OFFSET + SEEK_AMOUNT);
	EXPECT_EQ(archviveEntry.Peek(), SAMPLE_DATA[DATA_OFFSET + SEEK_AMOUNT]);

	SEEK_AMOUNT = 20;
	archviveEntry.Seek(SEEK_AMOUNT, rSeekMode::Beginning);
	EXPECT_EQ(archviveEntry.Pos(), DATA_SIZE);
	EXPECT_EQ(stringstream->Pos(), DATA_OFFSET + DATA_SIZE);
	EXPECT_EQ(archviveEntry.Peek(), EOF);
}

TEST(Stream_rArchiveEntryStream, SeekCurrent) {
	rString SAMPLE_DATA = "1234567890abcdef";
	size_t DATA_OFFSET = 7;
	size_t DATA_SIZE = 7;
	rIStringStream* stringstream = new rIStringStream(SAMPLE_DATA);

	recondite::ArchiveEntryStream archviveEntry(stringstream, DATA_OFFSET, DATA_SIZE);

	size_t SEEK1_AMOUNT = 1;
	archviveEntry.Seek(SEEK1_AMOUNT, rSeekMode::Current);
	EXPECT_EQ(archviveEntry.Pos(), SEEK1_AMOUNT);
	EXPECT_EQ(stringstream->Pos(), DATA_OFFSET + SEEK1_AMOUNT);

	size_t SEEK2_AMOUNT = 2;
	archviveEntry.Seek(SEEK2_AMOUNT, rSeekMode::Current);
	EXPECT_EQ(archviveEntry.Pos(), SEEK1_AMOUNT + SEEK2_AMOUNT);
	EXPECT_EQ(stringstream->Pos(), DATA_OFFSET + SEEK1_AMOUNT + SEEK2_AMOUNT);

	size_t SEEK3_AMOUNT = 20;
	archviveEntry.Seek(SEEK3_AMOUNT, rSeekMode::Current);
	EXPECT_EQ(archviveEntry.Pos(), DATA_SIZE);
	EXPECT_EQ(stringstream->Pos(), DATA_OFFSET + DATA_SIZE);
	EXPECT_EQ(archviveEntry.Peek(), EOF);
}

TEST(Stream_rArchiveEntryStream, SeekEnd) {
	rString SAMPLE_DATA = "1234567890abcdef";
	size_t DATA_OFFSET = 7;
	size_t DATA_SIZE = 7;
	rIStringStream* stringstream = new rIStringStream(SAMPLE_DATA);

	recondite::ArchiveEntryStream archviveEntry(stringstream, DATA_OFFSET, DATA_SIZE);

	size_t SEEK_AMOUNT = 1;
	archviveEntry.Seek(SEEK_AMOUNT, rSeekMode::End);
	EXPECT_EQ(archviveEntry.Pos(), DATA_SIZE - SEEK_AMOUNT);
	EXPECT_EQ(stringstream->Pos(), DATA_OFFSET + DATA_SIZE - SEEK_AMOUNT);

	SEEK_AMOUNT = 5;
	archviveEntry.Seek(SEEK_AMOUNT, rSeekMode::End);
	EXPECT_EQ(archviveEntry.Pos(), DATA_SIZE - SEEK_AMOUNT);
	EXPECT_EQ(stringstream->Pos(), DATA_OFFSET + DATA_SIZE - SEEK_AMOUNT);

	SEEK_AMOUNT = 20;
	archviveEntry.Seek(SEEK_AMOUNT, rSeekMode::End);
	EXPECT_EQ(archviveEntry.Pos(), 0);
	EXPECT_EQ(stringstream->Pos(), DATA_OFFSET);

	EXPECT_EQ(archviveEntry.Peek(), SAMPLE_DATA[DATA_OFFSET]);
}

TEST(Stream_rArchiveEntryStream, Get) {
	rString SAMPLE_DATA = "1234567890abcdef";
	size_t DATA_OFFSET = 0;
	size_t DATA_SIZE = 10;
	rIStringStream* stringstream = new rIStringStream(SAMPLE_DATA);

	recondite::ArchiveEntryStream archviveEntry(stringstream, DATA_OFFSET, DATA_SIZE);
	size_t pos = archviveEntry.Pos();
	char result;
	archviveEntry.Get(result);

	EXPECT_EQ(result, '1');
	EXPECT_EQ(archviveEntry.Pos(), pos + 1);

	archviveEntry.Get(result);

	EXPECT_EQ(result, '2');
	EXPECT_EQ(archviveEntry.Pos(), pos + 2);

	archviveEntry.Seek(0, rSeekMode::End);
	archviveEntry.Get(result);

	EXPECT_EQ(result, EOF);
}

TEST(Stream_rArchiveEntryStream, Read) {
	rString SAMPLE_DATA = "1234567890abcdef";
	size_t DATA_OFFSET = 1;
	size_t DATA_SIZE = 10;
	rIStringStream* stringstream = new rIStringStream(SAMPLE_DATA);

	recondite::ArchiveEntryStream archviveEntry(stringstream, DATA_OFFSET, DATA_SIZE);

	std::vector<char> buffer(10);

	archviveEntry.Read(buffer.data(), 5);
	rString str(buffer.data(), 5);
	EXPECT_EQ(str.compare(SAMPLE_DATA.substr(1, 5)), 0);
	EXPECT_EQ(archviveEntry.ReadCount(), 5);

	archviveEntry.Seek(1, rSeekMode::End);
	archviveEntry.Read(buffer.data(), 5);
	EXPECT_EQ(archviveEntry.ReadCount(), 1);
}

TEST(Stream_rArchiveEntryStream, ReadEnd) {
	rString SAMPLE_DATA = "1234567890abcdef";
	size_t DATA_OFFSET = 1;
	size_t DATA_SIZE = 10;
	rIStringStream* stringstream = new rIStringStream(SAMPLE_DATA);

	recondite::ArchiveEntryStream archviveEntry(stringstream, DATA_OFFSET, DATA_SIZE);

	std::vector<char> buffer(10);

	archviveEntry.Seek(1, rSeekMode::End);
	archviveEntry.Read(buffer.data(), 5);

	EXPECT_EQ(archviveEntry.ReadCount(), 1);
	EXPECT_EQ(buffer[0], 'a');
	EXPECT_EQ(archviveEntry.Peek(), EOF);
}