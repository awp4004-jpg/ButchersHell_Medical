class DIV_med_Splint_base extends ItemBase
{
	//================================================================
	// Splint ACTION
	//================================================================
	override bool HasFlammableMaterial()
	{
		return true;
	}
	
	override void SetActions()
	{
		super.SetActions();
		
		AddAction(ActionSplintDIVTarget);
		AddAction(ActionSplintDIVSelf);
	}
}