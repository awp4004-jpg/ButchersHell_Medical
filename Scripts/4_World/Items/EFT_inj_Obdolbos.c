class DIV_inj_Obdolbos extends DIV_Inj_Base {
    override void OnApply(PlayerBase player) {
        if (player.GetModifiersManager().IsModifierActive(new_DIV_eModifiers.MDF_DIV_OBDOLBOS)) {
            player.GetModifiersManager().DeactivateModifier(new_DIV_eModifiers.MDF_DIV_OBDOLBOS);
        }
        player.GetModifiersManager().ActivateModifier(new_DIV_eModifiers.MDF_DIV_OBDOLBOS);
    }
};