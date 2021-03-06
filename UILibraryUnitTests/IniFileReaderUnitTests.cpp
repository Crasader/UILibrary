#include "IniFileReader.h"

using namespace Microsoft::VisualStudio::TestTools::UnitTesting;
using namespace std;

namespace UILibraryUnitTests
{
    [TestClass]
    public ref class IniFileReaderUnitTests
    {
    public: 
        [TestMethod]
        void CanHandleNonExistantFile()
        {
            Assert::AreEqual(0, (int) IniFileReader::LoadFile("THIS FILE DOES NOT EXIST.INI").size());
        };

        [TestMethod]
        [DeploymentItem("..\\UnitTestDeploymentData\\empty.ini")]
        void IniFileReaderReturnsEmptyVectorWhenLoadingEmptyFile()
        {
            Assert::IsTrue(System::IO::File::Exists("empty.ini"));

            Assert::AreEqual(0, (int) IniFileReader::LoadFile("empty.ini").size());
        }

        [TestMethod]
        [DeploymentItem("..\\UnitTestDeploymentData\\single entry.ini")]
        void IniFileReaderReadsSingleIniEntry()
        {
            Assert::IsTrue(System::IO::File::Exists("single entry.ini"));

            vector<IniSection> readIniData = IniFileReader::LoadFile("single entry.ini");

            Assert::AreEqual(1, (int) readIniData.size());
            Assert::AreEqual(0, strcmp("ini header", readIniData[0].sectionName.c_str()));

            Assert::AreEqual(1, (int) readIniData[0].propertyMap.size());
            Assert::AreEqual(0, strcmp("value", readIniData[0].propertyMap["name"].c_str()));
        }

        [TestMethod]
        [DeploymentItem("..\\UnitTestDeploymentData\\single entry internal whitespace padded header.ini")]
        void IniFileReaderReadsSingleIniEntryWithWhitespacePaddedHeader()
        {
            Assert::IsTrue(System::IO::File::Exists("single entry internal whitespace padded header.ini"));

            vector<IniSection> readIniData = IniFileReader::LoadFile("single entry internal whitespace padded header.ini");

            Assert::AreEqual(1, (int)readIniData.size());
            Assert::AreEqual(0, strcmp("ini header", readIniData[0].sectionName.c_str()));

            Assert::AreEqual(1, (int)readIniData[0].propertyMap.size());
            Assert::AreEqual(0, strcmp("value", readIniData[0].propertyMap["name"].c_str()));
        }

        [TestMethod]
        [DeploymentItem("..\\UnitTestDeploymentData\\single entry external whitespace padded header.ini")]
        void IniFileReaderStripsWhitespaceFromHeaderTitle()
        {
            Assert::IsTrue(System::IO::File::Exists("single entry external whitespace padded header.ini"));

            vector<IniSection> readIniData = IniFileReader::LoadFile("single entry external whitespace padded header.ini");

            Assert::AreEqual(1, (int)readIniData.size());
            Assert::AreEqual(0, strcmp("ini header", readIniData[0].sectionName.c_str()));

            Assert::AreEqual(1, (int)readIniData[0].propertyMap.size());
            Assert::AreEqual(0, strcmp("value", readIniData[0].propertyMap["name"].c_str()));
        }

        [TestMethod]
        [DeploymentItem("..\\UnitTestDeploymentData\\multiple entries.ini")]
        void IniFileReaderReadsMultipleIniEntries()
        {
            Assert::IsTrue(System::IO::File::Exists("multiple entries.ini"));

            vector<IniSection> readIniData = IniFileReader::LoadFile("multiple entries.ini");

            Assert::AreEqual(2, (int)readIniData.size());
            Assert::AreEqual(0, strcmp("ini header 1", readIniData[0].sectionName.c_str()));

            Assert::AreEqual(1, (int)readIniData[0].propertyMap.size());
            Assert::AreEqual(0, strcmp("value1", readIniData[0].propertyMap["name1"].c_str()));

            Assert::AreEqual(0, strcmp("ini header 2", readIniData[1].sectionName.c_str()));

            Assert::AreEqual(2, (int)readIniData[1].propertyMap.size());
            Assert::AreEqual(0, strcmp("value2", readIniData[1].propertyMap["name2"].c_str()));
            Assert::AreEqual(0, strcmp("value3", readIniData[1].propertyMap["name3"].c_str()));
        }

        [TestMethod]
        [DeploymentItem("..\\UnitTestDeploymentData\\single entry with missing value.ini")]
        void IniFileReaderReadsSingleIniEntryWithMissingValue()
        {
            Assert::IsTrue(System::IO::File::Exists("single entry with missing value.ini"));

            vector<IniSection> readIniData = IniFileReader::LoadFile("single entry with missing value.ini");

            Assert::AreEqual(1, (int)readIniData.size());
            Assert::AreEqual(0, strcmp("ini header", readIniData[0].sectionName.c_str()));

            Assert::AreEqual(1, (int)readIniData[0].propertyMap.size());
            Assert::AreEqual(0, strcmp("", readIniData[0].propertyMap["name"].c_str()));
        }

        [TestMethod]
        [DeploymentItem("..\\UnitTestDeploymentData\\value pair without header.ini")]
        void IniFileReaderReadsValuePairsWithNoHeader()
        {
            Assert::IsTrue(System::IO::File::Exists("value pair without header.ini"));

            vector<IniSection> readIniData = IniFileReader::LoadFile("value pair without header.ini");

            Assert::AreEqual(0, (int)readIniData.size());
        }

        [TestMethod]
        [DeploymentItem("..\\UnitTestDeploymentData\\single entry with noise after header.ini")]
        void IniFileReaderTrimsNoiseAfterHeader()
        {
            Assert::IsTrue(System::IO::File::Exists("single entry with noise after header.ini"));

            vector<IniSection> readIniData = IniFileReader::LoadFile("single entry with noise after header.ini");

            Assert::AreEqual(1, (int)readIniData.size());
            Assert::AreEqual(0, strcmp("ini header", readIniData[0].sectionName.c_str()));

            Assert::AreEqual(1, (int)readIniData[0].propertyMap.size());
            Assert::AreEqual(0, strcmp("value", readIniData[0].propertyMap["name"].c_str()));
        }
    };
}
