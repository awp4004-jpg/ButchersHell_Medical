class DIVXTG12Mdfr : ModifierBase {
    const int DURATION = 30; // Effect duration (30 seconds)
    const int NEGATIVE_EFFECT_INTERVAL = 1; // Interval for negative effects (every second)
    const float HEALTH_DECREASE = -1.0; // Health decreases every second
    const float ENERGY_DECREASE = -50.0; // Food decreases every second
    const float WATER_DECREASE = -50.0; // Water decreases every second

    protected float m_EffectStartTime = 0;
    protected float m_LastNegativeEffectTime = 0;

    override void Init() {
        m_TrackActivatedTime = true;
        m_IsPersistent = false;
        m_ID = new_DIV_eModifiers.MDF_DIV_XTG12;
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
        m_LastNegativeEffectTime = m_EffectStartTime;

        // Вылечиваем все болезни
        player.m_AgentPool.SetAgentCount(eAgents.CHOLERA, 0);
        player.m_AgentPool.SetAgentCount(eAgents.INFLUENZA, 0);
        player.m_AgentPool.SetAgentCount(eAgents.SALMONELLA, 0);
        player.m_AgentPool.SetAgentCount(eAgents.BRAIN, 0);
        player.m_AgentPool.SetAgentCount(eAgents.FOOD_POISON, 0);
        player.m_AgentPool.SetAgentCount(eAgents.CHEMICAL_POISON, 0);
        player.m_AgentPool.SetAgentCount(eAgents.WOUND_AGENT, 0);
        player.m_AgentPool.SetAgentCount(eAgents.NERVE_AGENT, 0);
        player.m_AgentPool.SetAgentCount(eAgents.HEAVYMETAL, 0);
    }

    override void OnDeactivate(PlayerBase player) {
        if (player.GetNotifiersManager()) {
            player.GetNotifiersManager().DeactivateByType(eNotifiers.NTF_PILLS);
        }
    }

    override bool DeactivateCondition(PlayerBase player) {
        return !player.IsAlive() || (GetAttachedTime() - m_EffectStartTime) >= DURATION;
    }

    override void OnTick(PlayerBase player, float deltaT) {
        float elapsedTime = GetAttachedTime() - m_EffectStartTime;
        if (!player.IsAlive()) {
            OnDeactivate(player);
            return;
        }
        // Отрицательный эффект каждые 1 секунду
        if (elapsedTime - m_LastNegativeEffectTime >= NEGATIVE_EFFECT_INTERVAL) {
            player.AddHealth("GlobalHealth", "Health", HEALTH_DECREASE);
            player.GetStatEnergy().Add(ENERGY_DECREASE);
            player.GetStatWater().Add(WATER_DECREASE);

            m_LastNegativeEffectTime = GetAttachedTime();
        }
    }
};
