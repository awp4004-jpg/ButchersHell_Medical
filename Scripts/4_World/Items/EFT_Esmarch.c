class DIV_med_Esmarch_Base extends ItemBase
{
	override bool HasFlammableMaterial()
	{
		return true;
	}
	
	override void SetActions()
	{
		super.SetActions();
		
		AddAction(ActionEsmarchsDIVTarget);
		AddAction(ActionEsmarchsDIVSelf);
	}
	
}