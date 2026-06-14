modded class ActionConstructor
{
	override void RegisterActions(TTypenameArray actions)
	{
		super.RegisterActions(actions);
		
		actions.Insert(ActionUseTargetAI2_Basic);
		actions.Insert(ActionUseAI2_Basic);

		actions.Insert(ActionUseTargetAI2_Military);
		actions.Insert(ActionUseAI2_Military);

		actions.Insert(ActionUseTargetAI2_Scientific);
		actions.Insert(ActionUseAI2_Scientific);

        actions.Insert(Perform_Surgery_Self);
        actions.Insert(Perform_Surgery_Target);
		
        actions.Insert(Perform_BulletRemove_Self);
        actions.Insert(Perform_BulletRemove_Target);

		actions.Insert(Perform_BulletRemove_Self_Forceps);
		actions.Insert(Perform_BulletRemove_Target_Forceps);

		actions.Insert(Perform_Bandage_Bullet_Self);
		actions.Insert(Perform_Bandage_Bullet_Target);

		actions.Insert(Perform_Bandage_Deep_Self);
		actions.Insert(Perform_Bandage_Deep_Target);
		
		actions.Insert(Perform_Bullet_Surgery_Self);
		actions.Insert(Perform_Bullet_Surgery_Target);
		//DIV
		actions.Insert(ActionAFAKDIVTarget);
		actions.Insert(ActionAFAKDIVSelf);	
		actions.Insert(ActionIFAKSDIVTarget);
		actions.Insert(ActionIFAKSDIVSelf);	
		actions.Insert(ActionSalewaDIVTarget);
		actions.Insert(ActionSalewaDIVSelf);	
		actions.Insert(ActionDIVInjectorSelf);	
		actions.Insert(ActionDIVInjectorTarget);
		actions.Insert(ActionSplintDIVTarget);
		actions.Insert(ActionSplintDIVSelf);	
		actions.Insert(ActionCALOKsDIVTarget);
		actions.Insert(ActionCALOKsDIVSelf);		
		actions.Insert(ActionEsmarchsDIVTarget);
		actions.Insert(ActionEsmarchsDIVSelf);		
		actions.Insert(ActionCatsDIVTarget);
		actions.Insert(ActionCatsDIVSelf);			
		actions.Insert(ActionGrizlyDIVTarget);
		actions.Insert(ActionGrizlyDIVSelf);
		actions.Insert(ActionAi2DIVTarget);
		actions.Insert(ActionAi2DIVSelf);	
		actions.Insert(ActionSurvivalDIVTarget);
		actions.Insert(ActionSurvivalDIVSelf);	
		actions.Insert(ActionCMSDIVTarget);
		actions.Insert(ActionCMSDIVSelf);	
	}
}