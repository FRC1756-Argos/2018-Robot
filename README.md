# 2018-Robot
Robot code for 2018 FRC Season

## Documentation
Documentation may be automatically generated for this project using the AutoDoc.vi tool.  The most recently published documentation is available on this project's [GitHub Pages site](https://frc1756-argos.github.io/2018-Robot/).

## Notable Features
+ Multiple robot configurations to enable common software on all robot platforms
    + Support for different motor controller addresses and types
    + Support for different tuning values for closed loop control systems
    + Support for different motor controller configurations (e.g. brake mode)
    + Support for disabling motors on configurations with limited hardware installed
+ Auto homing of encoder positions on startup
    + Arm rotation, arm extension, and selfie stick all retract to known locations when robot is first enabled to ensure known locations for robot implements
    + Motor stall and timeout detection to handle sensor failure
    + Homing status provided to operator on dashboard
+ Rotating and extending arm with custom path planning and motion profiling
    + Setpoints for hold position, switch, low scale, high scale, and climbing
    + Path planning performed in Cartesian coordinate space (x,y) to optimize path lengths and converts to actuator coordinate space (angle, extension) when commanding motors
    + Paths constrained by avoidance polygon to keep claw inside maximum frame perimeter extension and prevent collisions with other robot components
    + Paths constrained by arm physical limits to prevent over extension or under extension
    + All paths generated on-demand to move from current position to commanded position
    + Path velocities smoothed using s-curve motion profile to provide smooth speed ramping between positions.  This is based on the motion profile generator Excel spreadsheet provided by Cross The Road Electronics
    + Uses Talon SRX motion profiles to synchronize motion of rotation and extension motors
    + Visualization in VI front panel to see path plans and executed path
+ Extending camera "selfie stick" with automatic camera switching
    + One web camera fixed to robot in aimed at a low height for power cube acquisition and switch, and one web camera actuates between a medium and high height for scale placement
    + Selfie stick raises and lowers automatically according to arm setpoints
    + Motion controlled by Talon SRX motion magic
    + RoboRIO provides each camera feed separately or offers an auto-sequenced mode where the dashboard footage switches camera source while monitoring the same video stream
        + Sequencer enables fast switching between camera feeds, lower bandwidth requirements, and lower processing costs on the RoboRIO
        + Auto sequenced feed controlled by robot arm position
+ Spline-based drive path planning
    + Utilizes [Pathfinder](https://github.com/JacisNonsense/Pathfinder) to generate path profiles
    + All processing performed on the RoboRIO
+ CSV-based autonomous script creation
    + Further documentation available in [AutoRoutines](PowerUpSrc/Autonomous/AutoRoutines/README.md)
    + Creating a new autonomous routine or modifying an existing routine only requires uploading a file to the RoboRIO via FTP
    + Autonomous sequencer uses routine steps to generate all necessary drive paths and synchronizes arm and intake actions along the drive path
    + RoboRIO generates images of autonomous routine paths that we used to create a "playbook" to share during pre-match strategy planning
    + All routines are pre-processed during application startup to enable minimal delay on match start
+ Fully-featured operator station dashboard
    + Auto-sequenced camera footage
    + Sensor homing status indicators
    + Visualization for robot arm position
    + Indicators for arm control state (manual, operator assist), autonomous status, limit switch states, and armed autonomous routines
    + Drive encoder readouts for diagnostics and testing
    + Auto-populating autonomous routine selector
        + Dashboard displays all available starting positions and routines for those positions based on the files loaded on the RoboRIO
        + Operator selects which routine to run for each of the four possible field configurations
        + Controls available to re-load routine lists if new files are uploaded during runtime without requiring the application to restart
        + Controls available to run autonomous routines during teleop mode for extra validation during practice matches
+ On-demand, asynchronous onboard path planning
    + Drive and arm path planners are implemented as asynchronous services accessed through message queues
    + This helps ensure computationally-heavy path planning does not stall high-frequency control loops that handle manual operator controls (such as driving and intake)
    + All operator assist functions can be interrupted and canceled by manual controls
+ Individually addressable RGB LED strips
    + LED strips controlled by Arduino Mega
    + RoboRIO sends robot state information to Arduino over I2C
    + Multiple lighting modes to indicate alliance, robot control mode (disabled, teleop, autonomous, climbing), and arm position
    + FFT audio analysis on Arduino for flame visualization lighting
+ [Automatic code documentation](#Documentation)

## Dependencies
+ LabVIEW 2017 with 2018 FRC Updates
+ Cross the Road Electronics Hero Toolsuite [v5.3.1.0](http://www.ctr-electronics.com/downloads/installers/CTRE%20Phoenix%20Framework%20v5.3.1.0.zip)

## Robot Configuration
There are configurations for "Competition", "Practice", "Programming", and "Demo" chassis.  To select which to use, create a file named "/home/lvuser/RobotID" on the RoboRIO and create a line with one of the chassis names only.  If there are any non-whitespace characters before or after the robot ID, the configuration will default to "Competition".  If multiple lines have valid robot IDs, the first will be used.

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

## Special Thanks (in no particular order)
+ [Chris Gerth](https://github.com/gerth2) and [Robot Cassarole (FRC team 1736)](https://github.com/RobotCasserole1736) for their help designing the autonomous drive path follower we used to great success
+ [Jaci Brunning](https://github.com/JacisNonsense) for developing and supporting the [Pathfinder project](https://github.com/JacisNonsense/Pathfinder)
+ [William Toth](https://github.com/willtoth) for developing the LabVIEW wrappers for Pathfinder
+ [Juan Chong](https://github.com/juchong) for developing and maintaining [ADIS16448 IMU drivers](https://github.com/juchong/ADIS16448-RoboRIO-Driver) for the RoboRIO
+ Our sponsors for the 2018 season.  Thank you for your continued support!
    + [Caterpillar](https://www.caterpillar.com)
    + [Limestone Community High School](http://limestone.k12.il.us)
    + [SC2](http://www.sc2services.com)

## License
This software is licensed under the [GNU General Public License v3](http://www.gnu.org/licenses/#GPL).  If you would like to use this software under the terms of a different license agreement, please [contact us](mailto:1756argos1756@limestone310.org).
