# Network Tables Variables

The following variables are used to communicate between the robot and the dashboard application:

| Variable Name | Data Type | Description |
| ------------- | --------- | ----------- |
| /Argos/Auto/StartingPositions | string array | List of available starting positions |
| /Argos/Auto/SelectedStartingPosition | uint16 | Index within StartingPositions selected by dashboard |
| /Argos/Auto/ReloadRoutines | bool | Robot reloads routines from CSV files on rising edge of ReloadRoutines |
| /Argos/Auto/Routines | string array | List of available routines from the selected starting position |
| /Argos/Auto/Selection_LLL | uint16 | Index within Routines selected by dashboard if field configuration is LLL |
| /Argos/Auto/Selection_LRL | uint16 | Index within Routines selected by dashboard if field configuration is LRL |
| /Argos/Auto/Selection_RRR | uint16 | Index within Routines selected by dashboard if field configuration is RRR |
| /Argos/Auto/Selection_RRR | uint16 | Index within Routines selected by dashboard if field configuration is RRR |
| /Argos/Auto/Armed_LLL | string | Routine name to be executed if field configuration is LLL |
| /Argos/Auto/Armed_LRL | string | Routine name to be executed if field configuration is LRL |
| /Argos/Auto/Armed_RRR | string | Routine name to be executed if field configuration is RRR |
| /Argos/Auto/Armed_RRR | string | Routine name to be executed if field configuration is RRR |
| /Argos/Auto/AutoInTeleop | bool | When true, robot will run an autonomous routine in teleop mode |
| /Argos/Diagnostics/ArmPositionX | double | X coordinate of claw |
| /Argos/Diagnostics/ArmPositionY | double | Y coordinate of claw |
| /Argos/Diagnostics/ArmHomeSuccess | bool | True once arm has successfully completed homing sequence |
| /Argos/Diagnostics/ArmHomeFailure | bool | True if arm fails homing sequence |
| /Argos/Diagnostics/ArmExtendLimit | bool | True if arm extension limit switch is triggered |
| /Argos/Diagnostics/ArmRotateLimit | bool | True if arm rotation limit switch is triggered |
| /Argos/Diagnostics/StartPositionActive | string | Currently active autonomous routine |
| /Argos/Diagnostics/AutoRoutineActive | string | Currently active autonomous routine |
| /Argos/Diagnostics/AutoControlActive | bool | True when autonomous controller is controlling robot |
| /Argos/Diagnostics/ArmControlMode | string | Current control mode of arm |
| /Argos/Calibration/EncoderDriveLeft | int32 | Left drive encoder tick count |
| /Argos/Calibration/EncoderDriveRight | int32 | Right drive encoder tick count |
