#include "Blueprint/UserWidget.h"
#include "Victory/Interactables/ArenaInteractable.h"
#include "Victory/Controllers/BasePlayerController.h"


void ABasePlayerController::BeginPlay() 
{
    Super::BeginPlay();

    PlayerHUD = CreateWidget(this, PlayerHUDClass);
    PlayerHUD->AddToViewport();

    InteractPromptScreen = CreateWidget(this, InteractPromptClass);

    DefeatScreen = CreateWidget(this, DefeatScreenClass);
    GameModeVictoryScreen = CreateWidget(this, GameModeVictoryScreenClass);
    RoundVictoryScreen = CreateWidget(this, RoundVictoryScreenClass);
    GameModeSelect = CreateWidget(this, GameModeSelectClass);
}

void ABasePlayerController::StaminaLow() 
{
    bStaminaLow = true;
    GetWorld()->GetTimerManager().SetTimer(StaminaTimerHandle, this, &ABasePlayerController::StaminaDefault, 0.5f, false);
}

void ABasePlayerController::StaminaDefault() 
{
    bStaminaLow = false;
}

FColor ABasePlayerController::GetStaminaColor() 
{
    if(bStaminaLow)
    {
        return StaminaLowColor;
    }
    else
    {
        return StaminaDefaultColor;
    }
}

void ABasePlayerController::DisplaySurvivalGameModeScreen(int Index) 
{
    if(Index == 0)
    {
        if(!RoundVictoryScreen->IsInViewport())
        {
            RoundVictoryScreen->AddToViewport();
        }

        GameModeVictoryScreen->RemoveFromViewport();
        DefeatScreen->RemoveFromViewport();
    }

    if(Index == 1)
    {

        if(!GameModeVictoryScreen->IsInViewport())
        {
            GameModeVictoryScreen->AddToViewport();
        }

        RoundVictoryScreen->RemoveFromViewport();
        DefeatScreen->RemoveFromViewport();

    }

    if(Index == 2)
    {
        if(!DefeatScreen->IsInViewport())
        {
            DefeatScreen->AddToViewport();
        }
    
        RoundVictoryScreen->RemoveFromViewport();
        GameModeVictoryScreen->RemoveFromViewport();
    }

    PlayerHUD->RemoveFromViewport();
}

void ABasePlayerController::DisplayDefaultPlayerHUD() 
{
    if(!PlayerHUD->IsInViewport())
    {
        PlayerHUD->AddToViewport();
    }
    

    DefeatScreen->RemoveFromViewport();
    RoundVictoryScreen->RemoveFromViewport();
    GameModeVictoryScreen->RemoveFromViewport();
    GameModeSelect->RemoveFromViewport();

    bShowMouseCursor = false;
    SetInputMode(FInputModeGameOnly());
}

void ABasePlayerController::DisplayInteractPrompt() 
{
    if(!InteractPromptScreen->IsInViewport())
    {
        InteractPromptScreen->AddToViewport();
    }

    bIsNear = true;
}

void ABasePlayerController::RemoveInteractPrompt() 
{
    if(InteractPromptScreen->IsInViewport())
    {
        InteractPromptScreen->RemoveFromViewport();
    }
    bIsNear = false;
}

void ABasePlayerController::DisplayGameModeSelect() 
{
    if(bIsNear)
    {
        GameModeSelect->AddToViewport();
        bShowMouseCursor = true;
        SetInputMode(FInputModeUIOnly());
    }
}

void ABasePlayerController::Restart() 
{
    GetWorld()->GetTimerManager().SetTimer(RestartTimerHandle, this, &APlayerController::RestartLevel, 7, false);
}
