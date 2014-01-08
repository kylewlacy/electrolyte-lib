#define BOOST_TEST_MODULE Base58Test
#include <iostream>
#include <vector>
#include <boost/assign.hpp>
#include <boost/test/included/unit_test.hpp>

#include "Base58.h"

using namespace std;
using namespace boost::assign;

namespace Electrolyte {
	namespace Test {
		struct Base58ByteArray {
			string base58;
			vector<uint8_t> data;
			
			Base58ByteArray(string _base58, vector<uint8_t> _data) : base58(_base58), data(_data) { }
		};
		
		struct EncodeDecodeFixture {
			vector<Base58ByteArray> test_cases;
			EncodeDecodeFixture() {
				test_cases = {
					Base58ByteArray("",                                   { }),
					Base58ByteArray("2g",                                 { 0x61 }),
					Base58ByteArray("a3gV",                               { 0x62, 0x62, 0x62 }),
					Base58ByteArray("aPEr",                               { 0x63, 0x63, 0x63 }),
					Base58ByteArray("1112",                               { 0x00, 0x00, 0x00, 0x01 }),
					Base58ByteArray("3EFU7m",                             { 0x57, 0x2E, 0x47, 0x94 }),
					Base58ByteArray("Rt5zm",                              { 0x10, 0xc8, 0x51, 0x1E }),
					Base58ByteArray("ABnLTmg",                            { 0x51, 0x6B, 0x6F, 0xCD, 0x0F }),
					Base58ByteArray("3SEo3LWLoPntC",                      { 0xBF, 0x4F, 0x89, 0x00, 0x1E, 0x67, 0x02, 0x74, 0xDD }),
					Base58ByteArray("EJDM8drfXA6uyA",                     { 0xEC, 0xAC, 0x89, 0xCA, 0xD9, 0x39, 0x23, 0xC0, 0x23, 0x21 }),
					Base58ByteArray("111111111111111",                    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }),
					Base58ByteArray("2cFupjhnEsSn59qHXstmK2ffpLv2",       { 0x73, 0x69, 0x6D, 0x70, 0x6C, 0x79, 0x20, 0x61, 0x20, 0x6C, 0x6F, 0x6E, 0x67, 0x20, 0x73, 0x74, 0x72, 0x69, 0x6E, 0x67 }),
					Base58ByteArray("1NS17iag9jJgTHD1VXjvLCEnZuQ3rJDE9L", { 0x00, 0xEB, 0x15, 0x23, 0x1D, 0xFC, 0xEB, 0x60, 0x92, 0x58, 0x86, 0xB6, 0x7D, 0x06, 0x52, 0x99, 0x92, 0x59, 0x15, 0xAE, 0xB1, 0x72, 0xC0, 0x66, 0x47 }),
				};
			}
		};
		
		BOOST_FIXTURE_TEST_CASE(Base58_encode, EncodeDecodeFixture) {
			for(auto test_case : test_cases) {
				BOOST_CHECK_EQUAL(Base58::encode(test_case.data), test_case.base58);
			}
		}
	}
}