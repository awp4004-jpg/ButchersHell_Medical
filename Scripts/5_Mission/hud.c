modded class IngameHud
{
    protected bool m_LastDeepWoundVisible = false;
    protected bool m_LastDeepWoundBandagedVisible = false;
    protected bool m_LastDeepWoundStichedVisible = false;
    protected bool m_LastBulletWoundVisible = false;
    protected bool m_LastBulletWoundBandagedVisible = false;
    protected bool m_LastBulletWoundRemovedVisible = false;
    protected bool m_LastBulletWoundStichedVisible = false;
    protected TextWidget m_DeepWoundCount;
    protected TextWidget m_DeepWoundBandagedCount;
    protected TextWidget m_DeepWoundStichedCount;
    protected TextWidget m_BulletWoundCount;
    protected TextWidget m_BulletWoundBandagedCount;
    protected TextWidget m_BulletWoundRemovedCount;
    protected TextWidget m_BulletWoundStichedCount;
    PlayerBase m_Player;
    protected float m_LastWoundCheck = 0;
    int m_DeepWound;
    int m_DeepWoundBandaged;
    int m_DeepWoundStiched;
    int m_Bulletwound;
    int m_BulletWoundBandaged;
    int m_BulletWoundRemoved;
    int m_BulletWoundStiched;

    override void Init( Widget hud_panel_widget )
    {
        super.Init(hud_panel_widget);
        RegisterBadgeWounds();
    }

    override void OnPlayerLoaded()
    {
        super.OnPlayerLoaded();

        m_Player = PlayerBase.Cast(GetGame().GetPlayer());
    }

    protected void RegisterBadgeWounds()
    {
        float x, y;
        
        ref Widget defaultBadgesPanel = m_HudPanelWidget.FindAnyWidget("BadgesPanel");
        if (!defaultBadgesPanel) return;  // Null check

        defaultBadgesPanel.GetSize(x, y);
        defaultBadgesPanel.SetSize(x + 280, y);  // +40 per badge; adjust if needed for overflow

        ref Widget badgeRoot = GetGame().GetWorkspace().CreateWidgets("ButchersHell_Medical/gui/badge_template.layout");
        if (!badgeRoot) return;  // Null check if layout fails to load

        // Deep Wound setup
        ref ImageWidget deepWidget = ImageWidget.Cast(badgeRoot.FindAnyWidget("DeepWound"));       
        if (deepWidget)
        {
            badgeRoot.RemoveChild(deepWidget);
            defaultBadgesPanel.AddChild(deepWidget);

            m_DeepWoundCount = TextWidget.Cast(deepWidget.FindAnyWidget("DeepWoundCount"));
            if (m_DeepWoundCount)
            {
                m_DeepWoundCount.SetText("");
            }
        }

        // Deep Wound Bandaged setup
        ref ImageWidget deepBandagedWidget = ImageWidget.Cast(badgeRoot.FindAnyWidget("DeepWoundBandaged"));       
        if (deepBandagedWidget)
        {
            badgeRoot.RemoveChild(deepBandagedWidget);
            defaultBadgesPanel.AddChild(deepBandagedWidget);

            m_DeepWoundBandagedCount = TextWidget.Cast(deepBandagedWidget.FindAnyWidget("DeepWoundBandagedCount"));
            if (m_DeepWoundBandagedCount)
            {
                m_DeepWoundBandagedCount.SetText("");
            }
        }

        // Deep Wound Stiched setup
        ref ImageWidget deepStichedWidget = ImageWidget.Cast(badgeRoot.FindAnyWidget("DeepWoundStiched"));       
        if (deepStichedWidget)
        {
            badgeRoot.RemoveChild(deepStichedWidget);
            defaultBadgesPanel.AddChild(deepStichedWidget);

            m_DeepWoundStichedCount = TextWidget.Cast(deepStichedWidget.FindAnyWidget("DeepWoundStichedCount"));
            if (m_DeepWoundStichedCount)
            {
                m_DeepWoundStichedCount.SetText("");
            }
        }

        // Bullet Wound setup
        ref ImageWidget bulletWidget = ImageWidget.Cast(badgeRoot.FindAnyWidget("BulletWound"));       
        if (bulletWidget)
        {
            badgeRoot.RemoveChild(bulletWidget);
            defaultBadgesPanel.AddChild(bulletWidget);

            m_BulletWoundCount = TextWidget.Cast(bulletWidget.FindAnyWidget("BulletWoundCount"));
            if (m_BulletWoundCount)
            {
                m_BulletWoundCount.SetText("");
            }
        }

        // Bullet Wound Bandaged setup
        ref ImageWidget bulletBandagedWidget = ImageWidget.Cast(badgeRoot.FindAnyWidget("BulletWoundBandaged"));       
        if (bulletBandagedWidget)
        {
            badgeRoot.RemoveChild(bulletBandagedWidget);
            defaultBadgesPanel.AddChild(bulletBandagedWidget);

            m_BulletWoundBandagedCount = TextWidget.Cast(bulletBandagedWidget.FindAnyWidget("BulletWoundBandagedCount"));
            if (m_BulletWoundBandagedCount)
            {
                m_BulletWoundBandagedCount.SetText("");
            }
        }

        // Bullet Wound Removed setup
        ref ImageWidget bulletRemovedWidget = ImageWidget.Cast(badgeRoot.FindAnyWidget("BulletWoundRemoved"));       
        if (bulletRemovedWidget)
        {
            badgeRoot.RemoveChild(bulletRemovedWidget);
            defaultBadgesPanel.AddChild(bulletRemovedWidget);

            m_BulletWoundRemovedCount = TextWidget.Cast(bulletRemovedWidget.FindAnyWidget("BulletWoundRemovedCount"));
            if (m_BulletWoundRemovedCount)
            {
                m_BulletWoundRemovedCount.SetText("");
            }
        }

        // Bullet Wound Stiched setup
        ref ImageWidget bulletStichedWidget = ImageWidget.Cast(badgeRoot.FindAnyWidget("BulletWoundStiched"));       
        if (bulletStichedWidget)
        {
            badgeRoot.RemoveChild(bulletStichedWidget);
            defaultBadgesPanel.AddChild(bulletStichedWidget);

            m_BulletWoundStichedCount = TextWidget.Cast(bulletStichedWidget.FindAnyWidget("BulletWoundStichedCount"));
            if (m_BulletWoundStichedCount)
            {
                m_BulletWoundStichedCount.SetText("");
            }
        }

        // Clean up root if needed (optional, but good practice)
        badgeRoot = null;
    }

    override void Update( float timeslice )
    {
        super.Update( timeslice );

        if (m_Player)
        {
            float currentTime = GetGame().GetTime();
            if (currentTime - m_LastWoundCheck > 1000)  // Check every 1s
            {
                m_LastWoundCheck = currentTime;
                bool hasDeepWounds = m_Player.HasDeepWounds();
                bool hasDeepWoundsBandaged = m_Player.HasDeepWoundsBandaged();
                bool hasDeepWoundsStiched = m_Player.HasDeepWoundsStiched();
                bool hasBulletWounds = m_Player.HasBulletWounds();
                bool hasBulletWoundsBandaged = m_Player.HasBulletWoundsBandaged();
                bool hasBulletWoundsRemoved = m_Player.HasBulletWoundsRemoved();
                bool hasBulletWoundsStiched = m_Player.HasBulletWoundsStiched();

                SetDeepWoundVisible(hasDeepWounds);
                SetDeepWoundBandagedVisible(hasDeepWoundsBandaged);
                SetDeepWoundStichedVisible(hasDeepWoundsStiched);
                SetBulletWoundVisible(hasBulletWounds);
                SetBulletWoundBandagedVisible(hasBulletWoundsBandaged);
                SetBulletWoundRemovedVisible(hasBulletWoundsRemoved);
                SetBulletWoundStichedVisible(hasBulletWoundsStiched);

                //Deep Wound
                if (hasDeepWounds && m_DeepWoundCount)
                {
                    int deepCount = m_Player.GetDeepWounds(); 
                    m_DeepWoundCount.SetText(deepCount.ToString());
                    m_DeepWound = deepCount;

                }
                else if (m_DeepWoundCount)
                {
                    m_DeepWoundCount.SetText("");
                }

                //Deep Wound Bandaged
                if (hasDeepWoundsBandaged && m_DeepWoundBandagedCount)
                {
                    int deepBandagedCount = m_Player.GetDeepWoundsBandaged(); 
                    m_DeepWoundBandagedCount.SetText(deepBandagedCount.ToString());
                    m_DeepWoundBandaged = deepBandagedCount;

                }
                else if (m_DeepWoundBandagedCount)
                {
                    m_DeepWoundBandagedCount.SetText("");
                }

                //Deep Wound Stiched
                if (hasDeepWoundsStiched && m_DeepWoundStichedCount)
                {
                    int deepStichedCount = m_Player.GetDeepWoundsStiched(); 
                    m_DeepWoundStichedCount.SetText(deepStichedCount.ToString());
                    m_DeepWoundStiched = deepStichedCount;

                }
                else if (m_DeepWoundStichedCount)
                {
                    m_DeepWoundStichedCount.SetText("");
                }

                //Bullet Wound
                if (hasBulletWounds && m_BulletWoundCount)
                {
                    int bulletCount = m_Player.GetBulletWounds();  
                    m_BulletWoundCount.SetText(bulletCount.ToString());
                    m_Bulletwound = bulletCount;

                }
                else if (m_BulletWoundCount)
                {
                    m_BulletWoundCount.SetText("");
                }

                //Bullet Wound Bandaged
                if (hasBulletWoundsBandaged && m_BulletWoundBandagedCount)
                {
                    int bulletBandagedCount = m_Player.GetBulletWoundsBandaged();  
                    m_BulletWoundBandagedCount.SetText(bulletBandagedCount.ToString());
                    m_BulletWoundBandaged = bulletBandagedCount;

                }
                else if (m_BulletWoundBandagedCount)
                {
                    m_BulletWoundBandagedCount.SetText("");
                }

                //Bullet Wound Removed
                if (hasBulletWoundsRemoved && m_BulletWoundRemovedCount)
                {
                    int bulletRemovedCount = m_Player.GetBulletWoundsRemoved();  
                    m_BulletWoundRemovedCount.SetText(bulletRemovedCount.ToString());
                    m_BulletWoundRemoved = bulletRemovedCount;

                }
                else if (m_BulletWoundRemovedCount)
                {
                    m_BulletWoundRemovedCount.SetText("");
                }

                //Bullet Wound Stiched
                if (hasBulletWoundsStiched && m_BulletWoundStichedCount)
                {
                    int bulletStichedCount = m_Player.GetBulletWoundsStiched();  
                    m_BulletWoundStichedCount.SetText(bulletStichedCount.ToString());
                    m_BulletWoundStiched = bulletStichedCount;

                }
                else if (m_BulletWoundStichedCount)
                {
                    m_BulletWoundStichedCount.SetText("");
                }
            }
        }
    }

    //Deep Wound
    void SetDeepWoundVisible(bool visible)
    {
        if (m_LastDeepWoundVisible == visible) 
            return;
            
        m_LastDeepWoundVisible = visible;

        ref Widget defaultBadgesPanel = m_HudPanelWidget.FindAnyWidget("BadgesPanel");
        if (!defaultBadgesPanel) 
            return;

        ref Widget deepWidget = defaultBadgesPanel.FindAnyWidget("DeepWound");
        if (deepWidget)
        {
            deepWidget.Show(visible);
        }
    }

    //Deep Wound Bandaged
    void SetDeepWoundBandagedVisible(bool visible)
    {
        if (m_LastDeepWoundBandagedVisible == visible) 
            return;
            
        m_LastDeepWoundBandagedVisible = visible;

        ref Widget defaultBadgesPanel = m_HudPanelWidget.FindAnyWidget("BadgesPanel");
        if (!defaultBadgesPanel) 
            return;

        ref Widget deepBandagedWidget = defaultBadgesPanel.FindAnyWidget("DeepWoundBandaged");
        if (deepBandagedWidget)
        {
            deepBandagedWidget.Show(visible);
        }
    }

    //Deep Wound Stiched
    void SetDeepWoundStichedVisible(bool visible)
    {
        if (m_LastDeepWoundStichedVisible == visible) 
            return;
            
        m_LastDeepWoundStichedVisible = visible;

        ref Widget defaultBadgesPanel = m_HudPanelWidget.FindAnyWidget("BadgesPanel");
        if (!defaultBadgesPanel) 
            return;

        ref Widget deepStichedWidget = defaultBadgesPanel.FindAnyWidget("DeepWoundStiched");
        if (deepStichedWidget)
        {
            deepStichedWidget.Show(visible);
        }
    }

    //Bullet Wound
    void SetBulletWoundVisible(bool visible)
    {
        if (m_LastBulletWoundVisible == visible) 
            return;

        m_LastBulletWoundVisible = visible;

        ref Widget defaultBadgesPanel = m_HudPanelWidget.FindAnyWidget("BadgesPanel");
        if (!defaultBadgesPanel) 
            return;

        ref Widget bulletWidget = defaultBadgesPanel.FindAnyWidget("BulletWound");
        if (bulletWidget)
        {
            bulletWidget.Show(visible);
        }
    }

    //Bullet Wound Bandaged
    void SetBulletWoundBandagedVisible(bool visible)
    {
        if (m_LastBulletWoundBandagedVisible == visible) 
            return;

        m_LastBulletWoundBandagedVisible = visible;

        ref Widget defaultBadgesPanel = m_HudPanelWidget.FindAnyWidget("BadgesPanel");
        if (!defaultBadgesPanel) 
            return;

        ref Widget bulletBandagedWidget = defaultBadgesPanel.FindAnyWidget("BulletWoundBandaged");
        if (bulletBandagedWidget)
        {
            bulletBandagedWidget.Show(visible);
        }
    }

    //Bullet Wound Removed
    void SetBulletWoundRemovedVisible(bool visible)
    {
        if (m_LastBulletWoundRemovedVisible == visible) 
            return;

        m_LastBulletWoundRemovedVisible = visible;

        ref Widget defaultBadgesPanel = m_HudPanelWidget.FindAnyWidget("BadgesPanel");
        if (!defaultBadgesPanel) 
            return;

        ref Widget bulletRemovedWidget = defaultBadgesPanel.FindAnyWidget("BulletWoundRemoved");
        if (bulletRemovedWidget)
        {
            bulletRemovedWidget.Show(visible);
        }
    }

    //Bullet Wound Stiched
    void SetBulletWoundStichedVisible(bool visible)
    {
        if (m_LastBulletWoundStichedVisible == visible) 
            return;

        m_LastBulletWoundStichedVisible = visible;

        ref Widget defaultBadgesPanel = m_HudPanelWidget.FindAnyWidget("BadgesPanel");
        if (!defaultBadgesPanel) 
            return;

        ref Widget bulletStichedWidget = defaultBadgesPanel.FindAnyWidget("BulletWoundStiched");
        if (bulletStichedWidget)
        {
            bulletStichedWidget.Show(visible);
        }
    }
};