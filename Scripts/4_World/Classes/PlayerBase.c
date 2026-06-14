modded class PlayerBase
{
    float m_PainkillerTimer = 0.0;
    float m_PainkillerStrength = 0.0;
    float m_DebugTimer = 0.0;
    float m_PainLevel = 0.0;
    float m_PainTickTimer = 0.0;
    float m_OverdoseLevel = 0.0;
    float m_OverdoseTickTimer = 0.0;
    float m_PainkillerCooldown = 0.0;
    float m_VisualUpdateTimer = 0.0;
    float m_HealingTimer = 0.0;
    float m_StichedHealInterval = 300.0;
    float chanceForBulletWound;
    float chanceForDeepWound;
    int m_playerDeepWoundsCount;
    int m_playerDeepWoundsBandagedCount;
    int m_playerDeepWoundsStichedCount;
    int m_playerBulletWoundsCount;
    int m_playerBulletWoundsBandagedCount;
    int m_playerBulletWoundsRemovedCount;
    int m_playerBulletWoundsStichedCount;
    BleedingSourcesManagerServer bleedingManagerDeepWound;

    override void Init()
    {
        super.Init(); //For the layout and edds
        m_playerDeepWoundsCount = 0; //DeepWound
        m_playerDeepWoundsBandagedCount = 0; //DeepWoundBandage
        m_playerDeepWoundsStichedCount = 0; //DeepWoundStiched
        m_playerBulletWoundsCount = 0; //BulletWound
        m_playerBulletWoundsBandagedCount = 0; //BulletWoundBandage
        m_playerBulletWoundsRemovedCount = 0; //BulletWoundRemoved
        m_playerBulletWoundsStichedCount = 0; //BulletWoundStiched
        chanceForBulletWound = 1.0;
        chanceForDeepWound = 1.0;
        RegisterNetSyncVariableInt("m_playerDeepWoundsCount");
        RegisterNetSyncVariableInt("m_playerDeepWoundsBandagedCount");
        RegisterNetSyncVariableInt("m_playerDeepWoundsStichedCount");
        RegisterNetSyncVariableInt("m_playerBulletWoundsCount");
        RegisterNetSyncVariableInt("m_playerBulletWoundsBandagedCount");
        RegisterNetSyncVariableInt("m_playerBulletWoundsRemovedCount");
        RegisterNetSyncVariableInt("m_playerBulletWoundsStichedCount");
    }

    override void OnStoreSave(ParamsWriteContext ctx)
    {
        super.OnStoreSave(ctx);

        Param7<int, int, int, int, int, int, int> data = new Param7<int, int, int, int, int, int, int>(m_playerDeepWoundsCount,m_playerDeepWoundsBandagedCount,m_playerDeepWoundsStichedCount,m_playerBulletWoundsCount,m_playerBulletWoundsBandagedCount,m_playerBulletWoundsRemovedCount,m_playerBulletWoundsStichedCount);

        ctx.Write(data);
    }

    override bool OnStoreLoad(ParamsReadContext ctx, int version)
    {
        if (!super.OnStoreLoad(ctx, version))
            return false;

        Param7<int, int, int, int, int, int, int> data;
        if (!ctx.Read(data))
            return false;

        // Correct order
        m_playerDeepWoundsCount          = data.param1;
        m_playerDeepWoundsBandagedCount  = data.param2;
        m_playerDeepWoundsStichedCount   = data.param3;
        m_playerBulletWoundsCount        = data.param4;
        m_playerBulletWoundsBandagedCount= data.param5;
        m_playerBulletWoundsRemovedCount = data.param6;
        m_playerBulletWoundsStichedCount = data.param7;

        // Sync everything
        SynchronizeValuesDeepWounds();
        SynchronizeValuesDeepWoundsBandaged();
        SynchronizeValuesDeepWoundsStiched();
        SynchronizeValuesBulletWounds();
        SynchronizeValuesBulletWoundsBandaged();
        SynchronizeValuesBulletWoundsRemoved();
        SynchronizeValuesBulletWoundsStiched();

        return true;
    }

    //Bleeding Source and Healing System
    override void OnPlayerLoaded()
    {
        super.OnPlayerLoaded();
        ApplyBleeding();
    }
    float m_BleedingTimer = 0.0; 

    
    override void OnScheduledTick(float deltaTime)
    {
        super.OnScheduledTick(deltaTime);

        m_BleedingTimer += deltaTime;

        if (m_BleedingTimer >= 1.0)
        {
            ApplyBleeding();      
            m_BleedingTimer = 0.0;
        }

        ApplyStichedHealing(deltaTime);
        UpdateWoundEffects(deltaTime);
        UpdatePainDecrease(deltaTime);

        m_DebugTimer += deltaTime;
        /*if (m_DebugTimer >= 4.0 && (m_PainLevel > 0.01 || m_OverdoseLevel > 0.01))
        {
            string debugText = "Pain: " + m_PainLevel.ToString() +" | OD: " + m_OverdoseLevel.ToString() +" | Deep:" + m_playerDeepWoundsCount.ToString() +" | Bullet:" + m_playerBulletWoundsCount.ToString() +" | Removed:" + m_playerBulletWoundsRemovedCount.ToString() +" | Bandaged:" + (m_playerDeepWoundsBandagedCount + m_playerBulletWoundsBandagedCount).ToString() +" | Stitched:" + (m_playerDeepWoundsStichedCount + m_playerBulletWoundsStichedCount).ToString();

            this.MessageStatus(debugText);
            m_DebugTimer = 0.0;
        }*/
    }

    void ApplyBleeding()
    {
        if (!GetGame().IsServer())
            return;
        float totalBloodLoss = 0.0;

        //Deep Wounds
        if (m_playerDeepWoundsCount > 0)
        {
            totalBloodLoss += 5.0 * m_playerDeepWoundsCount;
        }

        //Bullet Wounds
        if (m_playerBulletWoundsCount > 0)
        {
            totalBloodLoss += 5.0 * m_playerBulletWoundsCount;
        }

        //Bullet Wounds Removed
        if (m_playerBulletWoundsRemovedCount > 0)
        {
            totalBloodLoss += 5.0 * m_playerBulletWoundsRemovedCount;
        }

        if (totalBloodLoss > 0.0)
        {
            float currentBlood = GetHealth("GlobalHealth","Blood");
            float newBlood = Math.Max(currentBlood - totalBloodLoss, 0.0);

            SetHealth("GlobalHealth", "Blood", newBlood);
            SetSynchDirty();
        }
    }

    void ApplyStichedHealing(float deltaTime)
    {
        if (!GetGame().IsServer())
            return;
        
        m_HealingTimer += deltaTime;

        if (m_HealingTimer >= m_StichedHealInterval)
        {
            bool healedSomething = false;

            //Deep Wound Stiched healing
            if (m_playerDeepWoundsStichedCount > 0)
            {
                m_playerDeepWoundsStichedCount--;
                healedSomething = true;
            }

            //Bullet Wounds Stiched healing
            if (m_playerBulletWoundsStichedCount > 0)
            {
                m_playerBulletWoundsStichedCount--;
                healedSomething = true;
            }

            if (healedSomething)
            {
                SetSynchDirty();
            }

            m_HealingTimer = 0.0;
        }
    }

    void ApplyPainkiller(float painReductionInstant, float durationSeconds = 300.0, float strength = 0.6, float overdoseAmount = 0.0)
    {
        if (!GetGame().IsServer())
            return;

        // Instant pain relief
        m_PainLevel = Math.Max(0.0, m_PainLevel - painReductionInstant);

        // === PAINKILLER COOLDOWN + OVERDOSE ===
        if (m_PainkillerCooldown > 0.0)
        {
            ApplyOverdose(0.45); // extra penalty for spamming
            this.MessageImportant("You took too many painkillers too quickly!");
        }

        m_PainkillerCooldown = 90.0; // 90 seconds cooldown

        // Apply custom overdose from the item
        if (overdoseAmount > 0.0)
            ApplyOverdose(overdoseAmount);

        m_PainkillerTimer = durationSeconds;
        m_PainkillerStrength = Math.Min(1.0, strength);

        SetSynchDirty();
        this.MessageStatus("You feel the painkillers kicking in...");

        GetModifiersManager().ActivateModifier(eModifiers.MDF_PAINKILLERS);
    }

    void ApplyOverdose(float amount)
    {
        if (!GetGame().IsServer())
            return;

        m_OverdoseLevel = Math.Min(1.0, m_OverdoseLevel + amount);
    }

    //Deep Wound
    void SynchronizeValuesDeepWounds()
    {
        if (GetGame().IsServer())
            SetSynchDirty();
    }

    void SetDeepWounds()
    {
        m_playerDeepWoundsCount++;
        SetSynchDirty();
    }

    void RemoveDeepWound()
    {
        if (m_playerDeepWoundsCount > 0)
        {
            m_playerDeepWoundsCount--; 
            SetSynchDirty();
        }
    }

    int GetDeepWounds()
    {
        SetSynchDirty();
        return m_playerDeepWoundsCount;
    }

    bool HasDeepWounds()
    {
        return m_playerDeepWoundsCount > 0;
    }

    //Deep Wound Bandaged
    void SynchronizeValuesDeepWoundsBandaged()
    {
        if (GetGame().IsServer())
            SetSynchDirty();
    }

    void SetDeepWoundsBandaged()
    {
        m_playerDeepWoundsBandagedCount++;
            SetSynchDirty();
    }

    void RemoveDeepWoundBandaged()
    {
        if (m_playerDeepWoundsBandagedCount > 0)
        {
            m_playerDeepWoundsBandagedCount--;
            SetSynchDirty();
        }
    }

    int GetDeepWoundsBandaged()
    {
        SetSynchDirty();
        return m_playerDeepWoundsBandagedCount;
    }

    bool HasDeepWoundsBandaged()
    {
        return m_playerDeepWoundsBandagedCount > 0;
    }

    //Deep Wound Stiched
    void SynchronizeValuesDeepWoundsStiched()
    {
        if (GetGame().IsServer())
            SetSynchDirty();
    }

    void SetDeepWoundsStiched()
    {
        m_playerDeepWoundsStichedCount++;
            SetSynchDirty();
    }

    void RemoveDeepWoundStiched()
    {
        if (m_playerDeepWoundsStichedCount > 0)
        {
            m_playerDeepWoundsStichedCount--;
            SetSynchDirty();
        }
    }

    int GetDeepWoundsStiched()
    {
        SetSynchDirty();
        return m_playerDeepWoundsStichedCount;
    }

    bool HasDeepWoundsStiched()
    {
        return m_playerDeepWoundsStichedCount > 0;
    }

    //Bullet Wound
    void SynchronizeValuesBulletWounds()
    {
        if (GetGame().IsServer())
            SetSynchDirty();
    }


    void SetBulletWounds()
    {
        m_playerBulletWoundsCount++;
        SetSynchDirty();
    }

    void RemoveBulletWounds()
    {
        if (m_playerBulletWoundsCount > 0)
        {
            m_playerBulletWoundsCount--; 
            SetSynchDirty();
        }
    }

    int GetBulletWounds()
    {
        SetSynchDirty();
        return m_playerBulletWoundsCount;
    }

    bool HasBulletWounds()
    {
        return m_playerBulletWoundsCount > 0;
    }

    //Bullet Wound Bandaged
    void SynchronizeValuesBulletWoundsBandaged()
    {
        if (GetGame().IsServer())
            SetSynchDirty();
    }

    void SetBulletWoundsBandaged()
    {
        m_playerBulletWoundsBandagedCount++;
        SetSynchDirty();
    }

    void RemoveBulletWoundBandaged()
    {
        if (m_playerBulletWoundsBandagedCount > 0)
        {
            m_playerBulletWoundsBandagedCount--;
            SetSynchDirty();
        }
    }

    int GetBulletWoundsBandaged()
    {
        SetSynchDirty();
        return m_playerBulletWoundsBandagedCount;
    }

    bool HasBulletWoundsBandaged()
    {
        return m_playerBulletWoundsBandagedCount > 0;
    }
 
    //Bullet Wound Removed
    void SynchronizeValuesBulletWoundsRemoved()
    {
        if (GetGame().IsServer())
            SetSynchDirty();
    }

    void SetBulletWoundsRemoved()
    {
        m_playerBulletWoundsRemovedCount++;
        SetSynchDirty();
    }

    void RemoveBulletwoundRemoved()
    {
        if (m_playerBulletWoundsRemovedCount > 0)
        {
            m_playerBulletWoundsRemovedCount--; 
            SetSynchDirty();
        }
    }

    int GetBulletWoundsRemoved()
    {
        SetSynchDirty();
        return m_playerBulletWoundsRemovedCount;
    }

    bool HasBulletWoundsRemoved()
    {
        return m_playerBulletWoundsRemovedCount > 0;
    }
 
    //Bullet Wound Stiched
    void SynchronizeValuesBulletWoundsStiched()
    {
        if (GetGame().IsServer())
            SetSynchDirty();
    }

    void SetBulletWoundsStiched()
    {
        m_playerBulletWoundsStichedCount++;
        SetSynchDirty();
    }

    void RemoveBulletwoundStiched()
    {
        if (m_playerBulletWoundsStichedCount > 0)
        {
            m_playerBulletWoundsStichedCount--; 
            SetSynchDirty();
        }
    }

    int GetBulletWoundsStiched()
    {
        SetSynchDirty();
        return m_playerBulletWoundsStichedCount;
    }

    bool HasBulletWoundsStiched()
    {
        return m_playerBulletWoundsStichedCount > 0;
    }
 

    // Check if the player is wearing a vest
    bool HasVest()
    {
        EntityAI itemInSlot = FindAttachmentBySlotName("Vest");

        return itemInSlot != null;
    }

    override void EEHitBy(TotalDamageResult damageResult, int damageType, EntityAI source, int component, string dmgZone, string ammo, vector modelPos, float speedCoef)
    {
        super.EEHitBy(damageResult, damageType, source, component, dmgZone, ammo, modelPos, speedCoef);

        float randomChance = Math.RandomFloat(0.0, 1.0);
    
        if (damageType == DT_FIRE_ARM) 
        {
            if (GetGame().IsServer()) 
            {
                float chanceForBulletWound = 0.0; // Default 70% chance

                // If hit on the torso and player has a vest, reduce chance to 30%
                if (dmgZone == "Torso" && HasVest())  
                {
                    chanceForBulletWound = 0.3;  
                }
                else
                {
                    chanceForBulletWound = 0.7;
                }

                if (randomChance <= chanceForBulletWound) 
                {
                    this.SetBulletWounds();  
                }
                else
                {

                }
            }
        }
    


        // Deep Wound from close combat (chance logic as before)
        //if (damageType == DT_CLOSE_COMBAT)
        //Zombie and animal hit register
        if (source && (source.IsZombie() || source.IsAnimal()))
        {
            if (GetGame().IsServer())  // Ensure only the server handles the random chance
            {
                // If the player has a vest, reduce the chance of getting a bullet wound
                if (dmgZone == "Torso" && HasVest())  // Add your own method for checking if the player has a vest equipped
                {
                    chanceForDeepWound = 0.05;  // Example: 30% chance if the player has a vest
                }
                else
                {
                    chanceForDeepWound = 0.45;
                }

                if (randomChance <= chanceForDeepWound)
                {
                    this.SetDeepWounds();
                }
                else
                {

                }
            }
        }

        //bladed weapon register
        // weapon.IsInherited("CombatKnife")
        //if(ammo == "MeleeSharpLight_1" || ammo == "MeleeSharpLight_2" || ammo == "MeleeSharpLight_3" || ammo == "MeleeSharpLight_4" || ammo == "MeleeSharpHeavy_1" || ammo == "MeleeSharpHeavy_2" || ammo == "MeleeSharpHeavy_3" || ammo == "MeleeSharpHeavy_4")
        /*if (MELEE_AMMO_TYPES.Contains(ammo))
        {
            if (GetGame().IsServer())  // Ensure only the server handles the random chance
            {
                // If the player has a vest, reduce the chance of getting a bullet wound
                if (dmgZone == "Torso" && HasVest())    // Add your own method for checking if the player has a vest equipped
                {
                    chanceForDeepWound = 0.0;  // Example: 30% chance if the player has a vest
                }
                else
                {
                    chanceForDeepWound = 1.0;
                }

                if (randomChance <= chanceForDeepWound)
                {
                    this.SetDeepWounds();
                    this.MessageImportant("I have received a deep wound from close combat!");
                }
                else
                {
                    this.MessageImportant("The close combat didn't cause a deep wound.");
                }
            }
        }*/
    }

    /*override void EEKilled(Object killer)
    {
        float health = GetHealth("GlobalHealth", "Health");

        if (health <= 0)
        {
            SetHealth("GlobalHealth", "Health", 1.0);

            if (!IsUnconscious())
            {
                DayZPlayerSyncJunctures.SendPlayerUnconsciousness(this, true);
                MessageImportant("You are critically injured and unconscious...");
            }

            return;
        }

        super.EEKilled(killer);
    }*/

    // ====================== ALL STAGES CAUSE PAIN ======================
    void UpdateWoundEffects(float deltaTime)
    {
        if (!GetGame().IsServer())
            return;

        m_PainTickTimer += deltaTime;

        if (m_PainkillerTimer > 0.0)
        {
            m_PainkillerTimer -= deltaTime;

            if (m_PainLevel > 0.0)
            {
                float relief = m_PainkillerStrength * 0.08 * deltaTime;
                m_PainLevel = Math.Max(0.0, m_PainLevel - relief);
            }
        }

        if (m_PainTickTimer >= 5.0)
        {
            float painIncrease = 0.0;

            // === PAIN BUILD-UP ===
            painIncrease += m_playerDeepWoundsCount * 0.02;      // 1 deep wound = slow
            painIncrease += m_playerBulletWoundsCount * 0.02;    // 5 bullet wounds still takes time
            painIncrease += m_playerBulletWoundsRemovedCount * 0.021;
            painIncrease += m_playerDeepWoundsBandagedCount * 0.015;
            painIncrease += m_playerBulletWoundsBandagedCount * 0.012;
            painIncrease += m_playerDeepWoundsStichedCount * 0.008;
            painIncrease += m_playerBulletWoundsStichedCount * 0.007;

            if (m_PainkillerTimer > 0.0)
            {
                painIncrease *= (1.0 - m_PainkillerStrength * 0.7); //70% pain reduction
            }

            m_PainLevel = Math.Min(1.0, m_PainLevel + painIncrease);

            // Groaning
            if (m_PainLevel > 0.65)
            {
            }

            // Shock damage (slow)
            if (m_PainLevel > 0.70)
            {
                this.AddHealth("GlobalHealth", "Shock", -8);
            }

            // Very high pain = health loss
            if (m_PainLevel > 0.90)
            {
                this.AddHealth("GlobalHealth", "Health", -1.0);
            }

            if (m_OverdoseLevel > 0.0)
            {
                m_OverdoseLevel = Math.Max(0.0, m_OverdoseLevel - 0.055); // faster decrease

                if (m_OverdoseLevel > 0.40)
                {
                    this.AddHealth("GlobalHealth", "Shock", -30.0);   // strong shock
                }
                else if (m_OverdoseLevel > 0.15)
                {
                    this.AddHealth("GlobalHealth", "Shock", -10.0);
                }
            }

            // === PAINKILLER COOLDOWN DECREASE ===
            if (m_PainkillerCooldown > 0.0)
            {
                m_PainkillerCooldown -= 5.0; // because we check every 5 seconds
            }

            m_PainTickTimer = 0.0;
        }
    }
    
    void UpdatePainDecrease(float deltaTime)
    {
        if (!GetGame().IsServer())
            return;

        if (m_PainLevel > 0.0 && m_playerDeepWoundsCount == 0 && m_playerBulletWoundsCount == 0 && m_playerBulletWoundsRemovedCount == 0)
        {
            m_PainLevel = Math.Max(0.0, m_PainLevel - 0.025 * deltaTime);
        }
    }
}