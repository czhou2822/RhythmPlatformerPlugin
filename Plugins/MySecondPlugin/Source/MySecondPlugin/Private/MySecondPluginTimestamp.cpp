//// Fill out your copyright notice in the Description page of Project Settings.
//#include "MySecondPluginTimestamp.h"
//
//#include "components/SphereComponent.h"
//#include "Kismet/GameplayStatics.h"
//#include "UObject/ConstructorHelpers.h"
//
//#if WITH_EDITOR
//
//#include "Editor/EditorEngine.h"
//#include "Engine/Selection.h"
//#include "Editor.h"
//#endif
//
//
//#include "MySecondPluginManager.h"
//#include "RPPUtility.h"
//
//
//// Sets default values
//AMySecondPluginTimestamp::AMySecondPluginTimestamp()
//	:PluginManagerObject(nullptr)
//{
// 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
//	PrimaryActorTick.bCanEverTick = true;
//
//	SphereMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SphereMesh"));
////	SphereMesh->AttachTo(GetRootComponent());
//
//	SphereMesh->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
//	//
//	static ConstructorHelpers::FObjectFinder<UStaticMesh>SphereMeshAsset(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
//	SphereMesh->SetStaticMesh(SphereMeshAsset.Object);
//
//	//SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
//	//RootComponent = SphereComp;
//	RootComponent = SphereMesh;
//
//
//	//SphereComp->OnComponentBeginOverlap.AddDynamic(this, &AMySecondPluginTimestamp::HandleOnActorBeginOverlap);
//
//
//	if (GetWorld()!=NULL)
//	{
//		TArray<AActor*> foundManager;
//		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMySecondPluginManager::StaticClass(), foundManager);
//
//		if (foundManager.Num() == 1)
//		{
//			PluginManagerObject = Cast<AMySecondPluginManager>(foundManager[0]);
//		}
//	}
//	
//}
//
//
//
//void AMySecondPluginTimestamp::DeleteFromMemo(AActor* InAActor)
//{
//	if (InAActor)
//	{
//		if (InAActor->GetName() == GetName())
//		{
//			URPPUtility::DeleteTimestamp(GetUniqueID());
//		}
//	}
//
//
//}
//
//void AMySecondPluginTimestamp::HandleOnDeleteActorsEnd()
//{
//	UE_LOG(LogTemp, Warning, TEXT("Actor %s delete end"), *GetName());
//}
//
//void AMySecondPluginTimestamp::HandleOnDuplicateActorsEnd()
//{
//	UE_LOG(LogTemp, Warning, TEXT("Actor %s duplicate end"), *GetName());
//}
//
//void AMySecondPluginTimestamp::OnConstruction(const FTransform& Transform)
//{
//#if WITH_EDITOR
//
//	//UE_LOG(LogTemp, Warning, TEXT("Actor ID: %i, Location: %s"), GetUniqueID(), *GetActorLocation().ToString());
//
//	GEditor->OnLevelActorDeleted().AddUObject(this, &AMySecondPluginTimestamp::DeleteFromMemo);
//
//	//FEditorDelegates::OnDeleteActorsEnd.AddUObject(this, &AMySecondPluginTimestamp::HandleOnDeleteActorsEnd);
//
//	//FEditorDelegates::OnDuplicateActorsEnd.AddUObject(this, &AMySecondPluginTimestamp::HandleOnDuplicateActorsEnd);
//
//	URPPUtility::AddTimestamp(this, GetWorld());
//	
//
//#endif
//
//}
//
////void AMySecondPluginTimestamp::BeginDestroy()
////{
////#if WITH_EDITOR
////
////	//UE_LOG(LogTemp, Warning, TEXT("Actor %s being destory"), *GetName());
////
////#endif
////}
//
//// Called when the game starts or when spawned
//void AMySecondPluginTimestamp::BeginPlay()
//{
//	Super::BeginPlay();
//	DecideSpawnActor();
//}
//
//void AMySecondPluginTimestamp::HandleOnActorBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
//{
//	UE_LOG(LogTemp, Warning, TEXT("Timestamp Overlapped"));
//}
//
//void AMySecondPluginTimestamp::DecideSpawnActor()
//{
//	TArray <int> SpawnList;
//	SpawnList.Init(-1, 100);
//	int32 SpawnListIndex = 0;
//
//	for (int32 j = 0; j < SpawnPercentage.Num(); j++)
//	{
//		for (int32 i = SpawnListIndex; i < SpawnListIndex + SpawnPercentage[j]; i++)
//		{
//			SpawnList[i] = j;
//		}
//		SpawnListIndex += SpawnPercentage[j];
//	}
//
//	int SpawnIndex = FMath::RandRange(0, 99);
//
//	UE_LOG(LogTemp, Warning, TEXT("SpawnIndex: %d"), SpawnList[SpawnIndex]);
//	UE_LOG(LogTemp, Warning, TEXT("SpawnIndex: %s"), *SpawnedList[SpawnList[SpawnIndex]]->StaticClass()->GetFName().ToString());
//	
//	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	//TArray<TSubclassOf<AActor>> SpawnedList;
//
//	GetWorld()->SpawnActor<AActor>(SpawnedList[SpawnList[SpawnIndex]], GetActorLocation(), FRotator(0, 0, 0));
//
//
//}
//
//
//
//// Called every frame
//void AMySecondPluginTimestamp::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//}
//
