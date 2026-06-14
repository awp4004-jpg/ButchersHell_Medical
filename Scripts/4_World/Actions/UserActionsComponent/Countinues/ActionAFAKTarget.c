class ActionAFAKDIVTargetCB : ActionContinuousBaseCB
{
	override void CreateActionComponent()
	{
		m_ActionData.m_ActionComponent = new CAContinuousTime(7.0);
	}
};

class ActionAFAKDIVTarget : ActionContinuousBase
{
	void ActionAFAKDIVTarget()
	{
		m_CallbackClass 	= ActionAFAKDIVTargetCB;
		m_SpecialtyWeight 	= UASoftSkillsWeight.PRECISE_LOW;
		m_CommandUID 		= DayZPlayerConstants.CMD_ACTIONFB_BANDAGETARGET;
		m_FullBody 			= true;
		m_StanceMask 		= DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;
		m_Text 				= "#treat_persons_wound";
	}

	override void CreateConditionComponents()  
	{	
		m_ConditionItem 	= new CCINonRuined();
		m_ConditionTarget 	= new CCTMan(UAMaxDistances.DEFAULT);
	}

	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		PlayerBase other_player = PlayerBase.Cast(target.GetObject());
		
		if (!other_player || other_player == player)
			return false;

		// Block if ANY healing modifier is already active
		if (player.GetModifiersManager().IsModifierActive(new_DIV_eModifiers.MDF_HEALING_AFAK) || player.GetModifiersManager().IsModifierActive(new_DIV_eModifiers.MDF_HEALING_IFAK) || player.GetModifiersManager().IsModifierActive(new_DIV_eModifiers.MDF_HEALING_SALEWA) || player.GetModifiersManager().IsModifierActive(new_DIV_eModifiers.MDF_HEALING_GRIZLY) || player.GetModifiersManager().IsModifierActive(new_DIV_eModifiers.MDF_HEALING_AI2))
		{
			return false;
		}

		return other_player.GetHealth("GlobalHealth", "Health") < 100;
	}

	override void OnFinishProgressServer(ActionData action_data)
	{
		PlayerBase target = PlayerBase.Cast(action_data.m_Target.GetObject());
		ItemBase item     = action_data.m_MainItem;

		if (target && item)
		{
			// Activate healing over time
			if (!target.GetModifiersManager().IsModifierActive(new_DIV_eModifiers.MDF_HEALING_AFAK))
			{
				target.GetModifiersManager().ActivateModifier(new_DIV_eModifiers.MDF_HEALING_AFAK);
			}

			// Consume item
			if (item.HasQuantity())
				item.AddQuantity(-1, true);
			else
				item.Delete();
		}
	}
}