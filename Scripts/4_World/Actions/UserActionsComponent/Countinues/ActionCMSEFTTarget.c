class ActionCMSDIVTargetCB : ActionContinuousBaseCB
{
	override void CreateActionComponent()
	{
		m_ActionData.m_ActionComponent = new CAContinuousRepeat(2);
	}
};

class ActionCMSDIVTarget : ActionContinuousBase
{
	void ActionCMSDIVTarget()
	{
		m_CallbackClass 	= ActionCMSDIVTargetCB;
		m_SpecialtyWeight 	= UASoftSkillsWeight.PRECISE_LOW;
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
		PlayerBase other_player = PlayerBase.Cast(target.GetObject());
		if (!other_player || other_player == player)
			return false;

		return other_player.HasBulletWoundsRemoved() || other_player.HasDeepWoundsBandaged() || other_player.HasDeepWounds();
	}

	override void OnFinishProgressServer(ActionData action_data)
	{
		PlayerBase targetPlayer = PlayerBase.Cast(action_data.m_Target.GetObject());
		ItemBase item = action_data.m_MainItem;

		if (targetPlayer && item)
		{
			if (targetPlayer.HasBulletWoundsRemoved())
			{
				targetPlayer.RemoveBulletwoundRemoved();
				targetPlayer.SetBulletWoundsStiched();
			}
			else if (targetPlayer.HasDeepWoundsBandaged())
			{
				targetPlayer.RemoveDeepWoundBandaged();
				targetPlayer.SetDeepWoundsStiched();
			}
			else if (targetPlayer.HasDeepWounds())
			{
				targetPlayer.RemoveDeepWound();
				targetPlayer.SetDeepWoundsStiched();
			}
			
			if (item.HasQuantity())
				item.AddQuantity(-1, true);
			else
				item.Delete();
		}
	}
}