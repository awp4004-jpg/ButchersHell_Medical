class Perform_Bullet_Surgery_TargetCB : ActionContinuousBaseCB
{
	override void CreateActionComponent()
	{
		m_ActionData.m_ActionComponent = new CAContinuousRepeat(2); // Increased time for realism
	}
}

class Perform_Bullet_Surgery_Target : ActionContinuousBase
{
	void Perform_Bullet_Surgery_Target()
	{
		m_CallbackClass 	= Perform_Bullet_Surgery_TargetCB;
		m_CommandUID 		= DayZPlayerConstants.CMD_ACTIONFB_BANDAGETARGET;
		m_FullBody 			= true;
		m_StanceMask 		= DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;

		m_Text = "Perform surgery";
	}
	
	override void CreateConditionComponents()  
	{	
		m_ConditionItem 	= new CCINonRuined();
		m_ConditionTarget 	= new CCTMan(UAMaxDistances.DEFAULT);
	}

	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		PlayerBase otherPlayer = PlayerBase.Cast(target.GetObject());
		if (otherPlayer)
			return otherPlayer.HasBulletWoundsRemoved();
		
		return false;
	}

	override void OnFinishProgressServer(ActionData action_data)
	{	
		PlayerBase target = PlayerBase.Cast(action_data.m_Target.GetObject());
		if (action_data.m_MainItem && target)
		{
			// 30% chance of failure
			if (Math.RandomFloat01() < 0.4)
			{
				//target.MessageStatus("The surgery failed! The wound started bleeding.");
				return;
			}

			target.RemoveBulletwoundRemoved();
			target.SetBulletWoundsStiched();
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
	
	override bool CanTargetBeInVehicle()
	{
		return true;
	}
}
