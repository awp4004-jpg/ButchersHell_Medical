class DIVPropitalMdfr: ModifierBase { 
    const int DURATION = 300; // Duration of action
    const int REGEN_INTERVAL = 3; // Regeneration interval
    const int HUNGER_LOSS = 1000; // Energy loss
    const int WATER_LOSS = 1000; // Water loss

    override void Init()
    {
        m_TrackActivatedTime = true;
        m_IsPersistent = false;
        m_ID = new_DIV_eModifiers.MDF_DIV_PROPITAL;
        m_TickIntervalInactive = DEFAULT_TICK_TIME_INACTIVE;
        m_TickIntervalActive = REGEN_INTERVAL;
        DisableActivateCheck();
    }

    override bool ActivateCondition(PlayerBase player)
    {
        return false;
    }

    override void OnActivate(PlayerBase player)
    {
        if (player.GetNotifiersManager()) {
            player.GetNotifiersManager().ActivateByType(eNotifiers.NTF_PILLS);
        }		
    }

    override void OnDeactivate(PlayerBase player)
    {
        if (player.GetNotifiersManager()) {
            player.GetNotifiersManager().DeactivateByType(eNotifiers.NTF_PILLS);
        }
        player.GetStatEnergy().Add(-HUNGER_LOSS);
        player.GetStatWater().Add(-WATER_LOSS);
    }

    override bool DeactivateCondition(PlayerBase player)
    {
        float attached_time = GetAttachedTime();
        return attached_time >= DURATION || player.GetHealth("GlobalHealth", "Health") <= 0;
    }

    override void OnTick(PlayerBase player, float deltaT)
    {
        float attachedTime = GetAttachedTime();		
        if (player.GetHealth("GlobalHealth", "Health") <= 0) {
            OnDeactivate(player);
            return;
        }
		
        if (attachedTime > 0 && attachedTime <= DURATION - REGEN_INTERVAL + 1)
        {
            if (player.GetHealth("GlobalHealth", "Health") > 0)
            {
                player.AddHealth("GlobalHealth", "Health", 1);
            }
        }
    }
};
