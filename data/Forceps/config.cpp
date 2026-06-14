class CfgPatches
{
    class BUTCH_forceps
    {
        requiredAddons[] =
        {
            "DZ_Data"
        };
    };
};

class CfgVehicles
{
    class Inventory_Base;
    class DIV_med_Forceps : Inventory_Base
    {
        scope = 2;
        displayName = "Forceps";
        descriptionShort = "Special medical instrument";
        model = "\ButchersHell_Medical\data\Forceps\forceps.p3d";
        debug_ItemCategory = 2;
        animClass = "Knife";
        rotationFlags = 17;
        weight = 120;
        fragility = 0.01;
        itemSize[] = {1, 2};
        soundImpactType = "metal";
        class MeleeModes
        {
            class Default
            {
                ammo = "MeleeFistLight";
                range = 1;
            };
            class Heavy
            {
                ammo = "MeleeFistHeavy";
                range = 1;
            };
            class Sprint
            {
                ammo = "MeleeFistHeavy";
                range = 2.8;
            };
        };
        class DamageSystem
        {
            class GlobalHealth
            {
                class Health
                {
                    hitpoints = 100;
                    healthLevels[] =
                    {
                        {1, {"ButchersHell_Medical\data\Forceps\data\Forceps.rvmat"}},
                        {0.7, {"ButchersHell_Medical\data\Forceps\data\Forceps.rvmat"}},
                        {0.5, {"ButchersHell_Medical\data\Forceps\data\Forceps_damage.rvmat"}},
                        {0.3, {"ButchersHell_Medical\data\Forceps\data\Forceps_damage.rvmat"}},
                        {0, {"ButchersHell_Medical\data\Forceps\data\Forceps_destruct.rvmat"}}
                    };
                };
            };
        };
        class AnimEvents
        {
            class SoundWeapon
            {
                class pickUpItem
                {
                    soundSet = "pickUpPliers_SoundSet";
                    id = 797;
                };
                class Pliers_loop
                {
                    soundSet = "Pliers_loop_SoundSet";
                    id = 203;
                };
            };
        };
    };
};