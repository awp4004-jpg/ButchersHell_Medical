class DIV_med_CMS_base extends ItemBase
{
	//================================================================
	// CMS ACTION
	//================================================================
	override bool HasFlammableMaterial()
	{
		return true;
	}
	
	override void SetActions()
	{
		super.SetActions();
		
		AddAction(ActionCMSDIVTarget);
		AddAction(ActionCMSDIVSelf);
		AddAction(Perform_BulletRemove_Self_Forceps);
		AddAction(Perform_BulletRemove_Target_Forceps);
	}
}