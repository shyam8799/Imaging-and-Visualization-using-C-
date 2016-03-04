
#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <sstream>
#ifndef CSVFILEREADER_H
#define CSVFILEREADER_H


class CSVFileReader
{
public:
    static std::vector < std::vector <float> > parseCSV(std::string fileName);
};

#endif // CSVFILEREADER_H
