# Autonomous Routine Scripts

Here are our autonomous routines as steps saved in comma-separated value format.

## Naming Convention

To make a new autonomous routine, the file name should follow the following format:
```
    <StartingPosition>.<RoutineName_1>.<RoutineName_2>.<...>.<RoutineName_n>.csv
```
`StartingPosition` is one of:
 + "Left": Left starting position when facing center of field from alliance station.  Aligned with left bumper outside edge at left edge of left player station
 + "Center": Center starting position.  Aligned with left bumper outside edge at edge of exchange zone
 + "Right": Right starting position when facing center of field from alliance station.  Aligned with right bumper outside edge at right edge of right player station
 + "Any": Routines that can be run from any position

`RoutineName_n` is a series of identifiers for the routine.  Underscores will be replaced with spaces when displayed.  Periods separating routine names will be replaced with arrows ("`->`") when displayed.  This should indicate a sequence of events executed in the routine

## File Format

Each file contains rows defining autonomous steps for the robot to execute.  The first row has headers to make the file more readable for the author when opened in Excel or another spreadsheet program.  You may also edit the file in a text editor such as SublimeText or Notepad++.  While Notepad may work, I have not tested it thoroughly and using notepad may lead to inconsistent line endings.

The columns are as follows (in the listed order):

 1. "WaypointType": Type of step.  Enumerated value should be one of the following (input the number only):
   + 0: Pathfinder endpoint: Start or end of a spline path
   + 1: Pathfinder waypoint: Internal waypoint of a spline path
   + 2: Zero-radius turn endpoint: Start or end angle for an in-place turn
   + 3: Stationary: Robot will not move, but arm, claw or intake may be activated
   + 4: Vision assist endpoint: Start or end position that will utilize camera for path adjustment
   + 5: Stop: Ends autonomous routine.  Should always be called at the end of a routine to ensure the robot does not continue to another set of actions
 2. "Waypoint.x": X position of center of robot in inches.  X axis is 0 at your alliance's player station and increases toward field centerline
 3. "Waypoint.y": Y position of center of robot in inches.  Y axis is 0 at the right side of the field when observed from your player station and increases to the left side of the field
 4. "Waypoint.angle": Direction of robot's front in degrees where 0 is facing along the positive X axis and increasing angle with counter clockwise rotation until 360 degrees
 5. "WaitTime": Milliseconds to wait at end of this step (ignored on intermediate waypoints) before advancing to next step
 6. "ArmPosition": Arm target position.  Enumerated value should be one of the following (input the number only):
   + 0: Hold position: Arm all the way down
   + 1: Switch position: Lowest height to place in switch
   + 2: Low scale position: Place in scale when we have possession
   + 3: High scale position: Place in scale when opposing alliance has possession
   + 4: Climb position: Climbing hook deploy position
   + 5: Back place position: Place in scale behind robot
 7. "IntakeState": Enumerated value should be one of the following (input the number only):
   + 0: Stop: Intake retracted and open with motors off
   + 1: Forward: Intake extended and closed with motors set to pull in cube
   + 2: Reverse: Intake retracted and closed with motors set to expel cube
   + 3: Forward Open: Intake extended and open with motors set to pull in cube
 8. "ClawOpen": `1` for claw open, `0` for claw closed
 9. "ArmOffsetTime": Milliseconds before drive end the arm should finish motion.  Recommend at least 1000ms before switch and at least 2000ms before scale
 10. "TimedClawRelease": Milliseconds before step end the claw should transition to new state.  `0` indicates use new state for the entire step.

## Deploying Routines

FTP into the robot at `ftp://roborio-1756-frc.local` and copy the files to `/home/lvuser/AutoRoutines/`.  LabVIEW will load the files on next robot code startup.
