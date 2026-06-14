class DIV_inj_MULE extends DIV_Inj_Base {
    override void OnApply(PlayerBase player) {
        if (player.GetModifiersManager().IsModifierActive(new_DIV_eModifiers.MDF_DIV_COMBAT_STIMULATOR_MULE)) {
            player.GetModifiersManager().DeactivateModifier(new_DIV_eModifiers.MDF_DIV_COMBAT_STIMULATOR_MULE);
        }
        player.GetModifiersManager().ActivateModifier(new_DIV_eModifiers.MDF_DIV_COMBAT_STIMULATOR_MULE);
    }
};