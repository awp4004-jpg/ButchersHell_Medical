class Perform_BulletRemove_TargetCB : ActionContinuousBaseCB
{
	override void CreateActionComponent()
	{
		m_ActionData.m_ActionComponent = new CAContinuousRepeat(10); // Increased time for realism
	}
}

class Perform_BulletRemove_Target : ActionContinuousBase
{
	void Perform_BulletRemove_Target()
	{
		m_CallbackClass 	= Perform_BulletRemove_TargetCB;
		m_CommandUID 		= DayZPlayerConstants.CMD_ACTIONFB_BANDAGETARGET;
		m_FullBody 			= true;
		m_StanceMask 		= DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;

		m_Text = "Remove bullet";
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
			return otherPlayer.HasBulletWoundsBandaged() || otherPlayer.HasBulletWounds();
		
		return false;
	}

	override void OnFinishProgressServer(ActionData action_data)
	{	
		// Get the TARGET player, not the player doing the action
		PlayerBase targetPlayer = PlayerBase.Cast(action_data.m_Target.GetObject());
		
		if (action_data.m_MainItem && targetPlayer)
		{
			// 30% chance of failure (you can adjust this)
			if (Math.RandomFloat01() < 0.3) 
			{
				//targetPlayer.MessageStatus("The surgery failed!");
				return;
			}

			// Successfully remove bullet from the TARGET
			if (targetPlayer.HasBulletWounds())
			{
				targetPlayer.RemoveBulletWounds();
			}
			else if (targetPlayer.HasBulletWoundsBandaged())
			{
				targetPlayer.RemoveBulletWoundBandaged();
			}
			
			targetPlayer.SetBulletWoundsRemoved();
			//targetPlayer.MessageStatus("Bullet was removed.");

			// Damage the surgical tool
			action_data.m_MainItem.DecreaseHealth("", "", 15);
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
