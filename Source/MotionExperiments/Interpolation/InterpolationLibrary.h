#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "InterpolationLibrary.generated.h"

/**
 * Interpolation library
 * @see https://github.com/josimard/MotionExperiments
 * @see Unreal Engine built-in interpolations: https://api.unrealengine.com/INT/BlueprintAPI/Math/Interpolation/index.html
 */
UCLASS()
class UInterpolationLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:

	/**
	* Critically Damped Spring Interpolation (ie: Similar to Unity's SmoothDamp, but will less operations)
	*/
	UFUNCTION(BlueprintPure, Category = "Math|Interpolation", meta = (Keywords = "interp vinterp vectorspringinterp lerp smoothdamp"))
	static FVector VectorSpringInterpCD(FVector Current, FVector Target, UPARAM(ref) FVector& Velocity, float DeltaTime, float InterpSpeed = 10.f, float MaxVelocity = 0.f);

	/**
	* Critically Damped Spring Interpolation (ie: Similar to Unity's SmoothDamp, but will less operations)
	*/
	UFUNCTION(BlueprintPure, Category = "Math|Interpolation", meta = (Keywords = "interp finterp floatspringinterp lerp smoothdamp"))
	static float FloatSpringInterpCD(float Current, float Target, UPARAM(ref) float& Velocity, float DeltaTime, float InterpSpeed = 10.f, float MaxVelocity = 0.f);

	/**
	* Critically Damped Spring Interpolation
	*/
	UFUNCTION(BlueprintCallable, Category = "Math|Interpolation", meta = (Keywords = "rinterp smoothdamp"))
	static FRotator RotatorSpringInterpCD(FRotator Current, FRotator Target, UPARAM(ref) FVector4& Velocity, float DeltaTime, float InterpSpeed = 10.f, float MaxVelocity = 0.f);

	/**
	* Critically Damped Spring Interpolation
	*/
	UFUNCTION(BlueprintPure, Category = "Math|Interpolation", meta = (Keywords = "fquat smoothdamp"))
	static FQuat QuatSpringInterpCD(FQuat Current, FQuat Target, UPARAM(ref) FVector4& Velocity, float DeltaTime, float InterpSpeed = 10.f, float MaxVelocity = 0.f);

	/**
	* Using FMath::Slerp() like FMath::QInterpTo() 
	* The conversions to FQuat costs, but it gives less errors thant RInterp when interpolating between opposed different angles
	*/
	UFUNCTION(BlueprintCallable, Category = "Math|Interpolation", meta = (Keywords = "rinterp qinterp slerp"))
	static FRotator RotatorSlerpTo(FRotator Current, FRotator Target, float DeltaTime, float InterpSpeed = 10.f);

	/**
	* Critically Damped Spring Interpolation for angles in DEGREES
	* For 0-360 angles, (not -180 to 180 heading angles)
	*/
	UFUNCTION(BlueprintPure, Category = "Math|Interpolation", meta = (Keywords = "finterp floatspringinterp smoothdamp"))
	static float AngleSpringInterpCD(float CurrentAngle, float TargetAngle, UPARAM(ref) float& Velocity, float DeltaTime, float InterpSpeed = 10.f, float MaxVelocity = 0.f, bool ContraintAngle = true);

	/**
	* Angle Interpolation in DEGREES
	* For 0-360 angles, (not -180 to 180 heading angles)
	*/
	UFUNCTION(BlueprintPure, Category = "Math|Interpolation", meta = (Keywords = "finterp"))
	static float AngleInterpTo(float CurrentAngle, float TargetAngle, float DeltaTime, float InterpSpeed = 10.f, bool ContraintAngle = true);



// Utility methods
private:

	FORCEINLINE static FVector4 QuatToVector4(const FQuat& Quat)
	{
		return FVector4(Quat.X, Quat.Y, Quat.Z, Quat.W);
	}

	FORCEINLINE static FVector4 ClampVector4(FVector4 Target, float MaxSize)
	{
		if (MaxSize < KINDA_SMALL_NUMBER)
		{
			return FVector4(0.f, 0.f, 0.f, 0.f);
		}

		const float VSq = Target.SizeSquared();
		if (VSq > FMath::Square(MaxSize))
		{
			const float Scale = MaxSize * FMath::InvSqrt(VSq);
			return FVector4(Target.X*Scale, Target.Y*Scale, Target.Z*Scale, Target.W*Scale);
		}
		else
		{
			return Target;
		}
	}

	// In Degrees, [0,360]
	FORCEINLINE static float ConstrainAngle360(float x)
	{
		x = FMath::Fmod(x, 360);
		if (x < 0) x += 360;
		return x;
	}

	// In Degrees, [-180,180]
	FORCEINLINE static float ConstrainAngle180(float x)
	{
		x = FMath::Fmod(x + 180, 360);
		if (x < 0) x += 360;
		return x - 180;
	}
	
};
