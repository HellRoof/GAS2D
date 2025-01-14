// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemComponent.h"
#include "Weapons/TP_AmmoAttributeSet.h"
#include "../TestProject.h"
#include "Characters/TP_CharacterBase.h"

#include "TP_SideScrollerCharacter.generated.h"

class ATP_WeaponBase;

UCLASS(config=Game)
class ATP_SideScrollerCharacter : public ATP_CharacterBase
{
	GENERATED_BODY()
	

		//virtual void HealthChanged(const FOnAttributeChangeData& Data);

	
	/** Side view camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* SideViewCameraComponent;

	/** Camera boom positioning the camera beside the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Abilities | Attributes", meta = (AllowPrivateAccess = "true"))
	class UTP_AmmoAttributeSet* AmmoAttributeSet;

protected:

	UPROPERTY()
	ATP_WeaponBase* CurrentWeapon;

	FDelegateHandle HealthChangedDelegateHandle;

	virtual void BeginPlay() override;

	// Attribute changed callbacks
	virtual void HealthChanged(const FOnAttributeChangeData& Data);


public:
	ATP_SideScrollerCharacter();
	
	UFUNCTION(BlueprintNativeEvent)
		void PlayerDeath();
	virtual void PlayerDeath_Implementation();

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Weapon")
	FName WeaponAttachPoint;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon")
	TArray<TSubclassOf <class ATP_WeaponBase>> WeaponClasses;

	UPROPERTY()
	TArray<ATP_WeaponBase*> Weapons;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon")
	FGameplayTag CurrentWeaponTag;

	UFUNCTION(BlueprintCallable, Category = "Weapon")
    ATP_WeaponBase* GetCurrentWeapon() const;

	UFUNCTION(BlueprintCallable, Category = "Weapon")
    virtual void NextWeapon();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
    virtual void PreviousWeapon();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "Abilities | Attributes")
	bool IsAlive() const;

	virtual void InitializeWeapons();

	FName GetWeaponAttachPoint();

	/** Returns SideViewCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetSideViewCameraComponent() const { return SideViewCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	//FORCEINLINE class UAbilitySystemComponent* GetAbilitySystem() const { return AbilitySystem; }
};
