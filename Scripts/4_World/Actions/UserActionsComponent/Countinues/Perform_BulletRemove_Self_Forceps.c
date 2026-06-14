class Perform_BulletRemove_Self_ForcepsCB : ActionContinuousBaseCB
{
	override void CreateActionComponent()
	{
		m_ActionData.m_ActionComponent = new CAContinuousRepeat(5); // Increased time for realism
	}
}

class Perform_BulletRemove_Self_Forceps : ActionContinuousBase
{	
	void Perform_BulletRemove_Self_Forceps()
	{
		m_CallbackClass 	= Perform_BulletRemove_Self_ForcepsCB;
		m_CommandUID 		= DayZPlayerConstants.CMD_ACTIONFB_BANDAGE;
		m_FullBody 			= true;
		m_StanceMask 		= DayZPlayerConstants.STANCEMASK_CROUCH;

		m_Text = "Remove bullet";
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
		return player.HasBulletWoundsBandaged() || player.HasBulletWounds();
	}
	
	override void OnFinishProgressServer(ActionData action_data)
	{	
		PlayerBase target = PlayerBase.Cast(action_data.m_Player);
		if (action_data.m_MainItem && target)
		{
			// Successfully removed the bullet
			if (target.HasBulletWounds())
			{
				target.RemoveBulletWounds();
			}
			else if (target.HasBulletWoundsBandaged())
			{
				target.RemoveBulletWoundBandaged();
			}
			target.SetBulletWoundsRemoved();
			//target.MessageStatus("You removed the bullet.");

			action_data.m_MainItem.DecreaseHealth("", "", 15);
			/* Consume item properly
			if (action_data.m_MainItem.GetQuantity() > 1)
				action_data.m_MainItem.AddQuantity(-1);
			else
				action_data.m_MainItem.Delete();*/
		}
	}

	override void OnFinishProgressClient(ActionData action_data)
	{

	}
}
