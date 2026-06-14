class mAI2_Military: ModifierBase
{
	const int	LIFETIME	 		= 180;
		
	const int 	REGEN_HP_TIME 		= 30;
	const float REGEN_HP 			= 1.66;
	
	const int 	REGEN_SHOCK_TIME 	= 30;
	const float REGEN_SHOCK 		= 2;
	const float STAMINA_REGEN		= 2;

	override void Init()
	{
		m_TrackActivatedTime 	= true;
		m_IsPersistent 			= true;
		m_ID 					= MedModifiers.AI2_Military;
		m_TickIntervalInactive 	= DEFAULT_TICK_TIME_INACTIVE;
		m_TickIntervalActive 	= DEFAULT_TICK_TIME_ACTIVE;
	}

	override bool ActivateCondition(PlayerBase player)
	{
		return false;
	}

	override bool DeactivateCondition(PlayerBase player)
	{
		return ( GetAttachedTime() > LIFETIME );
	}

	override void OnReconnect(PlayerBase player)
	{
		OnActivate(player);
	}
	
	override void OnActivate(PlayerBase player)
	{
		if( player.GetNotifiersManager() )
			player.GetNotifiersManager().ActivateByType(eNotifiers.NTF_PILLS);
	}
	
	override void OnDeactivate(PlayerBase player)
	{
		if( player.GetNotifiersManager() )
			player.GetNotifiersManager().DeactivateByType(eNotifiers.NTF_PILLS);
	}

	override void OnTick(PlayerBase player, float deltaT)
	{		
		if( GetAttachedTime() <= REGEN_HP_TIME )
		{
			player.AddHealth("", "Health",  REGEN_HP * deltaT);
			player.AddHealth("", "Blood",  REGEN_HP * deltaT * 5);
		}
		
		if( GetAttachedTime() <= REGEN_SHOCK_TIME )
		{
			player.AddHealth("", "Shock", REGEN_SHOCK * deltaT);
			float m_Stamina = player.GetStatStamina().Get();			
			player.GetStaminaHandler().SetStamina( m_Stamina + STAMINA_REGEN );	
		}	
	}
	
};