class Perform_Bandage_Bullet_SelfCB : ActionContinuousBaseCB
{
	override void CreateActionComponent()
	{
		m_ActionData.m_ActionComponent = new CAContinuousRepeat(2); // Increased time for realism
	}
}

class Perform_Bandage_Bullet_Self : ActionContinuousBase
{	
	void Perform_Bandage_Bullet_Self()
	{
		m_CallbackClass 	= Perform_Bandage_Bullet_SelfCB;
		m_CommandUID 		= DayZPlayerConstants.CMD_ACTIONFB_BANDAGE;
		m_FullBody 			= true;
		m_StanceMask 		= DayZPlayerConstants.STANCEMASK_CROUCH;

		m_Text = "Bandage bullet wound";
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
		return player.HasBulletWounds();
	}
	
	override void OnFinishProgressServer(ActionData action_data)
	{	
		PlayerBase target = PlayerBase.Cast(action_data.m_Player);
		if (action_data.m_MainItem && target)
		{
            target.RemoveBulletWounds();
			target.SetBulletWoundsBandaged();
			//target.MessageStatus("You bandaged a bullet wound.");

			// Consume item properly
			if (action_data.m_MainItem.GetQuantity() > 1)
				action_data.m_MainItem.AddQuantity(-1);
			else
				action_data.m_MainItem.Delete();
		}
	}

	override void OnFinishProgressClient(ActionData action_data)
	{

	}
}
