using UnrealBuildTool;
using System.Collections.Generic;

public class MotionExperimentsEditorTarget : TargetRules
{
	public MotionExperimentsEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;

		ExtraModuleNames.AddRange( new string[] { "MotionExperiments" } );
	}
}
