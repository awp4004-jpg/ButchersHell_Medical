class TMB_AI2_Basic : ItemBase
{
    override void SetActions()
	{
		super.SetActions();
		AddAction(ActionUseTargetAI2_Basic);
		AddAction(ActionUseAI2_Basic);
	}

	override void OnApply(PlayerBase player)
	{
		if( !player.GetModifiersManager().IsModifierActive(MedModifiers.AI2_Basic ) )
		{
			player.GetModifiersManager().ActivateModifier(MedModifiers.AI2_Basic );
		}
		else
		{
			player.GetStaminaHandler().SetStamina(0);
		}
	}
}

class TMB_AI2_Military : ItemBase
{
	override void SetActions()
	{
		super.SetActions();
		AddAction(ActionUseTargetAI2_Military);
		AddAction(ActionUseAI2_Military);
	}

	override void OnApply(PlayerBase player)
	{
		if( !player.GetModifiersManager().IsModifierActive(MedModifiers.AI2_Military ) )
		{
			player.GetModifiersManager().ActivateModifier(MedModifiers.AI2_Military );
		}
		else
		{
			player.GetStaminaHandler().SetStamina(0);
		}
	}
}

class TMB_AI2_Scientific : ItemBase
{
	override void SetActions()
	{
		super.SetActions();
		AddAction(ActionUseTargetAI2_Scientific);
		AddAction(ActionUseAI2_Scientific);
	}

	override void OnApply(PlayerBase player)
	{
		if( !player.GetModifiersManager().IsModifierActive(MedModifiers.AI2_Scientific ) )
		{
			player.GetModifiersManager().ActivateModifier(MedModifiers.AI2_Scientific );
		}
		else
		{
			player.GetStaminaHandler().SetStamina(0);
		}
	}
}
