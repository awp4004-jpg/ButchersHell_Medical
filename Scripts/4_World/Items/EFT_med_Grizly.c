class DIV_med_Grizly_base extends ItemBase
{
	//================================================================
	// Grizly ACTION
	//================================================================
	override bool HasFlammableMaterial()
	{
		return true;
	}
	
	override void SetActions()
	{
		super.SetActions();
		
		AddAction(ActionGrizlyDIVTarget);
		AddAction(ActionGrizlyDIVSelf);
	}
}