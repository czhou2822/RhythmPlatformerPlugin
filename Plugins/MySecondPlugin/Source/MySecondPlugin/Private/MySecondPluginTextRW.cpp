// Fill out your copyright notice in the Description page of Project Settings.
#include "MySecondPluginTextRW.h"
#include "Misc/FileHelper.h"
#include "Runtime/JsonUtilities/Public/JsonObjectConverter.h"
#include "Dom/JsonObject.h"
#include "Misc/Paths.h"



UMySecondPluginTextRW::UMySecondPluginTextRW()
{
    UE_LOG(LogTemp, Log, TEXT("New TextRW created"));
    EventMemo.Empty();
    LevelInfoJsonObject = MakeShareable(new FJsonObject());
}


void UMySecondPluginTextRW::MakeNewLevelInfo(FString LevelName, FString SoundtrackName, int32 LevelFrameCount)
{

}



void UMySecondPluginTextRW::GetJsonObject(int32& index)
{
    if (index >= EventMemo.Num())
    {
        return;
    }
    TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());

}

void UMySecondPluginTextRW::ParseLevelInfoJsonObject(TSharedPtr<FJsonValue> JsonValue)
{
    TSharedPtr<FJsonObject> SingleEvent = MakeShareable(new FJsonObject());
    SingleEvent = JsonValue->AsObject();

    FPlatformerEvent EventTemp;


    FJsonObjectConverter::JsonObjectToUStruct<FPlatformerEvent>(SingleEvent.ToSharedRef(), &EventTemp, 0, 0);


    UE_LOG(LogTemp, Warning, TEXT("EventFrameStamp: %s.\n"), *EventTemp.EventName);

    EventMemo.Add(EventTemp);


}



bool UMySecondPluginTextRW::LoadLevelInfo(FString FileNameA, FString& SaveTextA)
{

    ReadLevelInfo.Empty();
    EventMemo.Empty();

    bool ReturnFlag = FFileHelper::LoadFileToString(ReadLevelInfo, *(FPaths::GameDir() + FileNameA));  //read from save

    //UE_LOG(LogTemp, Warning, TEXT("read from save jsonString -> %s"), *ReadLevelInfo);


    TSharedRef< TJsonReader<> > Reader = TJsonReaderFactory<>::Create(ReadLevelInfo);

    TArray<TSharedPtr<FJsonValue>> ReadEventsTemp;

    if (FJsonSerializer::Deserialize(Reader, LevelInfoJsonObject))
    {
        ReadEventsTemp = LevelInfoJsonObject->GetArrayField(TEXT("events"));
        UE_LOG(LogTemp, Warning, TEXT("Reading from test.txt: %d"), ReadEventsTemp.Num());
    }

    for (TSharedPtr<FJsonValue> x : ReadEventsTemp)
    {
        ParseLevelInfoJsonObject(x);
    }

    EventMemo;
    return ReturnFlag;
}



bool UMySecondPluginTextRW::SaveLevelInfo(FString FileNameB)
{
    int32 index = 0;
    FString StringtifiedLevelInfo = StringtifyLevelInfoJsonObject();

    return FFileHelper::SaveStringToFile(StringtifiedLevelInfo, *(FPaths::GameDir() + FileNameB));  //write to hdd/save save file
} 

FString UMySecondPluginTextRW::StringtifyLevelInfoJsonObject()
{
    CurrentLevelInfo.LevelFrameCount = 12345;
    CurrentLevelInfo.LevelName = TEXT("Test level");
    CurrentLevelInfo.SoundtrackName = TEXT("Imaginary soundtrack");
    CurrentLevelInfo.Events = EventMemo;
    

    FString OutputString;

    //FJsonObjectConverter::UStructToJsonObjectString(CurrentLevelInfo, OutputString, 0, 0);
    LevelInfoJsonObject = FJsonObjectConverter::UStructToJsonObject(CurrentLevelInfo, 0, 0);

    TSharedRef< TJsonWriter<> > Writer = TJsonWriterFactory<>::Create(&OutputString);
    FJsonSerializer::Serialize(LevelInfoJsonObject.ToSharedRef(), Writer);

    UE_LOG(LogTemp, Warning, TEXT("resulting jsonString -> %s"), *OutputString);


    return OutputString;
}

bool UMySecondPluginTextRW::AddNewEvent(FPlatformerEvent NewEvent)
{
    //FPlatformerEvent EventTemp;

    //EventTemp.EventName = EventName;
    //EventTemp.EventFrameStamp = EventTimeStamp;


    TSharedPtr<FJsonObject> EventTempJsonObject = MakeShareable(new FJsonObject());
    EventTempJsonObject = FJsonObjectConverter::UStructToJsonObject(NewEvent, 0, 0);

    EventMemo.Add(NewEvent);

    //EventMemo.Add(EventTemp);


    /*
    
    TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
    JsonObject->SetStringField("Name", newTimeStamp->GetName());
    JsonObject->SetNumberField("Location", SnapLineCursor);

    FString OutputString;
    TSharedRef< TJsonWriter<> > Writer = TJsonWriterFactory<>::Create(&OutputString);
    FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer);

    UE_LOG(LogTemp, Warning, TEXT("resulting jsonString -> %s"), *OutputString);
    */



    return false;
}

