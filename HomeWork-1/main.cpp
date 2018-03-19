#ifndef __PROGTEST__
#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <cstring>
#include <cassert>
#include <cmath>
#include <cctype>
#include <climits>

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <list>
#include <algorithm>
#include <functional>
#include <memory>
#include <string>
using namespace std;

const uint16_t ENDIAN_LITTLE = 0x4949;
const uint16_t ENDIAN_BIG    = 0x4d4d;

#endif /* __PROGTEST__ */

struct TCoordinate
{
    uint64_t m_col;
    uint64_t m_row;
    TCoordinate(const uint64_t r, const uint64_t c)
    : m_col(c), m_row(r)
    {}
};

class CConverter
{
private:
    int m_recievedInterleave;
    uint32_t m_recievedWidth;
    uint32_t m_recievedHeight;
    vector<uint64_t> m_cols;  //list of cols that are multiplied by interleave
    vector<uint64_t> m_rows;  //list of m_rows that are multiplied by interleave
    vector<TCoordinate> m_coordinatesList;   //coordinates list is based upon width, height and interleave
    vector<uint32_t> m_indexList;   //coordinates list converted into indexes of 1d array

    bool isInList(TCoordinate crdnt)
    {
        for(uint32_t i = 0; i < m_coordinatesList.size(); i++) {
            if(m_coordinatesList[i].m_col == crdnt.m_col
               && m_coordinatesList[i].m_row == crdnt.m_row)
                return true;
        }
        return false;
    }

    void composeCoordinatesList()
    {
        int curr_interleave = m_recievedInterleave;
        while(curr_interleave > 0) {
            for (uint32_t i = 0; i < m_recievedHeight; ++i)
                if (i % curr_interleave == 0)
                    for (uint32_t j = 0; j < m_recievedWidth; ++j)
                        if (j % curr_interleave == 0)
                            if (!isInList(TCoordinate(i, j)))
                                m_coordinatesList.emplace_back(TCoordinate(i, j));
            curr_interleave /= 2;
        }
    }

    void composeIndexList()
    {
        //traditional method (without iterator)
        for (uint64_t i = 0; i < m_coordinatesList.size() ; ++i) {
            m_indexList.push_back(m_coordinatesList[i].m_row * m_recievedWidth + m_coordinatesList[i].m_col);
        }
    }

public:
    CConverter(int, uint32_t, uint32_t);
    vector<uint32_t > getIndexList()
    {
        composeCoordinatesList();
        composeIndexList();
        return m_indexList;
    }
};

CConverter::CConverter(int intrlv, uint32_t w, uint32_t h)
        :m_recievedInterleave(intrlv), m_recievedWidth(w), m_recievedHeight(h)
{}

class CImage
{
private:
    char *m_contents;
    char *m_headerText;
    int m_number_of_pixels;
    struct THeader {
        uint16_t endianness;
        uint32_t width;
        uint32_t height;
        uint8_t format;
        int interleave;
        uint8_t channels;
        uint8_t transfer;
    } m_header;

    uint16_t toInt(char lw, char hg)
    {
        uint16_t lobyte = (uint16_t )lw;
        uint16_t hibyte = (uint16_t )hg;
        hibyte = hibyte << 8;
        uint16_t result = (hibyte | lobyte);

        return result;
    }

    bool validInterleave() const
    {
        switch(m_header.interleave) {
            case 1: return true;
            case 2: return true;
            case 4: return true;
            case 8: return true;
            case 16: return true;
            case 32: return true;
            case 64: return true;
            default: return false;
        }
    }

    void buildHeader()
    {
        if (m_header.endianness == ENDIAN_BIG) {
            m_headerText[0] = 0x4d;
            m_headerText[1] = 0x4d;
        } else {
            m_headerText[0] = 0x49;
            m_headerText[1] = 0x49;
        }
        m_headerText[6] = (char)(m_headerText[6] & 31);
        switch(m_header.interleave) {
            case 2: { m_headerText[6] = (char)(m_headerText[6] | 32); break; }
            case 4: { m_headerText[6] = (char)(m_headerText[6] | 64); break; }
            case 8: { m_headerText[6] = (char)(m_headerText[6] | 96); break; }
            case 16: { m_headerText[6] = (char)(m_headerText[6] | 128); break; }
            case 32: { m_headerText[6] = (char)(m_headerText[6] | 160); break; }
            case 64: { m_headerText[6] = (char)(m_headerText[6] | 192); break; }
        }
    }

public:

    CImage(char* hdr, char* cont, int);
    CImage(char*, char**, int , uint16_t, int);   //building new image based on interleave
    char** decode()const;
    bool isValid()const;
    bool saveToFile(const char * dstFile);
};

CImage::CImage(char * hdr, char * cont, int bytes)
{
    m_headerText = hdr;
    m_header.endianness = toInt(hdr[0], hdr[1]);
    m_header.width = toInt(hdr[2], hdr[3]);
    m_header.height = toInt(hdr[4], hdr[5]);
    m_header.format = (uint8_t)hdr[6];
    int interleave = (m_header.format & 224);
    switch (interleave) {
        case 0: { m_header.interleave = 1; break; }
        case 32: { m_header.interleave = 2; break; }
        case 64: { m_header.interleave = 4; break; }
        case 96: { m_header.interleave = 8; break; }
        case 128: { m_header.interleave = 16; break; }
        case 160: { m_header.interleave = 32; break; }
        case 192: { m_header.interleave = 64; break; }
        default: m_header.interleave = 0; //for error
    }
    uint8_t transfer = (uint8_t)(m_header.format & 28);
    switch (transfer) {
        case 0: { m_header.transfer = 1; break; }
        case 12: { m_header.transfer = 8; break; }
        case 16: { m_header.transfer = 16; break; }
        default: m_header.transfer = 0; //for error
    }
    uint8_t channels = (uint8_t)(m_header.format & 3);
    switch (channels) {
        case 0: { m_header.channels = 1; break; }
        case 2: { m_header.channels = 3; break; }
        case 3: { m_header.channels = 4; break; }
        default: m_header.channels = 0; //for error
    }
    m_number_of_pixels = bytes / m_header.channels;
    m_contents = cont;
}

char ** CImage::decode() const
{
    CConverter converter(m_header.interleave, m_header.width, m_header.height);
    vector<uint32_t> indexes = converter.getIndexList();
    uint32_t contents_size_header = m_header.width * m_header.height;
    uint32_t contents_size_body = m_header.width * m_header.height * m_header.channels;

//    vector<vector<char>> decoded_contents(contents_size_header, vector<char>(m_header.channels));
    char **decoded_contents = new char*[contents_size_header];
    for (uint32_t i = 0; i < contents_size_header; ++i) {
        decoded_contents[i] = new char[m_header.channels];
    }
    uint32_t i = 0;
    uint32_t j = 0;
    uint32_t pos = indexes[i];
    for(uint32_t k = 0; k < contents_size_body; k++) {
        decoded_contents[pos][j++] = m_contents[k];
        if(j == m_header.channels) {
            pos = indexes[++i];
            j = 0;
        }
    }
    return decoded_contents;
}

CImage::CImage(char * hdr, char** dc, int intrlv, uint16_t bo, int bytes)
{
    m_headerText = hdr;
    m_header.interleave = intrlv;
    m_header.endianness = bo;
    m_header.width = toInt(hdr[2], hdr[3]);
    m_header.height = toInt(hdr[4], hdr[5]);
    m_header.format = (uint8_t)hdr[6];
    m_header.format = (uint8_t)(m_header.format & 31);
    switch(intrlv) {
        case 2: { m_header.format = (uint8_t)(m_header.format | 32); break; }
        case 4: { m_header.format = (uint8_t)(m_header.format | 64); break; }
        case 8: { m_header.format = (uint8_t)(m_header.format | 96); break; }
        case 16: { m_header.format = (uint8_t)(m_header.format | 128); break; }
        case 32: { m_header.format = (uint8_t)(m_header.format | 160); break; }
        case 64: { m_header.format = (uint8_t)(m_header.format | 192); break; }
    }
    uint8_t transfer = (uint8_t)(m_header.format & 28);
    switch (transfer) {
        case 0: { m_header.transfer = 1; break; }
        case 12: { m_header.transfer = 8; break; }
        case 16: { m_header.transfer = 16; break; }
        default: m_header.transfer = 0; //for error
    }
    uint8_t channels = (uint8_t)(m_header.format & 3);
    switch (channels) {
        case 0: { m_header.channels = 1; break; }
        case 2: { m_header.channels = 3; break; }
        case 3: { m_header.channels = 4; break; }
        default: m_header.channels = 0; //for error
    }
    m_number_of_pixels = bytes / m_header.channels;
    buildHeader();

    CConverter converter(m_header.interleave, m_header.width, m_header.height);
    vector<uint32_t> indexes = converter.getIndexList();
    uint32_t contents_size_body = m_header.width * m_header.height * m_header.channels;
    uint32_t contents_size_header = m_header.width * m_header.height;
    m_contents = new char[contents_size_body];

    int k = 0;
    for (uint32_t i = 0; i < contents_size_header; ++i) {
        uint32_t pos = indexes[i];
        for (int j = 0; j < m_header.channels; ++j) {
            m_contents[k++] = dc[pos][j];
        }
    }
}

bool CImage::isValid() const
{
    int expectedVolume = m_header.width * m_header.height;
    int actualVolume = m_number_of_pixels;
    if(expectedVolume != actualVolume)
        return false;
    if(!validInterleave())
        return false;
    return true;
}

bool CImage::saveToFile(const char *dstFile)
{
    const uint8_t HEADER_SIZE = 8;
    uint32_t contents_size = m_header.width * m_header.height * m_header.channels;

    ofstream outputFile(dstFile, ios::binary);
    if(outputFile.is_open()) {
        outputFile.write(m_headerText, HEADER_SIZE);
        outputFile.write(m_contents, contents_size);
        outputFile.close();
        return true;
    } else return false;
}

bool recodeImage ( const char  * srcFileName,
                   const char  * dstFileName,
                   int           interleave,
                   uint16_t      byteOrder ) {
    string tmpPath("/home/victor/githubRepos/BI-PA2/HomeWork-1/");
    tmpPath = tmpPath + srcFileName;


    const uint8_t HEADER_SIZE = 8;
    uint64_t contents_size;
    char *header;
    char *contents;
    ifstream inputFile(tmpPath, ios::binary|ios::ate);
    streamsize bytes;

    //reading .img file and saving its contents into buffers *header and *contents
    if (inputFile.is_open())
    {
        contents_size = (uint64_t)inputFile.tellg() - HEADER_SIZE;
        header = new char[HEADER_SIZE];
        contents = new char[contents_size];

        //reading header
        inputFile.seekg(0, ios::beg);
        inputFile.read(header, HEADER_SIZE);
        //reading contents
        inputFile.read(contents, contents_size);
        bytes = inputFile.gcount();
        inputFile.close();
    } else {
        return false;
    }

    CImage inputImage(header, contents, (int)bytes);
    if (!inputImage.isValid())
        return false;

    char** decoded_contents = inputImage.decode();
    CImage outputImage(header, decoded_contents, interleave, byteOrder, (int)bytes);
    if(!outputImage.isValid())
        return false;
    return outputImage.saveToFile(dstFileName);
}

#ifndef __PROGTEST__
bool identicalFiles ( const char * fileName1,
                      const char * fileName2 )
{
    return true;
}

int main ( void )
{
    assert ( recodeImage ( "input_00.img", "output_00.img", 1, ENDIAN_LITTLE )
             && identicalFiles ( "output_00.img", "ref_00.img" ) );

    assert ( recodeImage ( "input_01.img", "output_01.img", 8, ENDIAN_LITTLE )
             && identicalFiles ( "output_01.img", "ref_01.img" ) );

    assert ( recodeImage ( "input_02.img", "output_02.img", 8, ENDIAN_LITTLE )
             && identicalFiles ( "output_02.img", "ref_02.img" ) );

    assert ( recodeImage ( "input_03.img", "output_03.img", 2, ENDIAN_LITTLE )
             && identicalFiles ( "output_03.img", "ref_03.img" ) );

    assert ( recodeImage ( "input_04.img", "output_04.img", 1, ENDIAN_LITTLE )
             && identicalFiles ( "output_04.img", "ref_04.img" ) );

    assert ( recodeImage ( "input_05.img", "output_05.img", 1, ENDIAN_LITTLE )
             && identicalFiles ( "output_05.img", "ref_05.img" ) );

    assert ( recodeImage ( "input_06.img", "output_06.img", 8, ENDIAN_LITTLE )
             && identicalFiles ( "output_06.img", "ref_06.img" ) );

    assert ( recodeImage ( "input_07.img", "output_07.img", 4, ENDIAN_LITTLE )
             && identicalFiles ( "output_07.img", "ref_07.img" ) );

    assert ( recodeImage ( "input_08.img", "output_08.img", 8, ENDIAN_LITTLE )
             && identicalFiles ( "output_08.img", "ref_08.img" ) );

    assert ( ! recodeImage ( "input_09.img", "output_09.img", 1, ENDIAN_LITTLE ) );

    assert ( ! recodeImage ( "input_10.img", "output_10.img", 5, ENDIAN_LITTLE ) );

   /* // extra inputs (optional & bonus tests)
    assert ( recodeImage ( "extra_input_00.img", "extra_out_00.img", 8, ENDIAN_LITTLE )
             && identicalFiles ( "extra_out_00.img", "extra_ref_00.img" ) );
    assert ( recodeImage ( "extra_input_01.img", "extra_out_01.img", 4, ENDIAN_BIG )
             && identicalFiles ( "extra_out_01.img", "extra_ref_01.img" ) );
    assert ( recodeImage ( "extra_input_02.img", "extra_out_02.img", 16, ENDIAN_BIG )
             && identicalFiles ( "extra_out_02.img", "extra_ref_02.img" ) );
    assert ( recodeImage ( "extra_input_03.img", "extra_out_03.img", 1, ENDIAN_LITTLE )
             && identicalFiles ( "extra_out_03.img", "extra_ref_03.img" ) );
    assert ( recodeImage ( "extra_input_04.img", "extra_out_04.img", 8, ENDIAN_LITTLE )
             && identicalFiles ( "extra_out_04.img", "extra_ref_04.img" ) );
    assert ( recodeImage ( "extra_input_05.img", "extra_out_05.img", 4, ENDIAN_LITTLE )
             && identicalFiles ( "extra_out_05.img", "extra_ref_05.img" ) );
    assert ( recodeImage ( "extra_input_06.img", "extra_out_06.img", 16, ENDIAN_BIG )
             && identicalFiles ( "extra_out_06.img", "extra_ref_06.img" ) );
    assert ( recodeImage ( "extra_input_07.img", "extra_out_07.img", 1, ENDIAN_BIG )
             && identicalFiles ( "extra_out_07.img", "extra_ref_07.img" ) );
    assert ( recodeImage ( "extra_input_08.img", "extra_out_08.img", 8, ENDIAN_LITTLE )
             && identicalFiles ( "extra_out_08.img", "extra_ref_08.img" ) );
    assert ( recodeImage ( "extra_input_09.img", "extra_out_09.img", 4, ENDIAN_LITTLE )
             && identicalFiles ( "extra_out_09.img", "extra_ref_09.img" ) );
    assert ( recodeImage ( "extra_input_10.img", "extra_out_10.img", 16, ENDIAN_BIG )
             && identicalFiles ( "extra_out_10.img", "extra_ref_10.img" ) );
    assert ( recodeImage ( "extra_input_11.img", "extra_out_11.img", 1, ENDIAN_BIG )
             && identicalFiles ( "extra_out_11.img", "extra_ref_11.img" ) );*/

    return 0;
}
#endif /* __PROGTEST__ */
