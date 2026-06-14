class DIV_Med_ActionInjectSelfCB: ActionContinuousBaseCB
{
	override void CreateActionComponent()
	{
		m_ActionData.m_ActionComponent = new CAContinuousTime(1.60);
	}
}

class ActionDIVInjectorSelf: ActionContinuousBase
{
	void ActionDIVInjectorSelf()
	{
		m_CallbackClass = DIV_Med_ActionInjectSelfCB;
		m_FullBody      = false;
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_EAT;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT| DayZPlayerConstants.STANCEMASK_CROUCH| DayZPlayerConstants.STANCEMASK_PRONE;
		m_SpecialtyWeight = UASoftSkillsWeight.PRECISE_MEDIUM;
		m_Text = "#inject";
	}

	override void CreateConditionComponents()
	{
		m_ConditionItem   = new CCINonRuined;
		m_ConditionTarget = new CCTSelf;
	}

	override bool HasTarget() { return false; }

	override void OnFinishProgressServer(ActionData action_data)
	{
		if (action_data.m_MainItem)
		{
			ApplyModifiers(action_data);
			action_data.m_MainItem.Delete();
		}
	}

	override void OnFinishProgressClient(ActionData action_data)
	{
		if (action_data.m_MainItem)
			action_data.m_MainItem.DeleteOnClient();
	}

	override void ApplyModifiers( ActionData action_data )
	{
		action_data.m_MainItem.OnApply(action_data.m_Player);		
	}
}