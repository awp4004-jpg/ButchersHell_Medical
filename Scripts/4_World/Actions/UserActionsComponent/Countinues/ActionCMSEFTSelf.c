class ActionCMSDIVSelfCB : ActionContinuousBaseCB
{
	override void CreateActionComponent()
	{
		m_ActionData.m_ActionComponent = new CAContinuousRepeat(2);
	}
};

class ActionCMSDIVSelf : ActionContinuousBase
{
	void ActionCMSDIVSelf()
	{
		m_CallbackClass 	= ActionCMSDIVSelfCB;
		m_CommandUID 		= DayZPlayerConstants.CMD_ACTIONFB_BANDAGE;
		m_FullBody 			= true;
		m_StanceMask 		= DayZPlayerConstants.STANCEMASK_CROUCH;
		m_Text = "Perform surgery";
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
		return player.HasBulletWoundsRemoved() || player.HasDeepWoundsBandaged() || player.HasDeepWounds();
	}

	override void OnFinishProgressServer(ActionData action_data)
	{
		PlayerBase player = PlayerBase.Cast(action_data.m_Player);
		ItemBase item     = action_data.m_MainItem;

		if (player && item)
		{
			// Stitch one wound (Bullet)
			if (player.HasBulletWoundsRemoved())
			{
				player.RemoveBulletwoundRemoved();
				player.SetBulletWoundsStiched();
			}
			// Or stitch one Deep Wound (if no bullet wounds removed)
			else if (player.HasDeepWoundsBandaged())
			{
				player.RemoveDeepWoundBandaged();
				player.SetDeepWoundsStiched();
			}
			else if (player.HasDeepWounds())
			{
				player.RemoveDeepWound();
				player.SetDeepWoundsStiched();
			}
			// Consume item
			if (item.HasQuantity())
				item.AddQuantity(-1, true);
			else
				item.Delete();
		}
	}
}