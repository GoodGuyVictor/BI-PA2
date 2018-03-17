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

class CImage
{
private:
    char *m_contents;
//    char *m_header;
    struct THeader {
        char endianness[2];
        char width[2];
        char height[2];
        char format[1];
    } m_header;
public:

    CImage(char*, char*);
    CImage(const char*, int, uint16_t);   //building new image based on interleave
    char* decode()const;
    bool isValid()const;
};

CImage::CImage(char * hdr, char * cont)
{
    m_header.endianness[0] = hdr[0];
    m_header.endianness[1] = hdr[1];
    m_header.width[1] = hdr[2];
    m_header.width[0] = hdr[3];
    m_header.height[1] = hdr[4];
    m_header.height[0] = hdr[5];
    m_header.format[0] = hdr[6];
    m_contents = cont;
}

ostream& operator << (ostream& os, const CImage& img) {

}

bool recodeImage ( const char  * srcFileName,
                   const char  * dstFileName,
                   int           interleave,
                   uint16_t      byteOrder ) {
    string tmpPath("/home/victor/githubRepos/BI-PA2/HomeWork-1/");
    tmpPath = tmpPath + srcFileName;


    const uint8_t HEADER_SIZE = 8;
    streampos contents_size;
    char *header;
    char *contents;
    ifstream inputFile(tmpPath, ios::binary|ios::ate);

    //reading .img file and saving its contents into buffer
    if (inputFile.is_open())
    {
        contents_size = inputFile.tellg() - HEADER_SIZE;
        header = new char[HEADER_SIZE];
        contents = new char[contents_size];

        //reading header
        inputFile.seekg(0, ios::beg);
        inputFile.read(header, HEADER_SIZE);
        //reading contents
        inputFile.read(contents, contents_size);
        inputFile.close();
    } else {
        return false;
    }

    CImage inputImage(header, contents);
    delete [] header;

    if (!inputImage.isValid())
        return false;


    /**************************************/
    char *decoded_contents = inputImage.decode();
    CImage outputImage(decoded_contents, interleave, byteOrder);

    ofstream outputFile(dstFileName, ios::binary);
    if(outputFile.is_open()) {
        outputFile << outputImage;
    }
}

#ifndef __PROGTEST__
bool identicalFiles ( const char * fileName1,
                      const char * fileName2 )
{
    // DIY
}

int main ( void )
{
//    streampos size;
//    char * memblock;
//
//    ifstream file ("/home/victor/githubRepos/BI-PA2/HomeWork-1/input_00.img", ios::in|ios::binary|ios::ate);
//    if (file.is_open())
//    {
//        size = file.tellg();
//        memblock = new char [size];
//        file.seekg (0, ios::beg);
//        file.read (memblock, size);
//        file.close();
//        cout << memblock[5];
//        delete[] memblock;
//    }
//    else cout << "Unable to open file";


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

    // extra inputs (optional & bonus tests)
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
             && identicalFiles ( "extra_out_11.img", "extra_ref_11.img" ) );

    return 0;
}
#endif /* __PROGTEST__ */
