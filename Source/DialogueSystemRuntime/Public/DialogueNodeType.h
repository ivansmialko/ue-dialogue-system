#pragma once

#include "DialogueNodeType.generated.h"

UENUM()
enum class EDialogueNodeType : uint8
{
	EDNT_Unknown,
	EDNT_Start,
	EDNT_Line,
	EDNT_End
};