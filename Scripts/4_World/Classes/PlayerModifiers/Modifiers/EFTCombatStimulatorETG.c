class DIVCombatStimulatorETG: ModifierBase {
    const int INITIAL_DURATION = 60; // Duration of the first stage is 60 seconds
    const int SECONDARY_DURATION = 60; // Duration of the second stage is 60 seconds
    const int POSITIVE_EFFECT_INTERVAL = 1; // Interval for positive effects
    const int NEGATIVE_EFFECT_INTERVAL = 5; // Interval for negative effects

    const float FOOD_WATER_INCREASE = 10.0; // Increase food and water every second
    const float HEALTH_REGENERATION = 3.0; // Health regeneration every second
    const float STAMINA_DECREASE = 5.0; // Decrease stamina every 5 seconds
    const float FOOD_WATER_DECREASE = -100.0; // Decrease food and water every 5 seconds

    protected float m_LastPositiveEffectTime = 0;
    protected float m_LastNegativeEffectTime = 0;
    protected bool m_SecondaryEffectActive = false;

    override void Init() {
        m_TrackActivatedTime = true;
        m_IsPersistent = false;
        m_ID = new_DIV_eModifiers.MDF_DIV_COMBAT_STIMULATOR_ETG;
        m_TickIntervalInactive = DEFAULT_TICK_TIME_INACTIVE;
        m_TickIntervalActive = 1;
    }

    override bool ActivateCondition(PlayerBase player) {
        return false;
    }

    override void OnActivate(PlayerBase player) {
        if (player.GetNotifiersManager()) player.GetNotifiersManager().ActivateByType(eNotifiers.NTF_PILLS);
        
        m_LastPositiveEffectTime = GetAttachedTime();
        m_LastNegativeEffectTime = 0;
        m_SecondaryEffectActive = false;
    }

    override void OnDeactivate(PlayerBase player) {
        if (player.GetNotifiersManager()) player.GetNotifiersManager().DeactivateByType(eNotifiers.NTF_PILLS);
        
        // Сбрасываем все эффекты
        player.GetStatEnergy().Add(-SECONDARY_DURATION * FOOD_WATER_DECREASE); // Сбрасываем еду
        player.GetStatWater().Add(-SECONDARY_DURATION * FOOD_WATER_DECREASE); // Сбрасываем воду
        player.SetShakesForced(0); // Убираем эффект тряски
    }

    override bool DeactivateCondition(PlayerBase player) {
        return GetAttachedTime() >= (INITIAL_DURATION + SECONDARY_DURATION) || player.GetHealth("GlobalHealth", "Health") <= 0;
    }

    override void OnTick(PlayerBase player, float deltaT) {
        float attachedTime = GetAttachedTime();

        // Проверяем, жив ли игрок
        if (!player.IsAlive()) {
            OnDeactivate(player);
            return;
        }

        // Положительные эффекты (каждую секунду)
        if (attachedTime - m_LastPositiveEffectTime >= POSITIVE_EFFECT_INTERVAL) {
            if (attachedTime < INITIAL_DURATION) {
                player.GetStatEnergy().Add(FOOD_WATER_INCREASE); // Увеличиваем еду
                player.GetStatWater().Add(FOOD_WATER_INCREASE); // Увеличиваем воду
                player.AddHealth("GlobalHealth", "Health", HEALTH_REGENERATION); // Регенерация здоровья
            } else if (attachedTime >= INITIAL_DURATION && attachedTime < (INITIAL_DURATION + SECONDARY_DURATION)) {
                // Активируем второй этап после 60 секунд
                if (!m_SecondaryEffectActive) {
                    m_SecondaryEffectActive = true; // Активируем второй этап
                }

                // Применяем отрицательные эффекты каждые 5 секунд
                if (attachedTime - m_LastNegativeEffectTime >= NEGATIVE_EFFECT_INTERVAL) {
                    player.GetStaminaHandler().SetStamina(player.GetStaminaHandler().GetStamina() - STAMINA_DECREASE);
                    player.GetStatEnergy().Add(FOOD_WATER_DECREASE);
                    player.GetStatWater().Add(FOOD_WATER_DECREASE);

                    m_LastNegativeEffectTime = attachedTime;
                }
            }

            // Обновляем время последнего положительного эффекта
            m_LastPositiveEffectTime = attachedTime;
        }
    }
};
