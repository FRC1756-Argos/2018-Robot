# 2018-Robot
Robot code for 2018 FRC Season

## Robot Configuration
There are configurations for "Competition", "Practice", and "Programming" chassis.  To select which to use, create a file named "/home/lvuser/RobotID" on the RoboRIO and create a line with one of the chassis names only.  If there are any non-whitespace characters before or after the robot ID, the configuration will default to "Competition".  If multiple lines have valid robot IDs, the first will be used.

### Drive Calibration
The autonomous execution accuracy is dependent on accurate wheel size calibration.  This is measured by the number of encoder ticks per inch.  The drive encoders produce 4096 ticks per revolution.

A simple strategy to determine the calibration values is as follows:

 1. On the dashboard, reset the encoder values
 2. Drive or push the robot a known distance
 3. Record the values for each side
 4. Repeat steps 1-3 several times to produce an average tick count
 5. Divide the average tick counts by the number of inches moved
 6. Record the averages to the calibration file on the roboRIO

The calibration file should be named "/home/lvuser/DriveEncoderCal.csv".  The header row of the CSV file should indicate the first column is for the left drive encoder and the second column is for the right drive encoder, but this row is not parsed by the robot code.  The second row should contain the left and right encoder calibration values calculated as described above; the units for calibration values are encoder ticks per inch driven.  Reboot roboRIO to load new calibration values.
