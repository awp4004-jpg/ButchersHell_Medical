modded class InjuryAnimationHandler
{
    override eInjuryHandlerLevels GetInjuryLevel(float health)
    {
        eInjuryHandlerLevels result = super.GetInjuryLevel(health);

        PlayerBase player = PlayerBase.Cast(m_Player);
        if (!player)
            return result;

        float totalPain = player.m_PainLevel;

        // Extra pain from wounds (also slowed down)
        totalPain += player.m_playerDeepWoundsCount * 0.045;
        totalPain += player.m_playerBulletWoundsCount * 0.035;
        totalPain += player.m_playerBulletWoundsRemovedCount * 0.04;
        totalPain += player.m_playerDeepWoundsBandagedCount * 0.015;
        totalPain += player.m_playerBulletWoundsBandagedCount * 0.012;
        totalPain += player.m_playerDeepWoundsStichedCount * 0.008;
        totalPain += player.m_playerBulletWoundsStichedCount * 0.007;

        totalPain = Math.Min(1.0, totalPain);

        // Limping thresholds - slower to reach heavy limp
        if (totalPain > 0.88)
            result = eInjuryHandlerLevels.RUINED;           // heavy limp
        else if (totalPain > 0.76)
            result = eInjuryHandlerLevels.BADLY_DAMAGED;    // medium limp
        else if (totalPain > 0.62)
            result = eInjuryHandlerLevels.DAMAGED;          // light limp
        else if (totalPain > 0.45)
            result = eInjuryHandlerLevels.WORN;             // very light limp

        return result;
    }
}