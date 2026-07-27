#pragma once

namespace R2MP::Constants {
	/** The maximum length of a player's username. */
	unsigned long const MAX_PLAYER_NAME_LENGTH = 64;

	/** The maximum length of a level name. */
	unsigned long const MAX_LEVEL_NAME_LENGTH = 32;
	/** How many bones are used to visualize another player **/
	unsigned long const GHOST_NUMBONES = 6;
	/** Maximum distance a bone can be from the player's origin **/
	float const GHOST_MAXBONEDIST = 2.0f;
}