class DIV_med_Salewa_base extends ItemBase
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
		
		AddAction(ActionSalewaDIVTarget);
		AddAction(ActionSalewaDIVSelf);
	}
}