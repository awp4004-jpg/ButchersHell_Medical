class DIVObdolbosMdfr: ModifierBase {
    const int DURATION = 300; // Duration is 300 seconds
    const int POSITIVE_EFFECT_INTERVAL = 3; // Interval for positive effects
    const int NEGATIVE_EFFECT_INTERVAL = 5; // Interval for negative effects
    const float HEALTH_REGEN_AMOUNT = 0.5; // Amount of health restored per tick
    const float STAMINA_INCREASE = 10.0; // Amount of stamina increase

    protected float m_LastPositiveEffectTime = 0; // Time of the last positive effect
    protected float m_LastNegativeEffectTime = 0; // Time of the last negative effect

    override void Init() {
        m_TrackActivatedTime = true;
        m_IsPersistent = false;
        m_ID = new_DIV_eModifiers.MDF_DIV_OBDOLBOS;
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
        float currentStamina = player.GetStaminaHandler().GetStamina();
        player.GetStaminaHandler().SetStamina(currentStamina + 20);
        m_LastPositiveEffectTime = GetAttachedTime();
        m_LastNegativeEffectTime = GetAttachedTime();
    }

    override void OnDeactivate(PlayerBase player) {
        if (player.GetNotifiersManager()) {
            player.GetNotifiersManager().DeactivateByType(eNotifiers.NTF_PILLS);
        }
        float currentStamina = player.GetStaminaHandler().GetStamina();
        player.GetStaminaHandler().SetStamina(currentStamina - 20);
    }

    override bool DeactivateCondition(PlayerBase player) {
        return GetAttachedTime() >= DURATION || player.GetHealth("GlobalHealth", "Health") <= 0;
    }

    override void OnTick(PlayerBase player, float deltaT) {
        float attachedTime = GetAttachedTime();
        if (!player.IsAlive()) 
			{
				OnDeactivate(player);
				return;
			}
        // Положительные эффекты (каждые 3 секунды)
        if (attachedTime - m_LastPositiveEffectTime >= POSITIVE_EFFECT_INTERVAL) {
            if (player.GetHealth("GlobalHealth", "Health") > 0) {
                player.AddHealth("GlobalHealth", "Health", HEALTH_REGEN_AMOUNT);
            }
            float currentStamina = player.GetStaminaHandler().GetStamina();
            player.GetStaminaHandler().SetStamina(currentStamina + STAMINA_INCREASE);
            m_LastPositiveEffectTime = attachedTime;
        }

        // Отрицательные эффекты (каждые 5 секунд)
        if (attachedTime - m_LastNegativeEffectTime >= NEGATIVE_EFFECT_INTERVAL) {
            if (Math.RandomFloat01() <= 0.10) {
                player.AddHealth("GlobalHealth", "Shock", -50);
                player.GetStatWater().Add(-100.0);
                player.GetStatEnergy().Add(-100.0);
            }
            m_LastNegativeEffectTime = attachedTime;
        }
    }
};
