Team    : Boleh
Course  : GAM200
Memeber : Kang Tae Wook, Jung Soon Woo, Choi Jin Hyun
Date    : 10/9/18

1.Clang-format team-style
	
	- AlignConsecutiveAssignments(true) 
		We agreed to set allignment operators to be in consecutive lines.
	
	- AlignConsecutiveDeclarations(true)
		We agreed to set alignment of the declaration names to be in consecutive lines.
	
	- AlwaysBreakTemplateDeclarations(true)
		we agreed to always break after template declaration.
	
	- BraceWrapping
		- AfterControlStatement(true)
		  	We agreed to use wrap control statements.
		- AfterFunction(true)
			We agreed to wrap function definitions.
  		- AfterNamespace(true)
  			We agreed to wrap namespace definitions.
  		- AfterStruct(true)
  			We agreed to wrap struct definitions.
  		- AfterUnion(true)
  			We agreed to wrap union definitions.
  		- BeforeCatch(true)
  			We agreed to wrap before catch.
  		- BeforeElse(true)
  			We agreed to wrap before else.
	
	- IndentCaseLabels(true)
		We agreed to use the different indentation level as for the switch statement
	
	- PointerAlignment(Left)
		We agreed to align pointer to the left.

	- SpaceBeforeParens(Never)
		We agreed to never put a space before opening parentheses.

	- TabWidth(4)
		We agreed to use tabwidth of 4.

2.Resharper team-style

	-  Modified Naming Style
		- Class and Structs
			Swtiched to uppercamelcase.
		- Enums
			Switched to uppercamelcase.
		- Templates parameters
			Switched to uppercamelcase.
		- Parameters
			Switched to lowercamelcase.
		- Namespace
			Switched to uppercamelcase.
	
	-	Inspection Severity
		- Constraints Violations
			Switched to warnings.

	-	File header text
		Modifed and added our team style header.
	
	-	Code CleanUp
		Made new code cleanup for our team.


