// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "MySecondPlugin.h"
#include "MySecondPluginStyle.h"
#include "MySecondPluginCommands.h"
#include "Misc/MessageDialog.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"
#include "IAssetViewport.h"
#include "LevelEditor.h"

static const FName MySecondPluginTabName("MySecondPlugin");

DEFINE_LOG_CATEGORY(LogRPP);


#define LOCTEXT_NAMESPACE "FMySecondPluginModule"

void FMySecondPluginModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FMySecondPluginStyle::Initialize();
	FMySecondPluginStyle::ReloadTextures();

	FMySecondPluginCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FMySecondPluginCommands::Get().PluginAction,
		FExecuteAction::CreateRaw(this, &FMySecondPluginModule::PluginButtonClicked),
		FCanExecuteAction());
		
	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	
	{
		TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender());
		MenuExtender->AddMenuExtension("WindowLayout", EExtensionHook::After, PluginCommands, FMenuExtensionDelegate::CreateRaw(this, &FMySecondPluginModule::AddMenuExtension));

		LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);
	}
	
	{
		TSharedPtr<FExtender> ToolbarExtender = MakeShareable(new FExtender);
		ToolbarExtender->AddToolBarExtension("Settings", EExtensionHook::After, PluginCommands, FToolBarExtensionDelegate::CreateRaw(this, &FMySecondPluginModule::AddToolbarExtension));
		
		LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(ToolbarExtender);
	}
}

void FMySecondPluginModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	FMySecondPluginStyle::Shutdown();

	FMySecondPluginCommands::Unregister();
}

void FMySecondPluginModule::PluginButtonClicked()
{
	//if (!bSMyWidgetInitilized)
	//{
	//	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	//	//TSharedPtr<ILevelViewport> MyILevelViewport = LevelEditorModule.GetFirstActiveViewport();
	//	MyCompoundWidget = SNew(SMyCompoundWidget);

	//	LevelEditorModule.GetFirstActiveViewport()->AddOverlayWidget(MyCompoundWidget.ToSharedRef());
	//	bSMyWidgetInitilized = true;
	//}


	//if (bPluginIsActivated == false)
	//{
	//	MyCompoundWidget->SetVisibility(EVisibility::SelfHitTestInvisible);
	//	bPluginIsActivated = true;
	//}
	//else
	//{
	//	MyCompoundWidget->SetVisibility(EVisibility::Hidden);
	//	bPluginIsActivated = false;
	//}
	//UE_LOG(LogTemp, Warning, TEXT("IsActivated: %s"), bPluginIsActivated ? "1" : "0");

	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");


	int32 Width = GEditor->GetActiveViewport()->GetSizeXY().X;

	int32 Height = GEditor->GetActiveViewport()->GetSizeXY().Y;

//	UE_LOG(LogTemp, Warning, TEXT("Width: %i, Height: %i"), Width, Height);

	if (RPPMain == nullptr)
	{
		RPPMain = SNew(SRPPMain)
			.RPPWidth(Width * 0.8)
			.RPPHeight(Height * 0.4);

		LevelEditorModule.GetFirstActiveViewport()->AddOverlayWidget(RPPMain.ToSharedRef());
		bSMyWidgetInitilized = true;
	}
	else
	{
		LevelEditorModule.GetFirstActiveViewport()->RemoveOverlayWidget(RPPMain.ToSharedRef());
		RPPMain.Reset();
	}




}

void FMySecondPluginModule::AddMenuExtension(FMenuBuilder& Builder)
{
	Builder.AddMenuEntry(FMySecondPluginCommands::Get().PluginAction);
}

void FMySecondPluginModule::AddToolbarExtension(FToolBarBuilder& Builder)
{
	Builder.AddToolBarButton(FMySecondPluginCommands::Get().PluginAction);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FMySecondPluginModule, MySecondPlugin)