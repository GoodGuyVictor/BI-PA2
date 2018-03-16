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
using namespace std;

const uint16_t ENDIAN_LITTLE = 0x4949;
const uint16_t ENDIAN_BIG    = 0x4d4d;

#endif /* __PROGTEST__ */

bool recodeImage ( const char  * srcFileName,
                   const char  * dstFileName,
                   int           interleave,
                   uint16_t      byteOrder )
{
    // todo
}

#ifndef __PROGTEST__
bool identicalFiles ( const char * fileName1,
                      const char * fileName2 )
{
    // DIY
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
