#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PInteractionInterface.generated.h"

UINTERFACE(MinimalAPI)
class UPInteractionInterface : public UInterface
{
	GENERATED_BODY()
};

class MYTHIARYGAMEJAM_API IPInteractionInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Interact(APawn* Instigator);
};
