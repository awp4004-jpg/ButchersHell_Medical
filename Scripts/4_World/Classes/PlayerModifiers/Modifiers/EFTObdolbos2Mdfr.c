class DIVObdolbos2Mdfr : ModifierBase {
    const int POSITIVE_DURATION = 60; // Duration of the positive effect (60 seconds)
    const int POSITIVE_INTERVAL = 3; // Interval for the positive effect (every 3 seconds)
    const int NEGATIVE_INTERVAL = 10; // Interval for negative effects (every 10 seconds)
    const float HEALTH_REGEN_AMOUNT = 1.0; // Amount of health restored per tick
    const float ENERGY_DECREASE = -100.0; // Amount of energy deducted every 10 seconds
    const float WATER_DECREASE = -100.0; // Amount of water deducted every 10 seconds
    const int FINAL_SHOCK_VALUE = 20; // Shock at the end of the effect

    protected float m_EffectStartTime = 0;
    protected float m_LastPositiveEffectTime = 0;
    protected float m_LastNegativeEffectTime = 0;
    protected bool m_PositiveEffectEnded = false;

    override void Init() {
        m_TrackActivatedTime = true;
        m_IsPersistent = false;
        m_ID = new_DIV_eModifiers.MDF_DIV_OBDOLBOS2;
        m_TickIntervalInactive = DEFAULT_TICK_TIME_INACTIVE;
        m_TickIntervalActive = 1;
    }

    override bool ActivateCondition(PlayerBase player) {
        return false;
    }

    override void OnActivate(PlayerBase player) {
        if (Math.RandomFloat01() <= 0.25) {
            player.AddHealth("GlobalHealth", "Health", -100);
            return;
        }

        if (player.GetNotifiersManager()) {
            player.GetNotifiersManager().ActivateByType(eNotifiers.NTF_PILLS);
        }

        m_EffectStartTime = GetAttachedTime();
        m_LastPositiveEffectTime = m_EffectStartTime;
        m_LastNegativeEffectTime = m_EffectStartTime;
    }

    override void OnDeactivate(PlayerBase player) {
        if (player.GetNotifiersManager()) {
            player.GetNotifiersManager().DeactivateByType(eNotifiers.NTF_PILLS);
        }
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

        // Положительный эффект каждые 3 секунды
        if (elapsedTime <= POSITIVE_DURATION && elapsedTime - m_LastPositiveEffectTime >= POSITIVE_INTERVAL) {
            player.AddHealth("GlobalHealth", "Health", HEALTH_REGEN_AMOUNT);
            m_LastPositiveEffectTime = GetAttachedTime();
        } else if (elapsedTime > POSITIVE_DURATION && !m_PositiveEffectEnded) {
            m_PositiveEffectEnded = true;
        }

        // Отрицательный эффект каждые 10 секунд
        if (elapsedTime - m_LastNegativeEffectTime >= NEGATIVE_INTERVAL) {
            player.GetStatWater().Add(WATER_DECREASE);
            player.GetStatEnergy().Add(ENERGY_DECREASE);
            m_LastNegativeEffectTime = GetAttachedTime();
            player.SetHealth("GlobalHealth", "Shock", FINAL_SHOCK_VALUE);
        }
    }
};
