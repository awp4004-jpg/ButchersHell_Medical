class ActionAFAKDIVSelfCB : ActionContinuousBaseCB
{
	override void CreateActionComponent()
	{
		m_ActionData.m_ActionComponent = new CAContinuousTime(7.0);
	}
};

class ActionAFAKDIVSelf : ActionContinuousBase
{
	void ActionAFAKDIVSelf()
	{
		m_CallbackClass 	= ActionAFAKDIVSelfCB;
		m_FullBody 			= false;
		m_CommandUID 		= DayZPlayerConstants.CMD_ACTIONMOD_EAT;
		m_StanceMask 		= DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH | DayZPlayerConstants.STANCEMASK_PRONE;
		m_Text 				= "#treat_wound";
	}

	override void CreateConditionComponents()  
	{		
		m_ConditionItem 	= new CCINonRuined();
		m_ConditionTarget 	= new CCTSelf();
	}

	override bool HasTarget()
	{
		return false;
	}

	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		// Block if ANY healing modifier is already active
		if (player.GetModifiersManager().IsModifierActive(new_DIV_eModifiers.MDF_HEALING_AFAK) || player.GetModifiersManager().IsModifierActive(new_DIV_eModifiers.MDF_HEALING_IFAK) || player.GetModifiersManager().IsModifierActive(new_DIV_eModifiers.MDF_HEALING_SALEWA) || player.GetModifiersManager().IsModifierActive(new_DIV_eModifiers.MDF_HEALING_GRIZLY) || player.GetModifiersManager().IsModifierActive(new_DIV_eModifiers.MDF_HEALING_AI2))
		{
			return false;
		}

		return player.GetHealth("GlobalHealth", "Health") < 100;
	}

	override void OnFinishProgressServer(ActionData action_data)
	{
		PlayerBase player = PlayerBase.Cast(action_data.m_Player);
		ItemBase item     = action_data.m_MainItem;

		if (player && item)
		{
			// Activate healing over time
			if (!player.GetModifiersManager().IsModifierActive(new_DIV_eModifiers.MDF_HEALING_AFAK))
			{
				player.GetModifiersManager().ActivateModifier(new_DIV_eModifiers.MDF_HEALING_AFAK);
			}

			// Consume item
			if (item.HasQuantity())
				item.AddQuantity(-1, true);
			else
				item.Delete();
		}
	}
}