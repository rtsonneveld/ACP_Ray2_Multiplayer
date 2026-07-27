#pragma once
#include <cstddef>

namespace R2MP::Constants {
	/** The maximum length of a player's username. */
	unsigned long constexpr MAX_PLAYER_NAME_LENGTH = 64;

	/** The maximum length of a level name. */
	unsigned long constexpr MAX_LEVEL_NAME_LENGTH = 32;
	/** How many bones are used to visualize another player **/
	unsigned long constexpr GHOST_NUMBONES = 6;
	/** Maximum distance a bone can be from the player's origin **/
	float constexpr GHOST_MAXBONEDIST = 2.0f;

	/** Amount of int32s used for the global bits array **/
	constexpr std::size_t GLOBAL_BITS_ARRAYSIZE = 45;
	constexpr std::size_t GLOBAL_BITS_NUMBITS = GLOBAL_BITS_ARRAYSIZE * 32;
}