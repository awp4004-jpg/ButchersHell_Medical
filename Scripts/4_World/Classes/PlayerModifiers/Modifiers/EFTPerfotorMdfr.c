class DIVPerfotorMdfr : ModifierBase {
    const int POSITIVE_DURATION = 60; // Duration of the positive effect (60 seconds)
    const int BLOOD_REGEN_INTERVAL = 1; // Interval for blood regeneration (every second)
    const float BLOOD_REGEN_AMOUNT = 50.0; // Amount of blood restored every second
    const float ENERGY_DECREASE = -500.0; // Energy drained after the effect ends
    const float WATER_DECREASE = -500.0; // Water drained after the effect ends
    const int FINAL_SHOCK_VALUE = 20; // Shock value after the effect ends

    protected float m_EffectStartTime = 0;
    protected float m_LastBloodRegenTime = 0;
    protected bool m_PositiveEffectEnded = false;

    override void Init() {
        m_TrackActivatedTime = true;
        m_IsPersistent = false;
        m_ID = new_DIV_eModifiers.MDF_DIV_PERFOTOR;
        m_TickIntervalInactive = DEFAULT_TICK_TIME_INACTIVE;
        m_TickIntervalActive = 1;
    }

    override bool ActivateCondition(PlayerBase player) {
        return false;
    }

    override void OnActivate(PlayerBase player) {
        if (player.GetNotifiersManager()) {
            player.GetNotifiersManager().ActivateByType(eNotifiers.NTF_PILLS);
        }

        m_EffectStartTime = GetAttachedTime();
        m_LastBloodRegenTime = m_EffectStartTime;
    }

    override void OnDeactivate(PlayerBase player) {
        if (player.GetNotifiersManager()) {
            player.GetNotifiersManager().DeactivateByType(eNotifiers.NTF_PILLS);
        }
        player.GetStatWater().Add(WATER_DECREASE);
        player.GetStatEnergy().Add(ENERGY_DECREASE);
        player.SetHealth("GlobalHealth", "Shock", FINAL_SHOCK_VALUE);
    }

    override bool DeactivateCondition(PlayerBase player) {
        return !player.IsAlive() || (GetAttachedTime() - m_EffectStartTime) >= POSITIVE_DURATION;
    }

    override void OnTick(PlayerBase player, float deltaT) {
        float elapsedTime = GetAttachedTime() - m_EffectStartTime;

        if (!player.IsAlive()) {
            OnDeactivate(player);
            return;
        }
        // Регенерация крови каждую секунду в течение 60 секунд
        if (elapsedTime <= POSITIVE_DURATION && elapsedTime - m_LastBloodRegenTime >= BLOOD_REGEN_INTERVAL) {
            player.AddHealth("GlobalHealth", "Blood", BLOOD_REGEN_AMOUNT);
            m_LastBloodRegenTime = GetAttachedTime();
        }
		
        if (elapsedTime > POSITIVE_DURATION && !m_PositiveEffectEnded) {
            m_PositiveEffectEnded = true;
        }
    }
};
