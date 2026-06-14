class ActionSplintDIVTargetCB : ActionContinuousBaseCB
{
	override void CreateActionComponent()
	{
		float Effectivity_Time = 3.0;
		m_ActionData.m_ActionComponent = new CAContinuousTime(Effectivity_Time);
	}
};

class ActionSplintDIVTarget: ActionSplintDIVBase
{
	void ActionSplintDIVTarget()
	{
		m_CallbackClass = ActionSplintDIVTargetCB;
		m_SpecialtyWeight = UASoftSkillsWeight.PRECISE_LOW;
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_BANDAGETARGET;
		m_FullBody = true;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;
	}
	
	override void CreateConditionComponents()  
	{	
		m_ConditionItem = new CCINonRuined;
		m_ConditionTarget = new CCTMan(UAMaxDistances.DEFAULT);
	}
		
	override string GetText()
	{
		return "#treat_persons_wound";
	}
	
	override void OnFinishProgressServer( ActionData action_data )
	{	
		PlayerBase target = PlayerBase.Cast(action_data.m_Target.GetObject());
		if(action_data.m_MainItem && target)
		{
			ApplySplint( action_data.m_MainItem, target );
			action_data.m_Player.GetSoftSkillsManager().AddSpecialty( m_SpecialtyWeight );
			action_data.m_Player.m_AgentPool.SetAgentCount(eAgents.WOUND_AGENT, 0);
		}
	}
};
