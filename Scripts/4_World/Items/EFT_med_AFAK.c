class DIV_med_AFAK_base extends ItemBase
{
	//================================================================
	// AFAK ACTION
	//================================================================
	override bool HasFlammableMaterial()
	{
		return true;
	}
	
	override void SetActions()
	{
		super.SetActions();
		
		AddAction(ActionAFAKDIVTarget);
		AddAction(ActionAFAKDIVSelf);
	}
}