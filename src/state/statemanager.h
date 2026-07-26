#pragma once
#include <unordered_map>
#include <optional>
#include <vector>
#include "characterstate.h"

namespace R2MP {

	class StateManager {
	private:
		std::unordered_map<unsigned long, CharacterState> CharacterStates;
	public:
		void Initialize();
		std::optional<CharacterState> GetCharacterState(unsigned long playerId);
		void SetCharacterState(unsigned long playerId, const CharacterState& state);
		void ClearCharacterState(unsigned long playerId);
		const std::unordered_map<unsigned long, CharacterState>& GetCharacterStates();
	};

}