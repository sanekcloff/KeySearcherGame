#pragma once

#include "KSCoreTypes.generated.h"

UENUM()
enum class EKSMatchState
{
    WaitingtoStart = 0,
    InProgress,
    Pause,
    GameOver,
    WinGame
};

DECLARE_MULTICAST_DELEGATE_OneParam(FOnMatchStateChangedSignature, EKSMatchState)
