class DIV_med_Cat_Base extends ItemBase
{
	override bool HasFlammableMaterial()
	{
		return true;
	}
	
	override void SetActions()
	{
		super.SetActions();
		
		AddAction(ActionCatsDIVTarget);
		AddAction(ActionCatsDIVSelf);
	}
	
}