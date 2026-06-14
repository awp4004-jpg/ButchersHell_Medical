class DIVGoldstarMdfr : ModifierBase
{
    const int DURATION_SHOCK_100 = 600;
    const int DURATION_SHOCK_40 = 30;
    const float SHOCK_VALUE_100 = 100.0;
    const float SHOCK_VALUE_40 = 40.0;

    const int LIFETIME = DURATION_SHOCK_100;

    protected int m_EffectPhase = 0;
    protected float m_PostEffectEndTime = 0.0;

    override void Init()
    {
        m_TrackActivatedTime = true;
        m_IsPersistent = true;
        m_ID = new_DIV_eModifiers.MDF_DIV_GOLDSTAR;
        m_TickIntervalInactive = DEFAULT_TICK_TIME_INACTIVE;
        m_TickIntervalActive = 1;
    }

    override bool ActivateCondition(PlayerBase player)
    {
        return false;
    }

    override void OnReconnect(PlayerBase player)
    {
        OnActivate(player);
    }

    override void OnActivate(PlayerBase player)
    {
        if (player.GetNotifiersManager())
        {
            player.GetNotifiersManager().ActivateByType(eNotifiers.NTF_PILLS);
        }

        m_EffectPhase = 0;
        m_PostEffectEndTime = 0.0;
    }

    override void OnDeactivate(PlayerBase player)
    {
        if (player.GetNotifiersManager())
        {
            player.GetNotifiersManager().DeactivateByType(eNotifiers.NTF_PILLS);
        }
    }

    override bool DeactivateCondition(PlayerBase player)
    {
        float current_time = GetAttachedTime();

        if (!player.IsAlive())
        {
            return true;
        }

        if (m_EffectPhase == 0 && current_time >= LIFETIME)
        {
            m_EffectPhase = 1;
            m_PostEffectEndTime = current_time + DURATION_SHOCK_40;
            player.SetHealth("", "Shock", SHOCK_VALUE_40);
        }

        if (m_EffectPhase == 1 && current_time >= m_PostEffectEndTime)
        {
            return true;
        }

        return false;
    }

    override void OnTick(PlayerBase player, float deltaT)
    {
        if (!player.IsAlive())
        {
            return;
        }

        float target_shock_value = SHOCK_VALUE_100;
        if (m_EffectPhase == 1)
        {
            target_shock_value = SHOCK_VALUE_40;
        }

        float current_shock = player.GetHealth("", "Shock");
        if (current_shock != target_shock_value)
        {
            player.SetHealth("", "Shock", target_shock_value);
        }
    }
};