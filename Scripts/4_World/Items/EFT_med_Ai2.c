class DIV_med_ai2_base extends ItemBase
{
	//================================================================
	// AI2 ACTION
	//================================================================
	override bool HasFlammableMaterial()
	{
		return true;
	}
	
	override void SetActions()
	{
		super.SetActions();
		
		AddAction(ActionAi2DIVTarget);
		AddAction(ActionAi2DIVSelf);
	}
}