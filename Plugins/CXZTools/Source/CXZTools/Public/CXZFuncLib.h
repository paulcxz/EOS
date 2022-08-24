#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "structs.h"
#include "libxl.h"
#include "enum.h"
#include "Json.h"
//#include "SImage.h"
#include "MediaTexture.h"
#include <Engine/EngineTypes.h>
#include "IImageWrapper.h"
#include "IImageWrapperModule.h"
#include "CXZFuncLib.generated.h"

using namespace libxl;
/**
 *
 */
UCLASS()
class CXZTOOLS_API UCXZFuncLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintPure,Category = "CXZ Tools")
	static FString CXZBase64Encode(const FString& Source);

	UFUNCTION(BlueprintPure,Category = "CXZ Tools")
	static bool CXZBase64Decode(const FString& Source,FString& Result);

	UFUNCTION(BlueprintPure,Category = "CXZ Tools")
	static float CXZGetUniformScale(APlayerController* PlayerController,FVector TargetLocation);

	UFUNCTION(BlueprintPure,Category = "CXZ Tools")
	static float CXZCalc2VectorsAngleDegrees(const FVector& V1,const FVector& V2,const FVector& Up);

	UFUNCTION(BlueprintPure,Category = "CXZ Tools")
	static bool CXZScreenPosPercentageVector(const APlayerController* Player,const float x,const float y,FVector& WorldOrigin,FVector& WorldDirection);

	UFUNCTION(BlueprintPure,Category = "CXZ Tools")
	static void CXZGetAbsolutePosition(const FGeometry Geometry,FVector2D& Position);

	UFUNCTION(BlueprintPure,Category = "CXZ Tools",meta=(AutoCreateRefTerm="ActorsToIgnore"))
	static bool CXZLineTraceFromScreenPosPercentage(const APlayerController* Player,ETraceTypeQuery TraceChannel,const TArray<AActor*>& ActorsToIgnore,bool bIgnoreSelf,bool bTraceComplex,const float x,const float y,FHitResult& HitResult);

	UFUNCTION(BlueprintCallable,Category = "CXZ Tools")
	static UMediaTexture* CXZCreateMediaTexture(/*UMediaPlayer& InMediaPlayer*/);

private:
	
	static FCollisionQueryParams ConfigureCollisionParams(FName TraceTag,bool bTraceComplex,const TArray<AActor*>& ActorsToIgnore,bool bIgnoreSelf,const UObject* WorldContextObject);

};