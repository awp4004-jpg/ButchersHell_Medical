class DIV_med_GoldStar: Edible_Base
{
	override void OnConsume(float amount, PlayerBase consumer)
	{
		if( consumer.GetModifiersManager().IsModifierActive(new_DIV_eModifiers.MDF_DIV_GOLDSTAR ) )
		{
			consumer.GetModifiersManager().DeactivateModifier( new_DIV_eModifiers.MDF_DIV_GOLDSTAR );
		}
		consumer.GetModifiersManager().ActivateModifier( new_DIV_eModifiers.MDF_DIV_GOLDSTAR );
		consumer.GetStatWater().Add(-500);
		consumer.GetStatEnergy().Add(-500);
	}
	
	override void SetActions()
	{
		super.SetActions();
		
		AddAction(ActionForceConsumeSingle);
		AddAction(ActionConsumeSingle);
	}
}