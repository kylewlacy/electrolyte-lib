#include <iostream>
#include <boost/multiprecision/cpp_int.hpp>

#include "Base58.h"

using namespace std;
using big_int = boost::multiprecision::cpp_int;

namespace Electrolyte {
	char const* Base58::character_set = "123456789ABCDEFGHJKLMNPQRSTUVWXYZabcdefghijkmnopqrstuvwxyz";
	
	string Base58::encode(vector<uint8_t> const &data) {
		big_int int_data = 0;
		
		for(uint8_t byte : data) {
			int_data <<= sizeof(uint8_t)*8;
			int_data += byte;
		}
		
		string result = "";
		while(int_data > 0) {
			int remainder = big_int(int_data % 58).convert_to<int>();
			int_data /= 58;
			result += character_set[remainder];
		}
		
		for(uint8_t byte : data) {
			if(byte != 0) {
				break;
			}
			
			result += '1';
		}
		
		reverse(result.begin(), result.end()); // Little endian to big endian
		return result;
	}

	vector<uint8_t> Base58::decode(string const &base58) {
		big_int int_data = 0;
		
		for(char base58_char : base58) {
			char *char_offset = strchr(character_set, base58_char);
			if(char_offset == NULL) {
				throw logic_error(string("Not a base58 character: ") + base58_char);
			}
			
			uint8_t value = uint8_t(char_offset - character_set);
			int_data = int_data * 58 + value;
		}
		
		// TODO: Merge with other for loop
		int leading_zero_count = 0;
		for(char base58_char : base58) {
			if(base58_char != '1') {
				break;
			}
			
			leading_zero_count++;
		}
		
		
		vector<uint8_t> data;
		while(int_data > 0) {
			big_int end_byte = int_data % (1 << sizeof(uint8_t)*8);
			data.push_back(end_byte.convert_to<uint8_t>());
			
			int_data >>= sizeof(uint8_t)*8;
		}
		
		for(int i = 0; i < leading_zero_count; i++) {
			data.push_back(0);
		}
		
		
		
		reverse(data.begin(), data.end()); // Big endian to little endian
		return data;
	}
}
