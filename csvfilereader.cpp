#include "csvfilereader.h"

using namespace std;
std::vector < std::vector <float> > CSVFileReader::parseCSV(std::string fileName) {

    ifstream file(fileName);
    std::vector<float> value;
    std::vector <vector <float> >values;
    int count=0;

    string item;
    string line;

    while (getline(file, line)) {
        std::vector<float> value;
        std::istringstream in(line);
        while (getline(in, item, ',')) {
            value.push_back(atof(item.c_str()));
            count++;
        }
        values.push_back(value);
        count=0;
    }
    return values;
}
