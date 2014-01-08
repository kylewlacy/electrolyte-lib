#ifndef Electrolyte_base58_h
#define Electrolyte_base58_h

#include <boost/bimap.hpp>

namespace Electrolyte {
	class Base58 {
	public:
		static std::string encode(std::vector<uint8_t> const &data);
		static std::vector<uint8_t> decode(std::string const &str);
	protected:
		static char const* character_set;
	};
}

#endif
