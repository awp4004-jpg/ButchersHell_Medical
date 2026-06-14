class ActionSplintDIVSelfCB : ActionContinuousBaseCB
{
	override void CreateActionComponent()
	{
		float Effectivity_Time = 3.0;
		m_ActionData.m_ActionComponent = new CAContinuousTime(Effectivity_Time);
	}
};

class ActionSplintDIVSelf: ActionSplintDIVBase
{	
	void ActionSplintDIVSelf()
	{
		m_CallbackClass = ActionSplintDIVSelfCB;
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_BANDAGE;
		m_FullBody = true;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_CROUCH;
		m_SpecialtyWeight = UASoftSkillsWeight.PRECISE_LOW;
	}

	override void CreateConditionComponents()  
	{		
		m_ConditionItem = new CCINonRuined;
		m_ConditionTarget = new CCTSelf;
	}

	override bool HasTarget()
	{
		return false;
	}
		
	override string GetText()
	{
		return "#treat_wound";
	}
	
	override void OnFinishProgressServer( ActionData action_data )
	{	
		PlayerBase target = PlayerBase.Cast(action_data.m_Player);
		
		if(action_data.m_MainItem && target)
		{
			ApplySplint( action_data.m_MainItem, target );
			action_data.m_Player.GetSoftSkillsManager().AddSpecialty( m_SpecialtyWeight );
			action_data.m_Player.m_AgentPool.SetAgentCount(eAgents.WOUND_AGENT, 0);
		}
	}
	
};
