class DIV_inj_SJ1 extends DIV_Inj_Base {
    override void OnApply(PlayerBase player) {
        if (player.GetModifiersManager().IsModifierActive(new_DIV_eModifiers.MDF_DIV_COMBAT_STIMULATOR_SJ1)) {
            player.GetModifiersManager().DeactivateModifier(new_DIV_eModifiers.MDF_DIV_COMBAT_STIMULATOR_SJ1);
        }
        player.GetModifiersManager().ActivateModifier(new_DIV_eModifiers.MDF_DIV_COMBAT_STIMULATOR_SJ1);
    }
};