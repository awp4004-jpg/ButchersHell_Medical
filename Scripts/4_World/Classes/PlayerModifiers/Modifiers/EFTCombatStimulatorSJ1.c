class DIVCombatStimulatorSJ1: ModifierBase {
    const int INITIAL_DURATION = 100; // Duration of the first stage is 100 seconds
    const int SECONDARY_DURATION = 180; // Duration of the second stage is 180 seconds
    const int POSITIVE_EFFECT_INTERVAL = 1; // Interval for positive effects
    const int NEGATIVE_EFFECT_INTERVAL = 1; // Interval for negative effects

    const float STAMINA_INCREASE = 20.0; // Increase stamina
    const float ENERGY_DECREASE = -0.5; // Decrease energy
    const float WATER_DECREASE = -0.5; // Decrease hydration

    protected float m_LastPositiveEffectTime = 0;
    protected float m_LastNegativeEffectTime = 0;
    protected bool m_SecondaryEffectActive = false;

    override void Init() {
        m_TrackActivatedTime = true;
        m_IsPersistent = false;
        m_ID = new_DIV_eModifiers.MDF_DIV_COMBAT_STIMULATOR_SJ1;
        m_TickIntervalInactive = DEFAULT_TICK_TIME_INACTIVE;
        m_TickIntervalActive = 1;
    }

    override bool ActivateCondition(PlayerBase player) {
        return false;
    }

    override void OnActivate(PlayerBase player) {
		if( player.GetNotifiersManager() ) player.GetNotifiersManager().ActivateByType(eNotifiers.NTF_PILLS);
        // Изначально увеличиваем выносливость
        float currentStamina = player.GetStaminaHandler().GetStamina();
        player.GetStaminaHandler().SetStamina(currentStamina + STAMINA_INCREASE); // Увеличиваем выносливость на 20
        m_LastPositiveEffectTime = GetAttachedTime(); // Устанавливаем время для первого положительного эффекта
        m_SecondaryEffectActive = false;
    }

    override void OnDeactivate(PlayerBase player) {
        // Сбрасываем все эффекты
		if( player.GetNotifiersManager() ) player.GetNotifiersManager().DeactivateByType(eNotifiers.NTF_PILLS);
        float currentStamina = player.GetStaminaHandler().GetStamina();
        player.GetStaminaHandler().SetStamina(currentStamina - STAMINA_INCREASE); // Сбрасываем увеличение выносливости
        player.GetStatWater().Add(-SECONDARY_DURATION * WATER_DECREASE); // Сбрасываем гидрацию
        player.GetStatEnergy().Add(-SECONDARY_DURATION * ENERGY_DECREASE); // Сбрасываем энергию
        player.SetShakesForced(0); // Убираем эффект тряски
    }

    override bool DeactivateCondition(PlayerBase player) {
        return GetAttachedTime() >= (INITIAL_DURATION + SECONDARY_DURATION) || player.GetHealth("GlobalHealth", "Health") <= 0; // Завершение действия модификатора
    }

    override void OnTick(PlayerBase player, float deltaT) {
        float attachedTime = GetAttachedTime();
			if (!player.IsAlive()) 
			{
				OnDeactivate(player);
				return;
			}
        // Положительные эффекты (каждую секунду)
        if (attachedTime - m_LastPositiveEffectTime >= POSITIVE_EFFECT_INTERVAL) {
            if (attachedTime < INITIAL_DURATION) {
                // Увеличиваем выносливость в первый этап (до 100 секунд)
                float currentStamina = player.GetStaminaHandler().GetStamina();
                player.GetStaminaHandler().SetStamina(currentStamina + STAMINA_INCREASE);
            } else if (attachedTime >= INITIAL_DURATION && attachedTime < (INITIAL_DURATION + SECONDARY_DURATION)) {
                // Активируем второй этап после 100 секунд
                if (!m_SecondaryEffectActive) {
                    m_SecondaryEffectActive = true; // Активируем второй этап
                }

                // Уменьшаем энергию и гидрацию на втором этапе
                player.GetStatEnergy().Add(ENERGY_DECREASE);
                player.GetStatWater().Add(WATER_DECREASE);
                player.SetShakesForced(3); // Трясение экрана
            }

            // Обновляем время последнего положительного эффекта
            m_LastPositiveEffectTime = attachedTime;
        }
    }
};
