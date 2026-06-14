class ActionCALOKsDIVBase: ActionContinuousBase
{	

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		return true;
	}
	
	void ApplysDIVCALOK( ItemBase item, PlayerBase player )
	{	
		if (player.GetBleedingManagerServer() )
		{
			player.GetBleedingManagerServer().RemoveMostSignificantBleedingSource();
			player.GetBleedingManagerServer().RemoveMostSignificantBleedingSource();	
		}
		
		PluginTransmissionAgents m_mta = PluginTransmissionAgents.Cast(GetPlugin(PluginTransmissionAgents));
		m_mta.TransmitAgents(item, player, AGT_ITEM_TO_FLESH);
		
		if (item.HasQuantity())
		{
			item.AddQuantity(-1,true);
		}
		else
		{
			item.Delete();
		}
	}
};