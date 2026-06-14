class Perform_Bandage_Bullet_TargetCB : ActionContinuousBaseCB
{
	override void CreateActionComponent()
	{
		m_ActionData.m_ActionComponent = new CAContinuousRepeat(2);
	}
}

class Perform_Bandage_Bullet_Target : ActionContinuousBase
{	
	void Perform_Bandage_Bullet_Target()
	{
		m_CallbackClass 	= Perform_Bandage_Bullet_TargetCB;
		m_CommandUID 		= DayZPlayerConstants.CMD_ACTIONFB_BANDAGETARGET;
		m_FullBody 			= true;
		m_StanceMask 		= DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;

		m_Text = "Bandage bullet wound";
	}

	override void CreateConditionComponents()  
	{		
		m_ConditionItem 	= new CCINonRuined();
		m_ConditionTarget 	= new CCTMan(UAMaxDistances.DEFAULT);
	}

	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		PlayerBase otherPlayer = PlayerBase.Cast(target.GetObject());
		if (!otherPlayer || otherPlayer == player)
			return false;
		
		return otherPlayer.HasBulletWounds();
	}
	
	override void OnFinishProgressServer(ActionData action_data)
	{	
		PlayerBase targetPlayer = PlayerBase.Cast(action_data.m_Target.GetObject());
		if (action_data.m_MainItem && targetPlayer)
		{
			targetPlayer.RemoveBulletWounds();
			targetPlayer.SetBulletWoundsBandaged();

			if (action_data.m_MainItem.GetQuantity() > 1)
				action_data.m_MainItem.AddQuantity(-1);
			else
				action_data.m_MainItem.Delete();
		}
	}
}