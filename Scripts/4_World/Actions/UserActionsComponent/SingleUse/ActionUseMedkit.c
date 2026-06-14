class ActionUseAI2_Basic: ActionInjectSelf
{	
	override void ApplyModifiers( ActionData action_data )
	{
		action_data.m_MainItem.OnApply(action_data.m_Player);
	}
	
	override string GetText()
	{
		return "Use AI-2 on yourself";
	}

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{	
		if( player.GetModifiersManager().IsModifierActive(MedModifiers.AI2_Basic ) || player.GetModifiersManager().IsModifierActive(MedModifiers.AI2_Military ) || player.GetModifiersManager().IsModifierActive(MedModifiers.AI2_Scientific ))
		{
			return false;
		}

		return super.ActionCondition( player, target, item );
	}
}

class ActionUseAI2_Military: ActionInjectSelf
{	
	override void ApplyModifiers( ActionData action_data )
	{
		action_data.m_MainItem.OnApply(action_data.m_Player);
	}
	
	override string GetText()
	{
		return "Use AI-2 on yourself";
	}

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{	
		if( player.GetModifiersManager().IsModifierActive(MedModifiers.AI2_Basic ) || player.GetModifiersManager().IsModifierActive(MedModifiers.AI2_Military ) || player.GetModifiersManager().IsModifierActive(MedModifiers.AI2_Scientific ))
		{
			return false;
		}

		return super.ActionCondition( player, target, item );
	}
}

class ActionUseAI2_Scientific: ActionInjectSelf
{	
	override void ApplyModifiers( ActionData action_data )
	{
		action_data.m_MainItem.OnApply(action_data.m_Player);
	}
	
	override string GetText()
	{
		return "Use AI-2 on yourself";
	}

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{	
		if( player.GetModifiersManager().IsModifierActive(MedModifiers.AI2_Basic ) || player.GetModifiersManager().IsModifierActive(MedModifiers.AI2_Military ) || player.GetModifiersManager().IsModifierActive(MedModifiers.AI2_Scientific ))
		{
			return false;
		}

		return super.ActionCondition( player, target, item );
	}
}



//////////////////// APPLY ON TARGETS

class ActionUseTargetAI2_Basic: ActionInjectTarget
{	
	override void ApplyModifiers( ActionData action_data )
	{
		action_data.m_MainItem.OnApply(PlayerBase.Cast(action_data.m_Target.GetObject()));
	}
	
	override string GetText()
	{
		return "Use AI-2 on other";
	}

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{	
		PlayerBase ptarget = PlayerBase.Cast( target.GetObject() );

		if( ptarget && ptarget.GetModifiersManager().IsModifierActive(MedModifiers.AI2_Basic ) )
		{
			return false;
		}

		return super.ActionCondition( player, target, item );
	}
}



//////////////////// APPLY ON TARGETS

class ActionUseTargetAI2_Military: ActionInjectTarget
{
	override void ApplyModifiers( ActionData action_data )
	{
		action_data.m_MainItem.OnApply(PlayerBase.Cast(action_data.m_Target.GetObject()));
	}
	
	override string GetText()
	{
		return "Use AI-2 on other";
	}

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{	
		PlayerBase ptarget = PlayerBase.Cast( target.GetObject() );

		if( ptarget && ptarget.GetModifiersManager().IsModifierActive(MedModifiers.AI2_Military ) )
		{
			return false;
		}

		return super.ActionCondition( player, target, item );
	}
}

class ActionUseTargetAI2_Scientific: ActionInjectTarget
{
	override void ApplyModifiers( ActionData action_data )
	{
		action_data.m_MainItem.OnApply(PlayerBase.Cast(action_data.m_Target.GetObject()));
	}
	
	override string GetText()
	{
		return "Use AI-2 on other";
	}

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{	
		PlayerBase ptarget = PlayerBase.Cast( target.GetObject() );

		if( ptarget && ptarget.GetModifiersManager().IsModifierActive(MedModifiers.AI2_Scientific ) )
		{
			return false;
		}

		return super.ActionCondition( player, target, item );
	}
}

