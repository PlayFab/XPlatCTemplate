#include "stdafx.h"
#include <playfab/PFEntity.h>
#include "GlobalState.h"

using namespace PlayFab;

HRESULT PFEntityRegisterTokenExpiredEventHandler(
    _In_opt_ XTaskQueueHandle queue,
    _In_opt_ void* context,
    _In_ PFEntityTokenExpiredEventHandler* handler,
    _Out_ PFRegistrationToken* token
) noexcept
{
    SharedPtr<GlobalState> state;
    RETURN_IF_FAILED(GlobalState::Get(state));

    return state->TokenExpiredHandler().RegisterClientHandler(
        state->RunContext().DeriveOnQueue(queue),
        context,
        handler,
        token
    );
}

void PFEntityUnregisterTokenExpiredEventHandler(
    _In_ PFRegistrationToken token
) noexcept
{
    SharedPtr<GlobalState> state;
    GlobalState::Get(state);
    if (state)
    {
        state->TokenExpiredHandler().UnregisterClientHandler(token);
    }
}
