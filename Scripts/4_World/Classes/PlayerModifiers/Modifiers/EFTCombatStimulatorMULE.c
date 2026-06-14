class DIVCombatStimulatorMULE: ModifierBase {
    const int INITIAL_DURATION = 900; // The duration of the first stage is 900 seconds
    const int SECONDARY_DURATION = 60; // The duration of the second stage is 60 seconds
    const int POSITIVE_EFFECT_INTERVAL = 1; // Interval for positive effects
    const int NEGATIVE_EFFECT_INTERVAL = 1; // Interval for negative effects
    
    const float STAMINA_INCREASE = 50.0; // Increase stamina every second
    const float SHOCK_DECREASE = 20.0; // Shock Damage
    const int SHAKES_EFFECT = 10; // Strength of the shaking effect

    protected float m_LastPositiveEffectTime = 0;
    protected bool m_SecondaryEffectActive = false;

    override void Init() {
        m_TrackActivatedTime = true;
        m_IsPersistent = false;
        m_ID = new_DIV_eModifiers.MDF_DIV_COMBAT_STIMULATOR_MULE;
        m_TickIntervalInactive = DEFAULT_TICK_TIME_INACTIVE;
        m_TickIntervalActive = 1;
    }

    override bool ActivateCondition(PlayerBase player) {
        return false;
    }

    override void OnActivate(PlayerBase player) {
        if( player.GetNotifiersManager() ) player.GetNotifiersManager().ActivateByType(eNotifiers.NTF_PILLS);
        float currentStamina = player.GetStaminaHandler().GetStamina();
        player.GetStaminaHandler().SetStamina(currentStamina + 30);        
        m_LastPositiveEffectTime = GetAttachedTime();
        m_SecondaryEffectActive = false;
    }

    override void OnDeactivate(PlayerBase player) {
        if( player.GetNotifiersManager() ) player.GetNotifiersManager().DeactivateByType(eNotifiers.NTF_PILLS);
        float currentStamina = player.GetStaminaHandler().GetStamina();
        player.GetStaminaHandler().SetStamina(currentStamina - 30);
        player.SetShakesForced(0);
    }

    override bool DeactivateCondition(PlayerBase player) {
        return GetAttachedTime() >= (INITIAL_DURATION + SECONDARY_DURATION) || player.GetHealth("GlobalHealth", "Health") <= 0;
    }

    override void OnTick(PlayerBase player, float deltaT) {
        float attachedTime = GetAttachedTime();
        
        // Проверяем, жив ли игрок
        if (!player.IsAlive()) 
			{
				OnDeactivate(player);
				return;
			}
        // Положительные эффекты (каждую секунду)
        if (attachedTime - m_LastPositiveEffectTime >= POSITIVE_EFFECT_INTERVAL) {
            if (attachedTime < INITIAL_DURATION) {
                float currentStamina = player.GetStaminaHandler().GetStamina();
                player.GetStaminaHandler().SetStamina(currentStamina + STAMINA_INCREASE);
            } else if (attachedTime >= INITIAL_DURATION && attachedTime < (INITIAL_DURATION + SECONDARY_DURATION)) {
                if (!m_SecondaryEffectActive) {
                    m_SecondaryEffectActive = true;
                }
                player.SetShakesForced(SHAKES_EFFECT);
                player.SetHealth("GlobalHealth", "Shock", SHOCK_DECREASE);
            }
            m_LastPositiveEffectTime = attachedTime;
        }
    }
};
