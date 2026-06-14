class DIV_med_IFAK_base extends ItemBase
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
		
		AddAction(ActionIFAKSDIVTarget);
		AddAction(ActionIFAKSDIVSelf);
	}
}