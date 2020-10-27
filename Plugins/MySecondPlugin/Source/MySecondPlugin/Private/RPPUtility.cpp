// Fill out your copyright notice in the Description page of Project Settings.

#include "RPPUtility.h"

#include "EditorViewportClient.h"
#include "Kismet/GameplayStatics.h"

#include "MySecondPluginTextRW.h"
#include "MySecondPluginTimestamp.h"
#include "MySecondPluginManager.h"



TArray<float> URPPUtility::DataRawArray;    //Raw data from wave file   
TArray<float> URPPUtility::DataDrawArray;   //RawDrawArray processed from RawDataArray, contain (RawDataArray.size()/bucketsize) elements
TArray<FVector2D> URPPUtility::DrawArray;	//DrawArray

TArray<float> URPPUtility::BeatRawArray{ 0.f, 1.f, 2.f, 3.f, 4.f,5.f, 6.f, 7.f, 8.f, 9.f, 10.f };    //Raw beat info; elements in second. for example, if BPM = 60, it shoud be [0,1,2,3,4,5...]
TArray<FVector2D> URPPUtility::BeatDrawArray;	//BeatArray

UMySecondPluginTextRW* URPPUtility::MySecondPluginTextRW = nullptr;

FEditorViewportClient* URPPUtility::EditorViewportClient = nullptr;

AMySecondPluginManager* URPPUtility::MySecondPluginManager = nullptr;

int32 URPPUtility::WidgetHeight = 0;

int32 URPPUtility::WidgetWidth = 0;


URPPUtility::URPPUtility()
{
	URPPUtility::MySecondPluginTextRW = NewObject<UMySecondPluginTextRW>();

	if (GetWorld())
	{

	}

}

void URPPUtility::SetEditorViewportClient(FEditorViewportClient* InEditorViewportClient)
{
	if (InEditorViewportClient)
	{
		EditorViewportClient = InEditorViewportClient;
	}
}
/**
 Extract data from USoundWave and put them into RawDataArray
 @param Soundwave, the Soundwave pointer
 @return TArray containing raw data from the USoundWave object.
*/
TArray<float> URPPUtility::WaveToRawDataArray(USoundWave* SoundWave)
{
	TArray<float> Output{};
	const int32 NumChannels = SoundWave->NumChannels;

	if ((NumChannels == 0) || (SoundWave->RawData.GetBulkDataSize() == 0))
	{
		return Output;
	}

	uint8* RawWaveData = (uint8*)SoundWave->RawData.Lock(LOCK_READ_ONLY);
	int32 RawDataSize = SoundWave->RawData.GetBulkDataSize();
	FWaveModInfo WaveInfo;

	if (WaveInfo.ReadWaveHeader(RawWaveData, RawDataSize, 0))
	{
		uint32 SampleCount = WaveInfo.SampleDataSize / (2 * NumChannels);

		const int16* SamplePtr = reinterpret_cast<const int16*>(WaveInfo.SampleDataStart);

		for (uint32 SampleIndex = 0; SampleIndex < SampleCount; ++SampleIndex)
		{
			int64 SampleSum = 0;
			for (int32 ChannelIndex = 0; ChannelIndex < NumChannels; ++ChannelIndex)
			{
				SampleSum += (*SamplePtr);
				SamplePtr++;
			}
			SampleSum = SampleSum / (float)NumChannels;
			Output.Add(SampleSum);
		}
	}

	SoundWave->RawData.Unlock();

	return Output;
}

void URPPUtility::SetDataRawArray(USoundWave* SoundWave)
{
	if (SoundWave)
	{
		DataRawArray = WaveToRawDataArray(SoundWave);
	}
}

/*
 Extract raw data from RawDataArray and put them into RawDrawArray
 @param InputArray, the RawDataArray from USoundWave
 @param BucketSize, we only push the absolute max value in the bucket into the DrawArray.
 Therefore, by default, the size of RawDrawArray is (InputArray.size()/200)
*/
void URPPUtility::RawDataArrayToRawDrawArray(int BucketSize)
{
	DataDrawArray.Empty();

	//float YOffset = Padding + BorderHeight / 2.f;

	if (WidgetHeight == 0 || WidgetWidth == 0)
	{
		return;
	}

	//if (DrawArray.Num() != 0)
	//{
	//	return;
	//}

	float YOffset = WidgetHeight/2;

	int InputArrayIndex = 0;
	int NumberOfBuckets = (DataRawArray.Num() - (DataRawArray.Num() % BucketSize)) / BucketSize;
	float AbsMax = DataRawArray[0];
	for (int i = 0; i < DataRawArray.Num(); i++)
	{
		if (FMath::Abs(DataRawArray[i]) > AbsMax)
		{
			AbsMax = DataRawArray[i];
		}
	}

	//float YScale = BorderHeight / (2 * AbsMax);

	float YScale = WidgetHeight / (2 * AbsMax);

	for (int i = 0; i < NumberOfBuckets; i++)
	{
		float Temp = 0;

		for (int j = 0; j < BucketSize; j++)      //absmax with bucket
		{
			if (FMath::Abs(DataRawArray[InputArrayIndex]) > Temp)
			{
				Temp = DataRawArray[InputArrayIndex];
			}
			InputArrayIndex++;
		}
		Temp = YOffset - (Temp * YScale);
		DataDrawArray.Add(Temp);
	}


}


/**
 Extract raw data from RawDataArray and put them into TArray<float> for drawing
 @param InputArray, the RawDataArray from USoundWave
 @param SampleCount, how many samples to draw. For example, If InputArray contains 20K samples,
 putting 10k at this para will only draw half of the waveform of the file
 @param BucketSize, we only push the absolute max value in the bucket into the DrawArray.
 Therefore, by default, the size of DrawArray is (InputArray.size()/200)
*/
void URPPUtility::RawDrawArrayToDrawArray(int Start, const int End)
{
	//get # of steps
	//take the peak value of each bucket
	//add to array
	/*
	This function serves as a moving window of deciding what's shown on the screen, picking the "window" section out of RawDrawArray
	if (header-start)<0 -> window is larger than default
	if (header-start)>0  &&  if (end+tail)<InArray.num() -> still going

	if (end+tail)>InArray.num() -> fill default

	//Todo: is it possible to change the pointer to the array instead of rewritting the array every frame?

	*/



	DrawArray.Empty();
	int ArrayIndex = Start;										 //starting point of the InArray
	int Steps = 1;												//how many steps has been taken. This process always take NUMBER_OF_LINES_IN_WINDOW steps
	int NumberOfSteps = NUMBER_OF_LINES_IN_WINDOW;
	//float YOffset = Padding + BorderHeight / 2.f;				//default Y position, horizontal line

	float YOffset = 0.f;				//default Y position, horizontal line

	float XCord = 0.f;										//X  starting cord   //Todo, just change Y, leave X

	float XIncrement = (float)WidgetWidth / NumberOfSteps;

	int Header = NUMBER_OF_LINES_IN_WINDOW / 2;
	int Tail = NUMBER_OF_LINES_IN_WINDOW / 2;

	EDrawType NextDrawType = EDrawType::Header;

	int HeadNeeded = Header - Start;
	if (HeadNeeded >= 0)
	{
		ArrayIndex = 0;
	}
	else
	{
		NextDrawType = EDrawType::Data;
		ArrayIndex = ArrayIndex - NumberOfSteps / 2;
		if (ArrayIndex < 0) ArrayIndex = 0;
	}



	while (Steps < NumberOfSteps)
	{
		float YTemp = YOffset;
		switch (NextDrawType)
		{
		case EDrawType::Data:
		{
			/*
			if array index in range, fill
			else mark next as footer and break;
			*/

			if (ArrayIndex > DataDrawArray.Num() - 1)
			{
				NextDrawType = EDrawType::Footer;
				break;
			}

			YTemp = DataDrawArray[ArrayIndex];
			ArrayIndex++;
			break;
		}
		case EDrawType::Header:
		{
			/*
			if (headneeded<0), break, nexttype = data
			else fill head, headneede--;
			*/
			if (HeadNeeded <= 0)
			{
				NextDrawType = EDrawType::Data;
				break;
			}
			else
			{
				HeadNeeded--;
			}
			break;
		}
		case EDrawType::Footer:
		{
			/*
			fill tail, the while take cares of ending condition
			*/
			break;
		}
		}
		DrawArray.Add(FVector2D(XCord, YTemp));
		XCord += XIncrement;
		Steps++;
	}
}


/*
calculatess beat array. e.g. if bpm = 60. BeatRawArray = {0,1,2,3 ...}
*/
void URPPUtility::CalculateRawBeatArray(const float& InBPM, const float& InAudioDuation, const float& InBeatStartingTime)
{
	if (InBPM)
	{
		URPPUtility::BeatRawArray.Empty();

		URPPUtility::BeatRawArray.Add(0.f);

		float NextBeatTime = 0.f + InBeatStartingTime;

		float BeatInveral = 60.f / InBPM;

		while (NextBeatTime <= InAudioDuation)
		{
			URPPUtility::BeatRawArray.Add(NextBeatTime);
			NextBeatTime += BeatInveral;
		}
	}

	return;
}

void URPPUtility::LoadLevel()
{
	FString outString;
	MySecondPluginTextRW->LoadLevelInfo(TEXT("test.txt"), outString);
}

void URPPUtility::SaveLevel()
{
	MySecondPluginTextRW->SaveLevelInfo("test.txt");
}

void URPPUtility::AddTimestamp(float InAudioCursor)
{
	if (EditorViewportClient)
	{
		AMySecondPluginTimestamp* newTimeStamp = EditorViewportClient->GetWorld()->SpawnActor<AMySecondPluginTimestamp>(FVector(EditorViewportClient->GetViewLocation().X, 0, EditorViewportClient->GetViewLocation().Z), FRotator::ZeroRotator);

		FPlatformerEvent NewEvent;
		NewEvent.EventUniqueID = newTimeStamp->GetUniqueID();
		NewEvent.EventTime = InAudioCursor;

		MySecondPluginTextRW->AddEvent(NewEvent);
	}

}

void URPPUtility::AddTimestamp(class AMySecondPluginTimestamp* InPluginTimestamp, UWorld* World)
{
	if (InPluginTimestamp)
	{
		if (InPluginTimestamp->GetActorLocation().IsZero())
		{
			return;
		}


		FPlatformerEvent NewEvent;
		NewEvent.EventUniqueID = InPluginTimestamp->GetUniqueID();
		NewEvent.EventTime = WorldSpaceToAudioCursor(InPluginTimestamp->GetActorLocation(), World);

		UE_LOG(LogTemp, Warning, TEXT("EventTime: %s"), *FString::SanitizeFloat(NewEvent.EventTime, 2));

		MySecondPluginTextRW->AddEvent(NewEvent);
		return;

	}
}

void URPPUtility::DeleteTimestamp(int32 InEventID)
{
	MySecondPluginTextRW->DeleteEvent(InEventID);
}

float URPPUtility::WorldSpaceToAudioCursor(FVector InLocation, UWorld* World)
{

	TArray<AActor*> foundManager;
	UGameplayStatics::GetAllActorsOfClass(World, AMySecondPluginManager::StaticClass(), foundManager);

	if (foundManager.Num() == 1)
	{
		MySecondPluginManager = Cast<AMySecondPluginManager>(foundManager[0]);
	}

	if (MySecondPluginManager)
	{
		float Delta = InLocation.X - MySecondPluginManager->GetActorLocation().X;

		float AudioCursor = Delta / MySecondPluginManager->RunningSpeed;

		UE_LOG(LogTemp, Warning, TEXT("Delta: %s, AudioCursor: %s"), *FString::SanitizeFloat(Delta, 2), *FString::SanitizeFloat(AudioCursor, 2));

		
		return AudioCursor;
	}
	return 0.0f;

}

void URPPUtility::SetPluginManager(AMySecondPluginManager* InMySecondPluginManager)
{
	MySecondPluginManager = InMySecondPluginManager;
}

void URPPUtility::RefreshRunSpeed(UWorld* World, AMySecondPluginManager* InPluginManager)
{
	//UE_LOG(LogTemp, Warning, TEXT("Running Speed: %s. "), *FString::SanitizeFloat(PluginManagerObject->RunningSpeed));

	//UE_LOG(LogTemp, Warning, TEXT("Running Speed: %d. "), MySecondPluginTextRW->EventMemo.Num());

	if (World)
	{
		TSubclassOf<AMySecondPluginTimestamp> classToFind;
		classToFind = AMySecondPluginTimestamp::StaticClass();
		TArray<AActor*> FoundMarkers;
		UGameplayStatics::GetAllActorsOfClass(World, classToFind, FoundMarkers);


		for (auto& TmpEvent : MySecondPluginTextRW->EventMemo)
		{

			FActorSpawnParameters SpawnParms;
			FVector SpawnLocation = FVector(TmpEvent.Value.EventTime * InPluginManager->RunningSpeed, 0, 0);

			bool bIsActorFound = false;
			for (AActor* SingleActor : FoundMarkers)
			{
				if (SingleActor->GetUniqueID() == TmpEvent.Value.EventUniqueID)
				{
					SpawnLocation.Z = SingleActor->GetActorLocation().Z;

					SingleActor->SetActorLocation(SpawnLocation);
					FoundMarkers.Remove(SingleActor);
					bIsActorFound = true;
					break;
				}
			}
			if (!bIsActorFound)
			{
				AMySecondPluginTimestamp* newTimeStamp = World->
					SpawnActor<AMySecondPluginTimestamp>(SpawnLocation, FRotator::ZeroRotator, SpawnParms);
			}
		}
	}



}

void URPPUtility::ClearEverything()
{
	URPPUtility::DataRawArray.Empty();    
	URPPUtility::DataDrawArray.Empty();   
	URPPUtility::DrawArray.Empty();	

	URPPUtility::BeatRawArray.Empty();    
	URPPUtility::BeatDrawArray.Empty();	

	URPPUtility::MySecondPluginTextRW = nullptr;

	URPPUtility::EditorViewportClient = nullptr;

	URPPUtility::MySecondPluginManager = nullptr;


}
