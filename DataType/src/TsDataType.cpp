#include "TsDataType.h"

DataStructure_SDP::iso1Part4_Security_TYPE cc_hexTls = 0x00;
DataStructure_SDP::iso1Part4_Security_TYPE cc_hexTcp = 0x10;

int cc_proximity_type1 = 1;
int cc_proximity_type2_AC_13A = 13;
int cc_proximity_type2_AC_20A = 20;
int cc_proximity_type2_AC_32A = 32;
int cc_proximity_type2_AC_63A = 63;
int cc_proximity_type2_DC = 2;

std::string cc_EvseId_NotSup = "";

float cc_maximum_value_physicalValue_case1 = 300;// a
float cc_maximum_value_physicalValue_case2 = 1000;//380;// v
float cc_maximum_value_physicalValue_case3 = 0;// ??
float cc_maximum_value_physicalValue_case4 = 200000;// w
uint64_t cc_maximum_value_meterReading = 0xFFFFFFFF;