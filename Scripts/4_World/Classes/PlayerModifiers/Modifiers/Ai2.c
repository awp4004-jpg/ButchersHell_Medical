class HealingAi2Mdfr : ModifierBase
{
    const int LIFETIME = 30;              // Total duration
    const int HEAL_DURATION = 20;         // Time it actually heals
    const float HEAL_PER_SECOND = 1.0;    // HP per second (lighter than AFAK)

    override void Init()
    {
        m_TrackActivatedTime = true;
        m_IsPersistent = false;
        m_ID = new_DIV_eModifiers.MDF_HEALING_AI2;
        m_TickIntervalInactive = DEFAULT_TICK_TIME_INACTIVE;
        m_TickIntervalActive = 1;
    }

    override bool ActivateCondition(PlayerBase player)
    {
        return false;
    }

    override bool DeactivateCondition(PlayerBase player)
    {
        return GetAttachedTime() > LIFETIME;
    }

    override void OnActivate(PlayerBase player)
    {
        if (player.GetNotifiersManager())
            player.GetNotifiersManager().ActivateByType(eNotifiers.NTF_PILLS);
    }

    override void OnDeactivate(PlayerBase player)
    {
        if (player.GetNotifiersManager())
            player.GetNotifiersManager().DeactivateByType(eNotifiers.NTF_PILLS);
    }

    override void OnTick(PlayerBase player, float deltaT)
    {
        if (GetAttachedTime() <= HEAL_DURATION)
        {
            if (player.GetHealth("GlobalHealth", "Health") < 100)
            {
                player.AddHealth("GlobalHealth", "Health", HEAL_PER_SECOND * deltaT);
            }
        }
    }
}