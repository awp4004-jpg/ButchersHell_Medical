modded class ModItemRegisterCallbacks
{
	override void RegisterOneHanded( DayZPlayerType pType, DayzPlayerItemBehaviorCfg pBehavior )
    {
		super.RegisterOneHanded( pType, pBehavior );
		pType.AddItemInHandsProfileIK("DIV_med_Salewa", "ButchersHell_Medical/Animations/Bandage/MF_BP_Bandage.asi", pBehavior,"dz/anims/anm/player/ik/gear/bandage_dressing.anm");
		pType.AddItemInHandsProfileIK("DIV_med_IFAK", "ButchersHell_Medical/Animations/Bandage/MF_BP_Bandage.asi", pBehavior,"dz/anims/anm/player/ik/gear/bandage_dressing.anm");
		pType.AddItemInHandsProfileIK("DIV_med_AFAK", "ButchersHell_Medical/Animations/Bandage/MF_BP_Bandage.asi", pBehavior,"dz/anims/anm/player/ik/gear/bandage_dressing.anm");
		pType.AddItemInHandsProfileIK("DIV_med_Splint", "dz/anims/workspaces/player/player_main/player_main_1h.asi", pBehavior,"dz/anims/anm/player/ik/gear/first_aid_kit.anm");
		// pType.AddItemInHandsProfileIK("DIV_Inj_Base", "dz/anims/workspaces/player/player_main/props/player_main_1h_morphine.asi", pBehavior,"dz/anims/anm/player/ik/gear/morphine.anm");
		pType.AddItemInHandsProfileIK("DIV_med_GoldStar_base", "dz/anims/workspaces/player/player_main/player_main_1h.asi", pBehavior,"dz/anims/anm/player/ik/gear/bait_worm.anm");
        pType.AddItemInHandsProfileIK("DIV_med_Cat_Base", "dz/anims/workspaces/player/player_main/player_main_1h.asi", pBehavior,"dz/anims/anm/player/ik/ammunition/9mm_25rnd_box.anm");
        pType.AddItemInHandsProfileIK("DIV_med_CALOK_Base", "dz/anims/workspaces/player/player_main/player_main_1h.asi", pBehavior,"dz/anims/anm/player/ik/ammunition/9mm_25rnd_box.anm");
        pType.AddItemInHandsProfileIK("DIV_med_Esmarch_Base", "dz/anims/workspaces/player/player_main/player_main_1h.asi", pBehavior,"dz/anims/anm/player/ik/ammunition/9mm_25rnd_box.anm");
		pType.AddItemInHandsProfileIK("DIV_med_CMS", "ButchersHell_Medical/Animations/Bandage/MF_BP_Bandage.asi", pBehavior,"dz/anims/anm/player/ik/gear/bandage_dressing.anm");
		pType.AddItemInHandsProfileIK("DIV_med_Grizly", "ButchersHell_Medical/Animations/Bandage/MF_BP_Bandage.asi", pBehavior,"dz/anims/anm/player/ik/gear/bandage_dressing.anm");
		pType.AddItemInHandsProfileIK("DIV_med_ai2", "ButchersHell_Medical/Animations/Bandage/MF_BP_Bandage.asi", pBehavior,"dz/anims/anm/player/ik/gear/bandage_dressing.anm");
		pType.AddItemInHandsProfileIK("DIV_med_Surv", "ButchersHell_Medical/Animations/Bandage/MF_BP_Bandage.asi", pBehavior,"dz/anims/anm/player/ik/gear/bandage_dressing.anm");
		pType.AddItemInHandsProfileIK("DIV_Inj_Base","ButchersHell_Medical/Animations/Injecto/MF_Injeckt.asi",pBehavior,"dz/anims/anm/player/ik/gear/morphine.anm");
	};
}