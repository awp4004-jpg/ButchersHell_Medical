class ActionSplintDIVBase: ActionContinuousBase
{    

    override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
    {
        return true;
    }
    
    void ApplySplint( ItemBase item, PlayerBase player )
    {    
        
        PluginTransmissionAgents m_mta = PluginTransmissionAgents.Cast(GetPlugin(PluginTransmissionAgents));
        m_mta.TransmitAgents(item, player, AGT_ITEM_TO_FLESH);

		if ( player.GetModifiersManager().IsModifierActive( eModifiers.MDF_BROKEN_LEGS ) )//effectively resets the modifier
                {
                    player.GetModifiersManager().DeactivateModifier( eModifiers.MDF_BROKEN_LEGS );
                    player.ApplySplint();
                    Print("Removed a 'BROKEN_LEGS' state to player! "); 
                }
		
        
        if(player.GetHealth("GlobalHealth", "Health") > 95)
        {
            player.SetHealth("GlobalHealth", "Health", 100);
        }
        else
        {    
            player.AddHealth("GlobalHealth", "Health", 5);
        }
        
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