#include "volume.h"

#ifndef MHDHANDLER_H
#define MHDHANDLER_H

#include <string>




/**
 * \brief MHDHandler reads and writes MHD files.
 */

class MHDHandler {
public:
    /* \brief read an MHD file into a Volume
     * \param[in] filename - filename of the MHD file to be read
     * \return volume containing the data
     */
    static Volume read(const std::string& filename);

    /* \brief write out a Volume into an MHD file
     * \param[in] filename - filename of the MHD file to be written
     * \param[in] vol      - volume to be written
     */
    static void write(std::string filename, Volume vol);

private:
    static constexpr auto TAG_DIMENSIONS  = "ndims";
    static constexpr auto TAG_DIMSIZE     = "dimsize";
    static constexpr auto TAG_BYTEORDER   = "elementbyteordermsb";
    static constexpr auto TAG_TYPE        = "elementtype";
    static constexpr auto TAG_DATAFILE    = "elementdatafile";
    static constexpr auto TAG_SPACING     = "elementspacing";
    static constexpr auto TAG_OFFSET      = "offset";

    static constexpr auto TYPE_CHAR   = "MET_CHAR";
    static constexpr auto TYPE_UCHAR  = "MET_UCHAR";
    static constexpr auto TYPE_SHORT  = "MET_SHORT";
    static constexpr auto TYPE_USHORT = "MET_USHORT";
    static constexpr auto TYPE_FLOAT  = "MET_FLOAT";
    static constexpr auto TYPE_DOUBLE = "MET_DOUBLE";
};


#endif // MHDHANDLER_H
