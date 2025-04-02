#include "InterpolationLibrary.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Critically Damped Spring Interpolations (ie: Similar to Unity's SmoothDamp, but will less operations)
// Notes: 
// * The following code was created before FMath::CriticallyDampedSmoothing() was added to the engine, so implementation might differ
// * Adapted/inspired from Keijiro's Unity code: https://github.com/keijiro/SmoothingTest
// * Math reference: http://mathproofs.blogspot.jp/2013/07/critically-damped-spring-smoothing.html

FVector UInterpolationLibrary::VectorSpringInterpCD(FVector Current, FVector Target, FVector& Velocity, float DeltaTime, float InterpSpeed, float MaxVelocity)
{
	// Also refer to FMath::CriticallyDampedSmoothing() for an alternative implementation and more comments/notes
	// The advantage here for the moment is that VectorSpringInterpCD is usable in blueprints
	const FVector n1 = Velocity - (Current - Target) * (InterpSpeed * InterpSpeed * DeltaTime);
	const float n2 = 1.f + InterpSpeed * DeltaTime;

	if (MaxVelocity > 0.f)
	{
		Velocity = (n1 / (n2 * n2)).GetClampedToMaxSize(MaxVelocity);
	}
	else
	{
		Velocity = n1 / (n2 * n2);
	}

	return Current + Velocity * DeltaTime;
}

float UInterpolationLibrary::FloatSpringInterpCD(float Current, float Target, float& Velocity, float DeltaTime, float InterpSpeed, float MaxVelocity)
{
	const float n1 = Velocity - (Current - Target) * (InterpSpeed * InterpSpeed * DeltaTime);
	const float n2 = 1.f + InterpSpeed * DeltaTime;

	if (MaxVelocity > 0.f)
	{
		Velocity = FMath::Min(n1 / (n2 * n2), MaxVelocity);
	}
	else
	{
		Velocity = n1 / (n2 * n2);
	}

	return Current + Velocity * DeltaTime;
}

FRotator UInterpolationLibrary::RotatorSpringInterpCD(FRotator Current, FRotator Target, FVector4& Velocity, float DeltaTime, float InterpSpeed, float MaxVelocity)
{
	return QuatSpringInterpCD(Current.Quaternion(), Target.Quaternion(), Velocity, DeltaTime, InterpSpeed, MaxVelocity).Rotator();
}

FQuat UInterpolationLibrary::QuatSpringInterpCD(FQuat Current, FQuat Target, FVector4& Velocity, float DeltaTime, float InterpSpeed, float MaxVelocity)
{
	// More operation options available on FVector4 and multiplier for instance seems lighter, so let's convert before
	FVector4 currentVector = QuatToVector4(Current);
	FVector4 targetVector = QuatToVector4(Target);

	// We can use either of vtarget/-vtarget. Use closer one. 
	// If using FQuat, might FQuat::Squad() be usesul here?
	if (Dot4(currentVector, targetVector) < 0.f) targetVector = -targetVector;

	const FVector4 n1 = Velocity - (currentVector - targetVector) * (InterpSpeed * InterpSpeed * DeltaTime);
	const float n2 = 1.f + InterpSpeed * DeltaTime;

	if (MaxVelocity > 0.f)
	{
		Velocity = ClampVector4(n1 / (n2 * n2), MaxVelocity);
	}
	else
	{
		Velocity = n1 / (n2 * n2);
	}
	
	// Apply delta on current
	currentVector = (currentVector + Velocity * DeltaTime);

	return FQuat(currentVector.X, currentVector.Y, currentVector.Z, currentVector.W);
}

/// Same as FMath::QInterpTo but with FRotator conversions for blueprint compatiblity
FRotator UInterpolationLibrary::RotatorSlerpTo(FRotator Current, FRotator Target, float DeltaTime, float InterpSpeed)
{
	// If no interp speed, jump to target value
	if (InterpSpeed <= 0.f) return Target;

	// If the values are nearly equal, just return Target and assume we have reached our destination.
	if (Current.Equals(Target)) return Target;

	return FQuat::Slerp(Current.Quaternion(), Target.Quaternion(), FMath::Clamp(InterpSpeed * DeltaTime, 0.f, 1.f)).Rotator();
}

float UInterpolationLibrary::AngleSpringInterpCD(float CurrentAngle, float TargetAngle, float& Velocity, float DeltaTime, float InterpSpeed, float MaxVelocity, bool ContraintAngle)
{
	TargetAngle = CurrentAngle + FMath::FindDeltaAngleDegrees(CurrentAngle, ContraintAngle ? ConstrainAngle360(TargetAngle) : TargetAngle);

	return FloatSpringInterpCD(CurrentAngle, TargetAngle, Velocity, DeltaTime, InterpSpeed, MaxVelocity);
}

float UInterpolationLibrary::AngleInterpTo(float CurrentAngle, float TargetAngle, float DeltaTime, float InterpSpeed, bool ContraintAngle)
{
	TargetAngle = CurrentAngle + FMath::FindDeltaAngleDegrees(CurrentAngle, ContraintAngle ? ConstrainAngle360(TargetAngle) : TargetAngle);

	return FMath::FInterpTo(CurrentAngle, TargetAngle, DeltaTime, InterpSpeed);
}