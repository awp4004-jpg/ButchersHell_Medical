class Perform_Surgery_SelfCB : ActionContinuousBaseCB
{
	override void CreateActionComponent()
	{
		m_ActionData.m_ActionComponent = new CAContinuousRepeat(2); // Increased time for realism
	}
}

class Perform_Surgery_Self : ActionContinuousBase
{	
	void Perform_Surgery_Self()
	{
		m_CallbackClass 	= Perform_Surgery_SelfCB;
		m_CommandUID 		= DayZPlayerConstants.CMD_ACTIONFB_BANDAGE;
		m_FullBody 			= true;
		m_StanceMask 		= DayZPlayerConstants.STANCEMASK_CROUCH;

		m_Text = "Perform surgery on myself";
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
		return player.HasDeepWounds() || player.HasDeepWoundsBandaged();
	}
	
	override void OnFinishProgressServer(ActionData action_data)
	{	
		PlayerBase target = PlayerBase.Cast(action_data.m_Player);
		if (action_data.m_MainItem && target)
		{
			// 30% chance of failure
			if (Math.RandomFloat01() < 0.2)
			{
				//target.MessageStatus("The surgery failed! The wound started bleeding.");
				return;
			}

			if (target.HasDeepWounds())
			{
				target.RemoveDeepWound();
			}
			else if (target.HasDeepWoundsBandaged())
			{
				target.RemoveDeepWoundBandaged();
			}
			target.SetDeepWoundsStiched();
			//target.MessageStatus("Surgery completed, but the pain is intense...");

			// Ensure item is consumed correctly
			if (action_data.m_MainItem.GetQuantity() > 10)
				action_data.m_MainItem.AddQuantity(-10);
			else
				action_data.m_MainItem.Delete();
		}
	}

	override void OnFinishProgressClient(ActionData action_data)
	{

	}
}
