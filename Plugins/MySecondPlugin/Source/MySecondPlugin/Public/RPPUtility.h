// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//engine include
#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Sound/SoundWave.h"

//user include


#include "RPPUtility.generated.h"

/**
 * 
 */

enum EDrawType { Header, Data, Footer };

UCLASS()
class MYSECONDPLUGIN_API URPPUtility : public UObject
{
	GENERATED_BODY()

private:

	//

	//URPPUtility(URPPUtility const&) = delete;

	//void operator=(URPPUtility const&) = delete;

	static const int32 NUMBER_OF_LINES_IN_WINDOW = 20000;

public:
	//waveform-related draw arrays
	//wav data were loaded from file to DataRawArray
	//program then process DataRawArray to DataDrawArray (such as average peak value), served as a base to DrawArray
	static TArray<float> DataRawArray;    //Raw data from wave file   

	static TArray<float> DataDrawArray;   //RawDrawArray processed from RawDataArray, contain (RawDataArray.size()/bucketsize) elements

	static TArray<FVector2D> DrawArray;	//DrawArray





private:
	static TArray<float> WaveToRawDataArray(USoundWave* SoundWave);


public:
	//URPPUtility();

	static void SetDataRawArray(USoundWave* SoundWave);

	FORCEINLINE const TArray<FVector2D>& GetDrawArray() { return DrawArray; }

	static void RawDataArrayToRawDrawArray(int BucketSize);

	static void RawDrawArrayToDrawArray(const int Start, const int End);

};
