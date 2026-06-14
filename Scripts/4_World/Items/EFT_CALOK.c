class DIV_med_CALOK_Base extends ItemBase
{
	override bool HasFlammableMaterial()
	{
		return true;
	}
	
	override void SetActions()
	{
		super.SetActions();
		
		AddAction(ActionCALOKsDIVTarget);
		AddAction(ActionCALOKsDIVSelf);
	}
	
}