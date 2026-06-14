class DIVCombatStimulatorZagustin: ModifierBase {
    const int INITIAL_DURATION = 180; // Duration of the first stage is 180 seconds
    const int SECONDARY_DURATION = 40; // Duration of the second stage is 40 seconds
    const int POSITIVE_EFFECT_INTERVAL = 1; // Interval for positive effects
    const int NEGATIVE_EFFECT_INTERVAL = 1; // Interval for negative effects

    const float BLEEDING_REMOVAL_INTERVAL = 1.0; // Interval for removing bleeding
    const float ENERGY_DECREASE = -10.0; // Decreases energy every second
    const float WATER_DECREASE = -10.0; // Decreases water every second
    const int SHAKES_EFFECT = 10; // Strength of the shaking effect

    protected float m_LastPositiveEffectTime = 0;
    protected bool m_SecondaryEffectActive = false;

    override void Init() {
        m_TrackActivatedTime = true;
        m_IsPersistent = false;
        m_ID = new_DIV_eModifiers.MDF_DIV_COMBAT_STIMULATOR_ZAGUSTIN;
        m_TickIntervalInactive = DEFAULT_TICK_TIME_INACTIVE;
        m_TickIntervalActive = 1;
    }

    override bool ActivateCondition(PlayerBase player) {
        return false;
    }

    override void OnActivate(PlayerBase player) {
        if (player.GetNotifiersManager()) player.GetNotifiersManager().ActivateByType(eNotifiers.NTF_PILLS);
        
        // Убираем кровотечения
        player.GetBleedingManagerServer().RemoveMostSignificantBleedingSource();
        player.m_AgentPool.SetAgentCount(eAgents.WOUND_AGENT, 0);
        player.AddHealth("GlobalHealth", "Health", 0.1); 
        
        m_LastPositiveEffectTime = GetAttachedTime();
        m_SecondaryEffectActive = false;
    }

    override void OnDeactivate(PlayerBase player) {
        if (player.GetNotifiersManager()) player.GetNotifiersManager().DeactivateByType(eNotifiers.NTF_PILLS);
        player.SetShakesForced(0);
    }

    override bool DeactivateCondition(PlayerBase player) {
        return GetAttachedTime() >= (INITIAL_DURATION + SECONDARY_DURATION) || player.GetHealth("GlobalHealth", "Health") <= 0;
    }

    override void OnTick(PlayerBase player, float deltaT) {
        float attachedTime = GetAttachedTime();
        if (!player.IsAlive()) {
            OnDeactivate(player);
            return;
        }

        // Положительные эффекты (каждую секунду)
        if (attachedTime - m_LastPositiveEffectTime >= POSITIVE_EFFECT_INTERVAL) {
            if (attachedTime < INITIAL_DURATION) {
                // Убираем кровотечения каждую секунду
                player.GetBleedingManagerServer().RemoveMostSignificantBleedingSource();
                player.m_AgentPool.SetAgentCount(eAgents.WOUND_AGENT, 0);
                player.AddHealth("GlobalHealth", "Health", 0.1);
            } else if (attachedTime >= INITIAL_DURATION && attachedTime < (INITIAL_DURATION + SECONDARY_DURATION)) {
                // Активируем второй этап после 170 секунд
                if (!m_SecondaryEffectActive) {
                    m_SecondaryEffectActive = true;
                }
                player.SetShakesForced(SHAKES_EFFECT); // Тремор экрана
                player.GetStatEnergy().Add(ENERGY_DECREASE); // Уменьшаем энергию
                player.GetStatWater().Add(WATER_DECREASE); // Уменьшаем воду
            }
            m_LastPositiveEffectTime = attachedTime;
        }
    }
};
