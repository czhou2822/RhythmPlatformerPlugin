// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Dom/JsonObject.h"
#include "MySecondPluginTextRW.generated.h"

/**
 * 
 */

USTRUCT()
struct FPlatformerEvent
{
	GENERATED_BODY()

	UPROPERTY()
	int32 EventFrameStamp = 0;  //indicate where is this event in frame

	UPROPERTY()
    float EventTime;  //indicate where is this event in frame

	UPROPERTY()
	int32 EventUniqueID;


};


USTRUCT()
struct FLevelInfo
{
	GENERATED_BODY()

	UPROPERTY()
	FString LevelName;

	UPROPERTY()
	FString SoundtrackName;

	UPROPERTY()
	int32 LevelFrameCount;

	UPROPERTY()
	float RunningSpeed = 600.f;

	UPROPERTY()
	TArray<FPlatformerEvent> Events;
};


UCLASS()
class MYSECONDPLUGIN_API UMySecondPluginTextRW : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

private:


	FLevelInfo CurrentLevelInfo;

	FString ReadLevelInfo;

	TSharedPtr<FJsonObject> LevelInfoJsonObject;


	
public:
	//TArray<FPlatformerEvent> EventMemo; //array to hold all intermediate FPlatformerEvent (timestamp)

	//pair event's uniqueID to platformerEvent
	TMap<int32, FPlatformerEvent> EventMemo; //array to hold all intermediate FPlatformerEvent (timestamp)


private:
	void MakeNewLevelInfo(FString LevelName, FString SoundtrackName, int32 LevelFrameCount);

	FString StringtifyLevelInfoJsonObject();  //stringtify event memo for store

	void GetJsonObject(int32& index); //get json object from the eventmemo

	void ParseLevelInfoJsonObject(TSharedPtr<FJsonValue> JsonValue);

public:

	//UFUNCTION(BlueprintCallable, Category = "Custom", meta = (Keywords = "LoadTxt"))
	bool LoadLevelInfo(FString FileNameA, FString& SaveTextA);

	//UFUNCTION(BlueprintCallable, Category = "Custom", meta = (Keywords = "SaveTxt"))
	bool SaveLevelInfo(FString FileNameB);

	bool AddEvent(FPlatformerEvent NewEvent);

	bool DeleteEvent(int32 InEventName);

	UMySecondPluginTextRW();




};
