class CfgPatches
{
	class Butchers_Hell_Medical
	{
		units[]={};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]=
		{
			"DZ_Data",
			"DZ_Scripts",
			"DZ_Weapons_Melee",
			"DZ_Gear_Containers",
			"DZ_Gear_Tools",
			"DZ_Weapons_Explosives",
			"sFrameWork",
			"sVisual",
			"DIV_Meds"
		};
	};
};
class CfgMods 
{
	class Butchers_Hell_Medical
	{
		name = "Butchers Hell Medical";
		dir = "Butchers_Hell_Medical";
		credits = "Butcher";
		author = "Butcher";
		type = "mod";
		dependencies[] =
		{
			"World"
		};
		class defs
		{
			class gameScriptModule
			{
				value = "";
				files[] = {"ButchersHell_Medical/Scripts/3_Game"};
			};
			class worldScriptModule
			{
				value = "";
				files[] = {"ButchersHell_Medical/Scripts/4_World"};
			};
			class missionScriptModule
			{
				value = "";
				files[] = {"ButchersHell_Medical/Scripts/5_Mission"};
			};
		};
	};
};