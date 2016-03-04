#include "mhdhandler.h"

#include <fstream>
#include <map>
#include <exception>
#include <iostream>

#include "ioutilities.h"


Volume MHDHandler::read(const std::string& filename)
{

    std::cout << filename << std::endl;
    std::string metaFilename = filename;

    std::ifstream metaFile(metaFilename);
    if (!metaFile)
        throw std::invalid_argument("MHDHandler::read: error opening " + metaFilename + " for reading");

    std::map<std::string, std::string> attributes;





    // --- read in the meta file
    std::string line;
    while (!metaFile.eof()) {
        getline(metaFile, line);

        if (!line.length()) // empty line
            continue;

        // split into name and value
        auto delimPos = line.find('=');
        if (delimPos == std::string::npos) // ignore lines without name/value pair
            continue;

        // get and process name and value
        auto name  = line.substr(0, delimPos);
        auto value = line.substr(delimPos + 1);

        StringUtils::trim(name);
        //StringUtils::trim(value);
        StringUtils::tolower(name);

        attributes[name] = value;
        std::cout << name << "-" << value << std::endl;
    }
    metaFile.close();

    // --- now parse the meta attributes

    // get dimensions
    int dimensions;

    auto dimensionIter = attributes.find(TAG_DIMENSIONS);


    if (dimensionIter != attributes.end())
        dimensions = StringUtils::parseString<int>(dimensionIter->second);
    else
        throw std::runtime_error(std::string("MHDHandler::read: could not read required tag '") + TAG_DIMENSIONS + std::string("'"));



    // bail if dimensions is not 3 (NanuLib specific)
    if (dimensions != 3)
        throw std::runtime_error("MHDHandler::read: can only handle 3D data, sorry.");


    // get extents
    Eigen::VectorXi dimSizes(3);
    auto dimSizeIter = attributes.find(TAG_DIMSIZE);
    if (dimSizeIter != attributes.end()) {
        // extract the values, expected are exactly 'dimensions' integer values, separated by whitespaces
        const std::string dimSizeStr = dimSizeIter->second;
        std::stringstream convert(dimSizeStr);

        for (int i = 0; i < dimensions; ++i) {
            unsigned int value;
            convert >> value;
            if (convert.fail())
                throw std::runtime_error(std::string("MHDHandler::read: failed reading sizes from tag '") + TAG_DIMSIZE + std::string("'"));
            dimSizes(i) = value;
        }
    }
    else
        throw std::runtime_error(std::string("MHDHandler::read: could not read required tag '") + TAG_DIMSIZE + std::string("'"));


    // check for spacing
    Eigen::VectorXf dimSpacing = Eigen::VectorXf::Ones(dimensions);

    auto dimSpacingIter = attributes.find(TAG_SPACING);
    if (dimSpacingIter != attributes.end()) {
        // extract the values, expected are exactly 'dimensions' real values, separated by whitespaces
        std::string dimSpacingStr = dimSpacingIter->second;
        std::stringstream convert(dimSpacingStr);

        for (int i = 0; i < dimensions; ++i) {
            float value;
            convert >> value;
            if (convert.fail())
                throw std::runtime_error(std::string("MHDHandler::read: failed reading spacings from tag '") + TAG_SPACING + std::string("'"));
            dimSpacing(i) = value;
        }
    }


    // check for offset
    Eigen::VectorXf offset = Eigen::VectorXf::Zero(dimensions);
    auto offsetIter = attributes.find(TAG_OFFSET);
    if (offsetIter != attributes.end()) {
        // extract the values, expected are exactly 'dimensions' real values, separated by whitespaces
        std::string offsetStr = offsetIter->second;
        std::stringstream convert(offsetStr);

        for (int i = 0; i < dimensions; ++i) {
            float value;
            convert >> value;
            if (convert.fail())
                throw std::runtime_error(std::string("MHDHandler::read: failed reading offset from tag '") + TAG_OFFSET + std::string("'"));
            offset(i) = value;
        }
    }


    // check for byte order
    ByteOrder::ByteOrderEnum byteOrder = ByteOrder::DEFAULT;
    auto byteOrderIter = attributes.find(TAG_BYTEORDER);
    if (byteOrderIter != attributes.end()) {
        std::string value = byteOrderIter->second;
        StringUtils::trim(value);
        StringUtils::tolower(value);

        if (value == "true" || value == "yes")
            byteOrder = ByteOrder::HIGH_BYTE_FIRST;
        else if (value == "false" || value == "no")
            byteOrder = ByteOrder::LOW_BYTE_FIRST;
        else
            throw std::runtime_error(std::string("MHDHandler::read: could not read tag '") + TAG_BYTEORDER + std::string("'"));
    }


    // get data type
    DataTypes::DataTypeEnum dataType;
    auto dataTypeIter = attributes.find(TAG_TYPE);
    if (dataTypeIter != attributes.end()) {
        std::string dataTypeValue = dataTypeIter->second;
        StringUtils::trim(dataTypeValue);
        StringUtils::toupper(dataTypeValue);

        if (dataTypeValue == TYPE_CHAR)
            dataType = DataTypes::INT8;
        else if (dataTypeValue == TYPE_UCHAR)
            dataType = DataTypes::UINT8;
        else if (dataTypeValue == TYPE_SHORT)
            dataType = DataTypes::INT16;
        else if (dataTypeValue == TYPE_USHORT)
            dataType = DataTypes::UINT16;
        else if (dataTypeValue == TYPE_FLOAT)
            dataType = DataTypes::FLOAT32;
        else if (dataTypeValue == TYPE_DOUBLE)
            dataType = DataTypes::FLOAT64;
        else
            throw std::runtime_error(std::string("MHDHandler::read: unsupported value of tag '") + TAG_TYPE + std::string("'"));
    }
    else
        throw std::runtime_error(std::string("MHDHandler::read: could not read required tag '") + TAG_TYPE + std::string("'"));


    // get data relative file path
    std::string dataFilename;
    auto dataFileIter = attributes.find(TAG_DATAFILE);
    if (dataFileIter != attributes.end())
        dataFilename = dataFileIter->second;
    else
        throw std::runtime_error(std::string("MHDHandler::read: could not read required tag '") + TAG_DATAFILE + std::string("'"));

    // read in data file
    StringUtils::trim(dataFilename);
    std::cout << "*" << dataFilename << "*" << "*" << metaFilename << "*" << std::endl;
    std::ifstream dataFile(metaFilename + ".raw", std::ios::binary | std::ios::in);
    if (!dataFile)
        throw std::runtime_error("MHDHandler::read: could not open required raw file " + dataFilename + " for reading");

    bool byteShuffle = (byteOrder != ByteOrder::DEFAULT);
    Eigen::VectorXf data = DataTypes::parseData<float>(dataFile, dataType, dimSizes.prod(), byteShuffle);

    dataFile.close();

    Eigen::Vector3f lowerLeft = offset;
    Eigen::Vector3f upperRight = offset + (dimSizes.cast<float>().array() * dimSpacing.array() ).matrix();

    Volume vol(lowerLeft, upperRight, dimSpacing, dimSizes);
    vol.setContent(data);

    return vol;
}

void MHDHandler::write(std::string filename, Volume vol)
{

    std::string metaFilename  = filename + ".mhd";
    std::string dataFilename  = filename + ".mhd.raw";

    // write the meta file
    std::ofstream metaFile(metaFilename);
    if (!metaFile.good())
        throw std::runtime_error("MHDHandler::write: cannot open " + metaFilename + " for writing");

    metaFile << TAG_DIMENSIONS << " = 3\n";
    metaFile << TAG_DIMSIZE    << " = " << vol.getNumVoxels().transpose() << "\n";
    metaFile << TAG_SPACING    << " = " << vol.getDimSpacing().transpose() << "\n";
    metaFile << TAG_TYPE       << " = " << TYPE_FLOAT << "\n";
    metaFile << TAG_BYTEORDER  << " = " << ( (ByteOrder::DEFAULT == ByteOrder::HIGH_BYTE_FIRST) ? "true" : "false") << "\n";
    metaFile << TAG_OFFSET     << " = " << Eigen::Vector3f(0,0,0).transpose() << "\n";
    metaFile << TAG_DATAFILE   << " = " << dataFilename << "\n";
    metaFile.close();

    // write the data file
    std::ofstream dataFile(dataFilename, std::ios::binary | std::ios::out);
    if (!dataFile.good())
        throw std::runtime_error("MHDHandler::write: cannot open " + dataFilename + " for writing");

    dataFile.write(reinterpret_cast<const char*>(vol.getContent().data()), vol.getNumVoxels().prod() * sizeof(float) );
    dataFile.close();
}

