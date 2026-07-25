#pragma once
#include <map>
#include <optional>
#include <vector>
#include "characterstate.h"

namespace R2MP {

	class StateManager {
	private:
		std::map<unsigned long, CharacterState> CharacterStates;
	public:
		void Initialize();
		std::optional<CharacterState> GetCharacterState(unsigned long playerId);
		void SetCharacterState(unsigned long playerId, const CharacterState& state);
		void ClearCharacterState(unsigned long playerId);
	};

}