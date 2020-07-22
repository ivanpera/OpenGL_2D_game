#ifndef ENT_KEY
#define ENT_KEY
#include <string>
#include "HashCombine.h"
typedef struct EntityKey {
	int const layer;
	std::string const meshName;
} EntityKey;

namespace std {

	template<> struct less<EntityKey> {
		bool operator () (EntityKey const& lhs, EntityKey const& rhs) const {
			if (lhs.layer == rhs.layer) {				
				return lhs.meshName.compare(rhs.meshName) > 0;
			}
			return lhs.layer < rhs.layer;
		}
	};

	template<> struct hash<EntityKey> {
		size_t operator()(EntityKey const& key) const {
			std::size_t seed = 0;
			hash_combine(seed, key.layer, key.meshName);
			return seed;
		}
	};
}

#endif 


