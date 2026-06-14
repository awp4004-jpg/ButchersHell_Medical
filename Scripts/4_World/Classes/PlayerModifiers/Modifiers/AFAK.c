class HealingAFAKMdfr : ModifierBase
{
    const int LIFETIME = 90;              // Total duration (90 seconds)
    const int HEAL_DURATION = 60;         // Time it actually heals
    const float HEAL_PER_SECOND = 0.9;    // HP healed per second

    override void Init()
    {
        m_TrackActivatedTime = true;
        m_IsPersistent = false;
        m_ID = new_DIV_eModifiers.MDF_HEALING_AFAK;
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