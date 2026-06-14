modded class Morphine
{
	override void OnApply(PlayerBase player)
	{
		super.OnApply(player);

		if (player)
		{
            player.ApplyPainkiller(0.65, 180.0, 0.75, 0.60); //pain - time - %reduction overdose
		}
	}
}
modded class PainkillerTablets
{
    void OnConsume(float amount, PlayerBase consumer)
    {
        super.OnConsume(amount, consumer);

        if (consumer)
        {
            consumer.ApplyPainkiller(0.15, 300.0, 0.20, 0.20);        
        }
    }
}