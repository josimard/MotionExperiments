# Motion Experiments in Unreal Engine

Some experiments on procedural animations, interpolations, tweening, etc. 

## Interpolation

### Critically Damped Spring Smoothing 

Looking for code translations of [this theory](http://mathproofs.blogspot.jp/2013/07/critically-damped-spring-smoothing.html), I stumbled upon [Keijiro's 'SmoothingTest' Repository](https://github.com/keijiro/SmoothingTest).

I took the time to convert his code in a c++ blueprint-compatible-flavor to use this smoothing type in Unreal Engine, which is similar to [Unity's SmoothDamp](https://github.com/Unity-Technologies/UnityCsReference/blob/master/Runtime/Export/Math/Vector3.cs#L75), but with less operations. 

![VectorSpringInterpCD](Documentation/VectorSpringInterpCD.png)

Accessible in Blueprints:

* [VectorSpringInterpCD](Source/MotionExperiments/Interpolation/InterpolationLibrary.h#L23)
* [FloatSpringInterpCD](Source/MotionExperiments/Interpolation/InterpolationLibrary.h#L29)
* [RotatorSpringInterpCD](Source/MotionExperiments/Interpolation/InterpolationLibrary.h#L35)
* [AngleSpringInterpCD](Source/MotionExperiments/Interpolation/InterpolationLibrary.h#L55)

You can also get the [gist of it here](https://gist.github.com/josimard/5737f3488fdfa2d207d68de282904479).


![Unreal SmoothDamp](Documentation/UnrealSmoothDamp.gif)


### Slerp for Unreal Rotators

Rotators and practical in blueprints, but using [RInterpTo](https://api.unrealengine.com/INT/API/Runtime/Engine/Kismet/UKismetMathLibrary/RInterpTo/index.html) on opposed angles sometimes gave me odd results.  

If you find your rotations going crazy, you can try using [RotatorSlerpTo()](Source/MotionExperiments/Interpolation/InterpolationLibrary.h#L48) which just converts FRotator to FQuat and then uses [FMath::QInterpTo()](https://api.unrealengine.com/INT/API/Runtime/Core/Math/FMath/QInterpTo/index.html) code.


![Unreal SmoothDamp](Documentation/UnrealRotationInterp.gif)