# Motion Experiments in Unreal Engine

Some experiments on procedural animations, interpolations, tweening, etc. 

## Interpolation

### Critically Damped Spring Smoothing Interpolation 

Looking for different code translations of [this theory](http://mathproofs.blogspot.jp/2013/07/critically-damped-spring-smoothing.html), I stumbled upon [Keijiro's 'SmoothingTest' Repository](https://github.com/keijiro/SmoothingTest).

I took the time to convert and experiment with his code in C++ by porting his Critically Damped Spring Interpolation Smoothing for Unreal Engine. This smoothing is very similar to Unity's SmoothDamp, but with less operations. 

Accessible in Blueprints:

* [VectorSpringInterpCD](blob/master/Source/MotionExperiments/Interpolation/InterpolationLibrary.cpp#L9)
* [FloatSpringInterpCD](blob/master/Source/MotionExperiments/Interpolation/InterpolationLibrary.cpp#L9)
* [RotatorSpringInterpCD](blob/master/Source/MotionExperiments/Interpolation/InterpolationLibrary.cpp#L35)
* [AngleSpringInterpCD](blob/master/Source/MotionExperiments/Interpolation/InterpolationLibrary.cpp#L88)

You can also get the [gist of it here](https://gist.github.com/josimard/5737f3488fdfa2d207d68de282904479).



### Slerp for Rotators

Rotators and practical in blueprints, but using [RInterpTo](https://api.unrealengine.com/INT/API/Runtime/Engine/Kismet/UKismetMathLibrary/RInterpTo/index.html) on opposed angles sometimes gave me odd results. If you find your rotations going crazy, you can try using [RotatorSlerpTo()](blob/master/Source/MotionExperiments/Interpolation/InterpolationLibrary.h#L48) which just converts FRotator to FQuat and then uses FMath::QInterpTo() code.

