// Fill out your copyright notice in the Description page of Project Settings.

#include "Victory/Characters/BaseCharacter.h"
#include "Victory/Characters/GuardAI.h"


void AGuardAI::GuardMeleeAttack() 
{
    if(!bIsAttacking && !bIsDodging)
    {
        PlayAnimMontage(GuardAttack, 1);
        DisableMovement(true);
        bIsAttacking = true;
    }
}

int AGuardAI::GetLevel() 
{
    return EnemyLevel;
}

void AGuardAI::SetGuardLevel(int Level) 
{
    EnemyLevel = Level;
    MaxHealth += 1.25 * Level;
    Health = MaxHealth;
}
