class DIV_inj_Zagustin extends DIV_Inj_Base {
    override void OnApply(PlayerBase player) {
        if (player.GetModifiersManager().IsModifierActive(new_DIV_eModifiers.MDF_DIV_COMBAT_STIMULATOR_ZAGUSTIN)) {
            player.GetModifiersManager().DeactivateModifier(new_DIV_eModifiers.MDF_DIV_COMBAT_STIMULATOR_ZAGUSTIN);
        }
        player.GetModifiersManager().ActivateModifier(new_DIV_eModifiers.MDF_DIV_COMBAT_STIMULATOR_ZAGUSTIN);
    }
};