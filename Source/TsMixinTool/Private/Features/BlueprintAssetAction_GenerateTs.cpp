// Copyright (c) 2025 Rokukkkk. All rights reserved.

#include "Features/BlueprintAssetAction_GenerateTs.h"

#include "ContentBrowserModule.h"
#include "TsMixinSettings.h"
#include "TsMixinUtils.h"


void FBlueprintAssetAction_GenerateTs::Register()
{
	FContentBrowserModule& ContentBrowserModule = FModuleManager::LoadModuleChecked<FContentBrowserModule>("ContentBrowser");

	ExtenderIndex = ContentBrowserModule.GetAllAssetViewContextMenuExtenders().Add(
		FContentBrowserMenuExtender_SelectedAssets::CreateRaw(this, &FBlueprintAssetAction_GenerateTs::OnExtendAssetContextMenu)
	);
}

void FBlueprintAssetAction_GenerateTs::Unregister() const
{
	FContentBrowserModule& ContentBrowserModule = FModuleManager::LoadModuleChecked<FContentBrowserModule>("ContentBrowser");

	ContentBrowserModule.GetAllAssetViewContextMenuExtenders().RemoveAt(ExtenderIndex);
}

TSharedRef<FExtender> FBlueprintAssetAction_GenerateTs::OnExtendAssetContextMenu(const TArray<FAssetData>& SelectedAssets)
{
	TSharedRef<FExtender> Extender(new FExtender());

	bool bHasBlueprint = false;
	for (const FAssetData& Asset : SelectedAssets)
	{
		if (Asset.AssetClassPath == UBlueprint::StaticClass()->GetClassPathName())
		{
			bHasBlueprint = true;
			break;
		}
	}

	if (bHasBlueprint)
	{
		CachedAssets = SelectedAssets;

		Extender->AddMenuExtension(
			"GetAssetActions",
			EExtensionHook::After,
			nullptr,
			FMenuExtensionDelegate::CreateRaw(this, &FBlueprintAssetAction_GenerateTs::AddGenerateTsMenu)
		);
	}

	return Extender;
}

void FBlueprintAssetAction_GenerateTs::AddGenerateTsMenu(FMenuBuilder& MenuBuilder)
{
	MenuBuilder.AddMenuEntry(
		FText::FromString(TEXT("Generate TS Script")),
		FText::FromString(TEXT("Generate PuerTS Mixin script from selected Blueprints.")),
		FSlateIcon(),
		FUIAction(FExecuteAction::CreateRaw(this, &FBlueprintAssetAction_GenerateTs::GenerateTsMixin))
	);
}

void FBlueprintAssetAction_GenerateTs::GenerateTsMixin()
{
	// Load settings
	const UTsMixinSettings* Settings = GetDefault<UTsMixinSettings>();

	for (const FAssetData& Asset : CachedAssets)
	{
		if (const UBlueprint* Blueprint = Cast<UBlueprint>(Asset.GetAsset()))
		{
			if (const UClass* GeneratedClass = Blueprint->GeneratedClass)
			{
				// Get all functions/delegates that start with "TS_"
				TArray<FString> TsPlaceholderNames;
				if (Settings->MixinMode == EMixinMode::DefaultMode)
				{
					GetAllFunc(GeneratedClass, TsPlaceholderNames);
				}
				else
				{
					GetAllDelegate(GeneratedClass, TsPlaceholderNames);
				}

				// Load TS template
				FString TemplateContent;
				FString TemplatePath;
				if (Settings->MixinMode == EMixinMode::DefaultMode)
				{
					TemplatePath = FPaths::ProjectPluginsDir() / TEXT("TsMixinTool/Content/Template_DefaultMode.ts");
				}
				else
				{
					TemplatePath = FPaths::ProjectPluginsDir() / TEXT("TsMixinTool/Content/Template_ManagerMode.ts");
				}

				if (!FFileHelper::LoadFileToString(TemplateContent, *TemplatePath))
				{
					UE_LOG(LogTemp, Error, TEXT("Failed to load template file: %s."), *TemplatePath);
					return;
				}

				// Get all FStrings for generating TS file
				FString BlueprintName = Blueprint->GetName();
				FString BlueprintPathName = Blueprint->GetPathName();
				FString BlueprintPathNameDot = BlueprintPathName.Replace(TEXT("/"), TEXT("."));
				FString BlueprintPathNameForTs = BlueprintPathName.Replace(TEXT("/Game/"), TEXT(""));
				BlueprintPathNameForTs.RemoveFromEnd(FString(".") + *BlueprintName);

				// Show message dialog if there are no TS_Functions in the Blueprint
				if (TsPlaceholderNames.IsEmpty())
				{
					const auto UserChoice = FMessageDialog::Open(
						EAppMsgType::YesNo, FText::FromString(TEXT("Do you want to creat an empty script?")), FText::FromString(TEXT("No TS placeholder(s)"))
					);

					if (UserChoice == EAppReturnType::No)
					{
						return;
					}
				}

				FString PlaceholderOverrides;
				for (const FString& PlaceholderName : TsPlaceholderNames)
				{
					if (Settings->MixinMode == EMixinMode::DefaultMode)
					{
						PlaceholderOverrides += FString::Printf(TEXT("  %s {\n    // TODO: implement here\n  }\n"), *PlaceholderName);
					}
					else
					{
						PlaceholderOverrides += FString::Printf(TEXT("this.bpObj.%s.Add(this.%s.bind(this));\n"), *PlaceholderName, *PlaceholderName);;
					}
				}

				TemplateContent = TemplateContent.Replace(TEXT("/*BlueprintPathName*/"), *BlueprintPathName);
				TemplateContent = TemplateContent.Replace(TEXT("/*BlueprintPathName_Dot*/"), *BlueprintPathNameDot);
				TemplateContent = TemplateContent.Replace(TEXT("/*BlueprintName*/"), *BlueprintName);
				TemplateContent = TemplateContent.Replace(TEXT("/*PlaceholderOverrides*/"), *PlaceholderOverrides);

				FString GenPath = FPaths::ProjectDir() + Settings->TsScriptOutputPath;
				if (Settings->MixinMode == EMixinMode::DefaultMode)
				{
					GenPath += "/TsScripts_Mixin/" + BlueprintPathNameForTs + ".ts";
				}
				else
				{
					GenPath += "/TsScripts_Manager/" + BlueprintPathNameForTs + ".ts";
				}

				// WriteLog
				if (FFileHelper::SaveStringToFile(TemplateContent, *GenPath))
				{
					TsMixinToolUtils::ShowSimpleNotification(TEXT("TS Script Generated"));
				}
				else
				{
					TsMixinToolUtils::ShowSimpleNotification(TEXT("Failed to save TS Script"), false);
				}
			}
		}
	}
}

void FBlueprintAssetAction_GenerateTs::GetAllFunc(const UClass* GeneratedClass, TArray<FString>& TsPlaceholderNames)
{
	for (TFieldIterator<UFunction> FuncIt(GeneratedClass); FuncIt; ++FuncIt)
	{
		const UFunction* Func = *FuncIt;
		FString FuncNameStr = Func->GetName();

		if (FuncNameStr.EndsWith("__DelegateSignature"))
		{
			continue;
		}

		if (FuncNameStr.StartsWith("TS_"))
		{
			TsPlaceholderNames.Add(FString::Printf(TEXT("%s()"), *FuncNameStr));
		}
	}
}

void FBlueprintAssetAction_GenerateTs::GetAllDelegate(const UClass* GeneratedClass, TArray<FString>& TsPlaceholderNames)
{
	for (TFieldIterator<FMulticastDelegateProperty> PropIt(GeneratedClass); PropIt; ++PropIt)
	{
		const FMulticastDelegateProperty* DelegateProp = *PropIt;
		FString PropName = DelegateProp->GetName();

		if (PropName.StartsWith("TS_"))
		{
			TsPlaceholderNames.Add(PropName);
		}
	}
}
