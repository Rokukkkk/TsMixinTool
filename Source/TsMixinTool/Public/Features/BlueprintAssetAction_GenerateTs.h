// Copyright (c) 2025 Rokukkkk. All rights reserved.

#pragma once

class FContentBrowserModule;


class FBlueprintAssetAction_GenerateTs
{
public:
	void Register();
	void Unregister() const;

private:
	int32 ExtenderIndex = INDEX_NONE;

	TSharedRef<FExtender> OnExtendAssetContextMenu(const TArray<FAssetData>& SelectedAssets);
	void AddGenerateTsMenu(FMenuBuilder& MenuBuilder);
	void GenerateTsMixin();
	static void GetAllFunc(const UClass* GeneratedClass, TArray<FString>& TsPlaceholderNames);
	static void GetAllDelegate(const UClass* GeneratedClass, TArray<FString>& TsPlaceholderNames);

	TArray<FAssetData> CachedAssets;
};
