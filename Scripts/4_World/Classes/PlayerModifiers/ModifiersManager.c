modded class ModifiersManager
{
	override void Init()
	{
		super.Init();
		AddModifier(new mAI2_Basic);
		AddModifier(new mAI2_Military);
		AddModifier(new mAI2_Scientific);
		//DIV
        AddModifier(new DIVPropitalMdfr);
        AddModifier(new DIVGoldstarMdfr);
        AddModifier(new DIVObdolbosMdfr);
        AddModifier(new DIVCombatStimulatorSJ1);
        AddModifier(new DIVCombatStimulatorSJ6);
        AddModifier(new DIVCombatStimulatorZagustin);
        AddModifier(new DIVCombatStimulatorETG);
        AddModifier(new DIVCombatStimulatorMULE);
        AddModifier(new DIVObdolbos2Mdfr);
        AddModifier(new DIVPerfotorMdfr);
        AddModifier(new DIVXTG12Mdfr);

        AddModifier(new HealingAFAKMdfr);
        AddModifier(new HealingAi2Mdfr);
        AddModifier(new HealingGrizlyMdfr);
        AddModifier(new HealingIFAKMdfr);
        AddModifier(new HealingSalewaMdfr);
	}
}