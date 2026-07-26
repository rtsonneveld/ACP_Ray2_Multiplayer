#include "statemanager.h"

namespace R2MP {
	void StateManager::Initialize() {
		CharacterStates = std::unordered_map<unsigned long, CharacterState>();
	}

	std::optional<CharacterState> StateManager::GetCharacterState(unsigned long playerId) {
		if (CharacterStates.find(playerId) == CharacterStates.end()) {
			return {};
		}

		return CharacterStates[playerId];
	}

	void StateManager::SetCharacterState(unsigned long playerId, const CharacterState& state) {
		CharacterStates[playerId] = state;
	}

	void StateManager::ClearCharacterState(unsigned long playerId) {
		CharacterStates.erase(playerId);
	}

	const std::unordered_map<unsigned long, CharacterState>& StateManager::GetCharacterStates()
	{
		return CharacterStates;
	}

}