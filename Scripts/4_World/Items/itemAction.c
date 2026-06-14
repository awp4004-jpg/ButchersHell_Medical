modded class Pliers extends ToolBase
{
	override void SetActions()
	{
		super.SetActions();
		
		AddAction(Perform_BulletRemove_Self);
		AddAction(Perform_BulletRemove_Target);
	}
}
modded class SewingKit: Inventory_Base
{
 	override void SetActions()
	{
		super.SetActions();
		
		AddAction(Perform_Surgery_Self);
		AddAction(Perform_Surgery_Target);
		AddAction(Perform_Bullet_Surgery_Self);
		AddAction(Perform_Bullet_Surgery_Target);
		RemoveAction(ActionSewSelf);
		RemoveAction(ActionSewTarget);
	}   
}
modded class BandageDressing extends ItemBase
{
 	override void SetActions()
	{
		super.SetActions();
		
		AddAction(Perform_Bandage_Bullet_Self);
		AddAction(Perform_Bandage_Bullet_Target);
		AddAction(Perform_Bandage_Deep_Self);
		AddAction(Perform_Bandage_Deep_Target);
	}
}
class DIV_med_Forceps extends Inventory_Base
{
 	override void SetActions()
	{
		super.SetActions();

		AddAction(Perform_BulletRemove_Self_Forceps);
		AddAction(Perform_BulletRemove_Target_Forceps);
	}	
}