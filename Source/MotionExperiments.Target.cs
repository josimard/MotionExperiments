using UnrealBuildTool;
using System.Collections.Generic;

public class MotionExperimentsTarget : TargetRules
{
	public MotionExperimentsTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;

		ExtraModuleNames.AddRange( new string[] { "MotionExperiments" } );
	}
}
