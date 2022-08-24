// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "Networking.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CXZUDPBroadcaster.generated.h"

UCLASS(Blueprintable, BlueprintType)
class CXZTOOLS_API ACXZUDPBroadcaster : public AActor
{
	GENERATED_BODY()

	void GetUtf8Length(char const *str, int *cnt);
public:
	// Sets default values for this actor's properties
	ACXZUDPBroadcaster();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	bool IsUDP;
	bool IsInitSender;
	bool IsInitReceiver;

	TSharedPtr<FInternetAddr> RemoteAddr;
	FSocket* SenderSocket;

	FSocket* ReceiverSocket;



public:
	UFUNCTION(BlueprintCallable, Category = "UDP")
	bool FakeInputBroadcast(bool bShot);

	UFUNCTION(BlueprintCallable, Category = "UDP")
	bool UDPBroadcast(FString ToSend);

	UFUNCTION(BlueprintCallable, Category = "UDP")
	int StartUDPSender(const FString& YourChosenSocketName, const FString& TheIP, const int32 ThePort);

	UFUNCTION(BlueprintCallable, Category = "UDP")
	int StartUDPReceiver(const FString& YourChosenSocketName, const FString& TheIP, const int32 ThePort);

	UFUNCTION(BlueprintPure, Category = "UDP")
	int UPDGetBroadcastData(FString& str);

	UFUNCTION(BlueprintCallable,Category = "UDP")
	bool UDPBroadcastByteArray(const TArray<uint8>& ToSend);
};
