#include "CXZFuncLib.h"
#include "CXZTools.h"
#include "Modules/ModuleManager.h"
#include <SocketSubsystem.h>
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

float UCXZFuncLib::CXZCalc2VectorsAngleDegrees(const FVector& V1,const FVector& V2,const FVector& Up)
{
	FVector v1 = UKismetMathLibrary::Normal(V1,0);
	FVector v2 = UKismetMathLibrary::Normal(V2,0);
	//FVector v1 = V1;
	//FVector v2 = V2;
	//v1.Normalize(0);
	//v2.Normalize(0);

	float dot = FVector::DotProduct(v1,v2);
	float absdeg = UKismetMathLibrary::DegAcos(dot);

	//FVector v3;
	//v3.X = abs(v1.Y * v2.Z - v1.Z * v2.Y);
	//v3.Y = abs(v1.Z * v2.X - v1.X * v2.Z);
	//v3.Z = abs(v1.X * v2.Y - v1.Y * v2.X);

	FVector vecRotated = v1.RotateAngleAxis(absdeg,Up);
	
	float ret = absdeg;
	if(!v2.Equals(vecRotated,0.0001))
	{
		ret = absdeg * -1;
	}
	return ret;
}

FString UCXZFuncLib::CXZBase64Encode(const FString& Source)
{
	return FBase64::Encode(Source);
}

bool UCXZFuncLib::CXZBase64Decode(const FString& Source,FString& Result)
{
	return FBase64::Decode(Source,Result);
}

float UCXZFuncLib::CXZGetUniformScale(APlayerController* PlayerController,FVector TargetLocation)
{
	if(!PlayerController)
	{
		return -1;
	}
	ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(PlayerController->Player);
	if(!LocalPlayer)
	{
		return -2;
	}
	FSceneInterface* psi = PlayerController->GetWorld()->Scene;
	//= GEngine->GetWorld()->Scene;
	FSceneViewFamilyContext ViewFamily(FSceneViewFamily::ConstructionValues(
		LocalPlayer->ViewportClient->Viewport,
		psi,
		LocalPlayer->ViewportClient->EngineShowFlags)
		.SetRealtimeUpdate(true));



	FVector ViewLocation;
	FRotator ViewRotation;
	FSceneView* View = LocalPlayer->CalcSceneView(&ViewFamily, /*out*/ ViewLocation, /*out*/ ViewRotation,LocalPlayer->ViewportClient->Viewport);
	float UniformScale = -3;
	if(View)
		UniformScale = View->WorldToScreen(TargetLocation).W * (4.0f / View->UnscaledViewRect.Width() / View->ViewMatrices.GetProjectionMatrix().M[0][0]);

	return UniformScale;
}

bool UCXZFuncLib::CXZLineTraceFromScreenPosPercentage(const APlayerController* Player,ETraceTypeQuery TraceChannel,const TArray<AActor*>& ActorsToIgnore,bool bIgnoreSelf,bool bTraceComplex,const float x,const float y,FHitResult& HitResult)
{
	if(!IsValid(Player))
		return false;
	if(GEngine == nullptr)
	{
		return false;
	}
	UGameViewportClient* ViewportClient = GEngine->GameViewport;
	if(ViewportClient == nullptr)
	{
		return false;
	}
	FViewport* Viewport = ViewportClient->Viewport;
	if(Viewport == nullptr)
	{
		return false;
	}

	const TArray<ULocalPlayer*>& PlayerList = ViewportClient->GetOuterUEngine()->GetGamePlayers(ViewportClient);

	const ESplitScreenType::Type SplitType = ViewportClient->GetCurrentSplitscreenConfiguration();


	FIntPoint Size = Viewport->GetSizeXY();
	ULocalPlayer* pLPlayer = Player->GetLocalPlayer();
	FVector2D Position;
	FVector2D FSizePercent;
	FVector2D Origin;

	ECollisionChannel CollisionChannel = UEngineTypes::ConvertToCollisionChannel(TraceChannel);

	static const FName LineTraceSingleName(TEXT("CXZLineTraceFromScreenPosPercentage"));
	FCollisionQueryParams Params = ConfigureCollisionParams(LineTraceSingleName,bTraceComplex,ActorsToIgnore,bIgnoreSelf,Player);


	for(int32 PlayerIdx = 0; PlayerIdx < PlayerList.Num(); PlayerIdx++)
	{
		if(SplitType < ViewportClient->SplitscreenInfo.Num() && PlayerIdx < ViewportClient->SplitscreenInfo[SplitType].PlayerData.Num())
		{
			if(PlayerList[PlayerIdx] == pLPlayer)
			{
				FSizePercent.X = ViewportClient->SplitscreenInfo[SplitType].PlayerData[PlayerIdx].SizeX * (float)Size.X;;
				FSizePercent.Y = ViewportClient->SplitscreenInfo[SplitType].PlayerData[PlayerIdx].SizeY * (float)Size.Y;;
				Origin.X = ViewportClient->SplitscreenInfo[SplitType].PlayerData[PlayerIdx].OriginX * (float)Size.X;
				Origin.Y = ViewportClient->SplitscreenInfo[SplitType].PlayerData[PlayerIdx].OriginY * (float)Size.Y;

				//const FCollisionQueryParams& CollisionQueryParams
				Position.X = FMath::RoundToInt(FSizePercent.X * FMath::Clamp(x,0.0f,1.0f) + Origin.X);
				Position.Y = FMath::RoundToInt(FSizePercent.Y * FMath::Clamp(y,0.0f,1.0f) + Origin.Y);
				return Player->GetHitResultAtScreenPosition(Position,CollisionChannel,Params,HitResult);
			}
		}
	}

	Position.X = FMath::RoundToInt(Size.X * FMath::Clamp(x,0.0f,1.0f));
	Position.Y = FMath::RoundToInt(Size.Y * FMath::Clamp(y,0.0f,1.0f));
	return Player->GetHitResultAtScreenPosition(Position,CollisionChannel,Params,HitResult);
}

bool UCXZFuncLib::CXZScreenPosPercentageVector(const APlayerController* Player,const float x,const float y,FVector& WorldOrigin,FVector& WorldDirection)
{
	FVector2D Position;
	if(!IsValid(Player))
		return false;
	if(GEngine == nullptr)
	{
		return false;
	}
	UGameViewportClient* ViewportClient = GEngine->GameViewport;
	if(ViewportClient == nullptr)
	{
		return false;
	}
	FViewport* Viewport = ViewportClient->Viewport;
	if(Viewport == nullptr)
	{
		return false;
	}
	FIntPoint Size = Viewport->GetSizeXY();
	Position.X = FMath::RoundToInt(Size.X * FMath::Clamp(x,0.0f,1.0f));
	Position.Y = FMath::RoundToInt(Size.Y * FMath::Clamp(y,0.0f,1.0f));
	if(UGameplayStatics::DeprojectScreenToWorld(Player,Position,WorldOrigin,WorldDirection) == true)
	{
		return true;
	}
	return false;
}

void UCXZFuncLib::CXZGetAbsolutePosition(const FGeometry Geometry,FVector2D& Position)
{
	Position = Geometry.GetAbsolutePosition();
}

UMediaTexture* UCXZFuncLib::CXZCreateMediaTexture(/*UMediaPlayer& InMediaPlayer*/)
{
	//	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	UMediaTexture* MediaTexture = NewObject<UMediaTexture>(GetTransientPackage(),NAME_None,RF_Transient | RF_Public);

	if(MediaTexture != nullptr)
	{
		MediaTexture->AutoClear = true;
		//MediaTexture->SetMediaPlayer(nullptr);
		MediaTexture->UpdateResource();
		MediaTexture->AddToRoot();
	}

	return MediaTexture;
	//}

	//return nullptr;
}

FCollisionQueryParams UCXZFuncLib::ConfigureCollisionParams(FName TraceTag,bool bTraceComplex,const TArray<AActor*>& ActorsToIgnore,bool bIgnoreSelf,const UObject* WorldContextObject)
{
	FCollisionQueryParams Params(TraceTag,SCENE_QUERY_STAT_ONLY(KismetTraceUtils),bTraceComplex);
	Params.bReturnPhysicalMaterial = true;
	Params.bReturnFaceIndex = false;//!UPhysicsSettings::Get()->bSuppressFaceRemapTable; // Ask for face index, as long as we didn't disable globally
	Params.AddIgnoredActors(ActorsToIgnore);
	if(bIgnoreSelf)
	{
		const AActor* IgnoreActor = Cast<AActor>(WorldContextObject);
		if(IgnoreActor)
		{
			Params.AddIgnoredActor(IgnoreActor);
		}
		else
		{
			// find owner
			const UObject* CurrentObject = WorldContextObject;
			while(CurrentObject)
			{
				CurrentObject = CurrentObject->GetOuter();
				IgnoreActor = Cast<AActor>(CurrentObject);
				if(IgnoreActor)
				{
					Params.AddIgnoredActor(IgnoreActor);
					break;
				}
			}
		}
	}

	return Params;
}