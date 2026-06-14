class CfgPatches
{
	class AI2Med
	{
		units[] = {""};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {"DZ_Data","DZ_Gear_Medical"};
	};
};

class CfgVehicles
{
	class Inventory_Base;
	class TMB_AI2_Basic: Inventory_Base
	{
		scope = 2;
		displayName = "Standart AI2 Kit";
		descriptionShort = "Standart AI2 kit, popular with Stalkers.";
		model = "\ButchersHell_Medical\data\AI.p3d";
		rotationFlags = 2;
		weight = 140;
		itemSize[] = {1,1};
		allowOwnedCargoManipulation = 1;
		randomQuantity = 2;
		canBeDigged = 1;
		isMeleeWeapon = 1;
	};
	class TMB_AI2_Military: Inventory_Base
	{
		scope = 2;
		displayName = "Military AI2 Kit";
		descriptionShort = "Military issued AI2 kit, used by Ukrain Military.";
		rotationFlags = 2;
		weight = 140;
		itemSize[] = {1,1};
		model = "\ButchersHell_Medical\data\AI_2.p3d";
		allowOwnedCargoManipulation = 1;
		randomQuantity = 2;
		canBeDigged = 1;
		isMeleeWeapon = 1;
	};
	class TMB_AI2_Scientific: Inventory_Base
	{
		scope = 2;
		displayName = "Scientific AI2 Kit";
		descriptionShort = "Scientific AI2 kit, Ecologist developed this kit to provide better treatment in the zone.";
		rotationFlags = 2;
		weight = 140;
		itemSize[] = {1,1};
		model = "\ButchersHell_Medical\data\AI_3.p3d";
		allowOwnedCargoManipulation = 1;
		randomQuantity = 2;
		canBeDigged = 1;
		isMeleeWeapon = 1;
	};
};
