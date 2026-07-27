#pragma once

#include <ACP_Ray2.h>

namespace R2MP::CPA::Actor {

    template <typename T>
    T* GetDsgVarPtr(HIE_tdstEngineObject* actor, uint32_t dsgVarIndex)
    {
        if (!actor || !actor->hBrain || !actor->hBrain->p_stMind)
            return NULL;

        AI_tdstAIModel* aiModel = actor->hBrain->p_stMind->p_stAIModel;
        AI_tdstDsgMem* dsgMem = actor->hBrain->p_stMind->p_stDsgMem;

        if (!aiModel || !aiModel->p_stDsgVar)
            return NULL;

        if (dsgVarIndex < 0 || dsgVarIndex >= aiModel->p_stDsgVar->ucNbDsgVar)
            return NULL;

        AI_tdstDsgVarInfo info = aiModel->p_stDsgVar->a_stDsgVarInfo[dsgVarIndex];
        return (T*)(dsgMem->p_cDsgMemBuffer + info.ulOffsetInDsgMem);
    }

    template <typename T, typename EnumT>
        requires std::is_enum_v<EnumT>
    T* GetDsgVarPtr(HIE_tdstEngineObject* actor, EnumT dsgVarIndex)
    {
        return GetDsgVarPtr<T>(actor, static_cast<uint32_t>(dsgVarIndex));
    }
}