class DIV_inj_SJ6 extends DIV_Inj_Base {
    override void OnApply(PlayerBase player) {
        if (player.GetModifiersManager().IsModifierActive(new_DIV_eModifiers.MDF_DIV_COMBAT_STIMULATOR_SJ6)) {
            player.GetModifiersManager().DeactivateModifier(new_DIV_eModifiers.MDF_DIV_COMBAT_STIMULATOR_SJ6);
        }
        player.GetModifiersManager().ActivateModifier(new_DIV_eModifiers.MDF_DIV_COMBAT_STIMULATOR_SJ6);
    }
};