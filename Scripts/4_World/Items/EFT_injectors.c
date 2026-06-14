class DIV_Inj_Base extends ItemBase
{
	override void SetActions()
	{
		super.SetActions();
		
		AddAction(ActionDIVInjectorSelf);
		AddAction(ActionDIVInjectorTarget);
	}
};