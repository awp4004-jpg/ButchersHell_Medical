class DIV_med_Surv_base extends ItemBase
{
	//================================================================
	// Surv ACTION
	//================================================================
	override bool HasFlammableMaterial()
	{
		return true;
	}
	
	override void SetActions()
	{
		super.SetActions();
		
		AddAction(ActionSurvivalDIVTarget);
		AddAction(ActionSurvivalDIVSelf);
		AddAction(Perform_BulletRemove_Self_Forceps);
		AddAction(Perform_BulletRemove_Target_Forceps);
	}
}