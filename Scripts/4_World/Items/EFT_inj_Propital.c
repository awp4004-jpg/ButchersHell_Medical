class DIV_inj_Propital extends DIV_Inj_Base { 

	override void OnApply(PlayerBase player) {
		if( player.GetModifiersManager().IsModifierActive(new_DIV_eModifiers.MDF_DIV_PROPITAL ) ) 
		{
			player.GetModifiersManager().DeactivateModifier(new_DIV_eModifiers.MDF_DIV_PROPITAL ); 
		} 
		player.GetModifiersManager().ActivateModifier(new_DIV_eModifiers.MDF_DIV_PROPITAL ); } 
};