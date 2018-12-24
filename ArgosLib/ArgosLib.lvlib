<?xml version='1.0' encoding='UTF-8'?>
<Library LVVersion="17008000">
	<Property Name="NI.Lib.Icon" Type="Bin">&amp;Q#!!!!!!!)!"1!&amp;!!!-!%!!!@````]!!!!"!!%!!!(]!!!*Q(C=\&gt;7R=2MR%!81N=?"5Q&lt;/07RB7W!,&lt;'&amp;&lt;9+K1,7Q,&lt;)%N&lt;!NMA3X)DW?-RJ(JQ"I\%%Z,(@`BA#==ZB3RN;]28_,V7@PWW`:R`&gt;HV*SU_WE@\N_XF[3:^^TX\+2YP)D7K6;G-RV3P)R`ZS%=_]J'XP/5N&lt;XH,7V\SEJ?]Z#5P?=J4HP+5JTTFWS%0?=B$DD1G(R/.1==!IT.+D)`B':\B'2Z@9XC':XC':XBUC?%:HO%:HO&amp;R7QT0]!T0]!S0I4&lt;*&lt;)?=:XA-(]X40-X40-VDSGC?"GC4N9(&lt;)"D2,L;4ZGG?ZH%;T&gt;-]T&gt;-]T?.S.%`T.%`T.)^&lt;NF8J4@-YZ$S'C?)JHO)JHO)R&gt;"20]220]230[;*YCK=ASI2F=)1I.Z5/Z5PR&amp;)^@54T&amp;5TT&amp;5TQO&lt;5_INJ6Z;"[(H#&gt;ZEC&gt;ZEC&gt;Z$"(*ETT*ETT*9^B)HO2*HO2*(F.&amp;]C20]C2)GN4UE1:,.[:/+5A?0^NOS?UJ^3&lt;*\9B9GT@7JISVW7*NIFC&lt;)^:$D`5Q9TWE7)M@;V&amp;D,6;M29DVR]6#R],%GC47T9_/=@&gt;Z5V&gt;V57&gt;V5E&gt;V5(OV?^T[FTP?\`?YX7ZRP6\D=LH%_8S/U_E5R_-R$I&gt;$\0@\W/VW&lt;[_"\Y[X&amp;],0^^+,]T_J&gt;`J@_B_]'_.T`$KO.@I"XC-_N!!!!!!</Property>
	<Property Name="NI.Lib.SourceVersion" Type="Int">385908736</Property>
	<Property Name="NI.Lib.Version" Type="Str">1.0.0.0</Property>
	<Item Name="Config" Type="Folder">
		<Item Name="ConfigComponents" Type="Folder">
			<Item Name="TypeDefs" Type="Folder">
				<Item Name="Config_AnalogSensor.ctl" Type="VI" URL="../Config/ConfigComponents/TypeDefs/Config_AnalogSensor.ctl"/>
				<Item Name="Config_DigitalIO.ctl" Type="VI" URL="../Config/ConfigComponents/TypeDefs/Config_DigitalIO.ctl"/>
				<Item Name="Config_DoubleSolenoid.ctl" Type="VI" URL="../Config/ConfigComponents/TypeDefs/Config_DoubleSolenoid.ctl"/>
				<Item Name="Config_IMU.ctl" Type="VI" URL="../Config/ConfigComponents/TypeDefs/Config_IMU.ctl"/>
				<Item Name="Config_Motor.ctl" Type="VI" URL="../Config/ConfigComponents/TypeDefs/Config_Motor.ctl"/>
				<Item Name="Config_MotorCtrlType.ctl" Type="VI" URL="../Config/ConfigComponents/TypeDefs/Config_MotorCtrlType.ctl"/>
				<Item Name="Config_PIDParams.ctl" Type="VI" URL="../Config/ConfigComponents/TypeDefs/Config_PIDParams.ctl"/>
				<Item Name="Config_SerialPort.ctl" Type="VI" URL="../Config/ConfigComponents/TypeDefs/Config_SerialPort.ctl"/>
				<Item Name="Config_SingleSolenoid.ctl" Type="VI" URL="../Config/ConfigComponents/TypeDefs/Config_SingleSolenoid.ctl"/>
			</Item>
		</Item>
	</Item>
	<Item Name="Controls" Type="Folder">
		<Item Name="TypeDefs" Type="Folder">
			<Item Name="XBoxAxes_Type.ctl" Type="VI" URL="../Controls/TypeDefs/XBoxAxes_Type.ctl"/>
			<Item Name="XBoxButtons_Type.ctl" Type="VI" URL="../Controls/TypeDefs/XBoxButtons_Type.ctl"/>
		</Item>
		<Item Name="Swap_Joysticks.vi" Type="VI" URL="../Controls/Swap_Joysticks.vi"/>
		<Item Name="XBOX_Joystick_Name.vi" Type="VI" URL="../Controls/XBOX_Joystick_Name.vi"/>
	</Item>
	<Item Name="Drive" Type="Folder">
		<Item Name="MotorControl" Type="Folder">
			<Item Name="SRXConfig" Type="Folder">
				<Item Name="SRXConfigLimitSwitchSingle.vi" Type="VI" URL="../Drive/MotorControl/SRXConfig/SRXConfigLimitSwitchSingle.vi"/>
				<Item Name="SRXConfigVoltageCompensationSingle.vi" Type="VI" URL="../Drive/MotorControl/SRXConfig/SRXConfigVoltageCompensationSingle.vi"/>
			</Item>
			<Item Name="TypeDefs" Type="Folder">
				<Item Name="RobotDriveMotorSelectorEnum.ctl" Type="VI" URL="../Drive/MotorControl/TypeDefs/RobotDriveMotorSelectorEnum.ctl"/>
			</Item>
			<Item Name="MotorControllerOpen.vi" Type="VI" URL="../Drive/MotorControl/MotorControllerOpen.vi"/>
			<Item Name="MotorSetInvalidHandler.vi" Type="VI" URL="../Drive/MotorControl/MotorSetInvalidHandler.vi"/>
			<Item Name="RobotDriveMotors.vi" Type="VI" URL="../Drive/MotorControl/RobotDriveMotors.vi"/>
			<Item Name="RobotDriveOpen6MotorTalon.vi" Type="VI" URL="../Drive/MotorControl/RobotDriveOpen6MotorTalon.vi"/>
			<Item Name="RobotDriveOpen6MotorWithTalonSR.vi" Type="VI" URL="../Drive/MotorControl/RobotDriveOpen6MotorWithTalonSR.vi"/>
			<Item Name="RobotDriveOpen6MotorWithTalonSRX.vi" Type="VI" URL="../Drive/MotorControl/RobotDriveOpen6MotorWithTalonSRX.vi"/>
			<Item Name="WPI_RobotDriveGetMotorControlReference_6Motor.vi" Type="VI" URL="../Drive/MotorControl/WPI_RobotDriveGetMotorControlReference_6Motor.vi"/>
		</Item>
		<Item Name="ArcadeDrive.vi" Type="VI" URL="../Drive/ArcadeDrive.vi"/>
		<Item Name="Argo_Drive.vi" Type="VI" URL="../Drive/Argo_Drive.vi"/>
		<Item Name="Auto_PID_Drive.vi" Type="VI" URL="../Drive/Auto_PID_Drive.vi"/>
		<Item Name="Hypotenuse_Control.vi" Type="VI" URL="../Drive/Hypotenuse_Control.vi"/>
		<Item Name="Saturation_Powers.vi" Type="VI" URL="../Drive/Saturation_Powers.vi"/>
		<Item Name="Shifters.vi" Type="VI" URL="../Drive/Shifters.vi"/>
		<Item Name="Turning_Power_Mode.vi" Type="VI" URL="../Drive/Turning_Power_Mode.vi"/>
	</Item>
	<Item Name="Math" Type="Folder">
		<Item Name="DeltaAngle_Degrees.vi" Type="VI" URL="../Math/DeltaAngle_Degrees.vi"/>
		<Item Name="DotProduct.vi" Type="VI" URL="../Math/DotProduct.vi"/>
		<Item Name="Hypotenuse.vi" Type="VI" URL="../Math/Hypotenuse.vi"/>
		<Item Name="Modulus.vim" Type="VI" URL="../Math/Modulus.vim"/>
		<Item Name="NumToPercent.vi" Type="VI" URL="../Math/NumToPercent.vi"/>
		<Item Name="PointLineDistance.vi" Type="VI" URL="../Math/PointLineDistance.vi"/>
		<Item Name="TangentLineAngle.vi" Type="VI" URL="../Math/TangentLineAngle.vi"/>
		<Item Name="VectorLength.vi" Type="VI" URL="../Math/VectorLength.vi"/>
	</Item>
	<Item Name="Miscellaneous" Type="Folder">
		<Item Name="Arbitor" Type="Folder">
			<Item Name="ArbitorSpecializations" Type="Folder">
				<Item Name="Arbitor_Bool.vi" Type="VI" URL="../Miscellaneous/Arbitor/ArbitorSpecializations/Arbitor_Bool.vi"/>
				<Item Name="Arbitor_Float.vi" Type="VI" URL="../Miscellaneous/Arbitor/ArbitorSpecializations/Arbitor_Float.vi"/>
				<Item Name="Arbitor_Int.vi" Type="VI" URL="../Miscellaneous/Arbitor/ArbitorSpecializations/Arbitor_Int.vi"/>
				<Item Name="Arbitor_Var.vi" Type="VI" URL="../Miscellaneous/Arbitor/ArbitorSpecializations/Arbitor_Var.vi"/>
			</Item>
			<Item Name="Arbitor.vi" Type="VI" URL="../Miscellaneous/Arbitor/Arbitor.vi"/>
		</Item>
		<Item Name="AutoDoc" Type="Folder">
			<Item Name="HTML Helpers" Type="Folder">
				<Item Name="MakeHTML.vi" Type="VI" URL="../Miscellaneous/AutoDoc/HTML Helpers/MakeHTML.vi"/>
				<Item Name="MakeHTMLBody.vi" Type="VI" URL="../Miscellaneous/AutoDoc/HTML Helpers/MakeHTMLBody.vi"/>
				<Item Name="MakeHTMLHeader.vi" Type="VI" URL="../Miscellaneous/AutoDoc/HTML Helpers/MakeHTMLHeader.vi"/>
				<Item Name="MakeHTMLLink.vi" Type="VI" URL="../Miscellaneous/AutoDoc/HTML Helpers/MakeHTMLLink.vi"/>
				<Item Name="MakeHTMLList.vi" Type="VI" URL="../Miscellaneous/AutoDoc/HTML Helpers/MakeHTMLList.vi"/>
				<Item Name="MakeHTMLParagraph.vi" Type="VI" URL="../Miscellaneous/AutoDoc/HTML Helpers/MakeHTMLParagraph.vi"/>
				<Item Name="TagHTMLContent.vi" Type="VI" URL="../Miscellaneous/AutoDoc/HTML Helpers/TagHTMLContent.vi"/>
			</Item>
			<Item Name="AutoDoc.vi" Type="VI" URL="../Miscellaneous/AutoDoc/AutoDoc.vi"/>
			<Item Name="GenerateNavigationPages.vi" Type="VI" URL="../Miscellaneous/AutoDoc/GenerateNavigationPages.vi"/>
		</Item>
		<Item Name="TypeDefs" Type="Folder">
			<Item Name="ArgoDriveJoystickMap.ctl" Type="VI" URL="../Miscellaneous/TypeDefs/ArgoDriveJoystickMap.ctl"/>
			<Item Name="LookUpTableParameters.ctl" Type="VI" URL="../Miscellaneous/TypeDefs/LookUpTableParameters.ctl"/>
			<Item Name="MotorLimitPositions_Type.ctl" Type="VI" URL="../Miscellaneous/TypeDefs/MotorLimitPositions_Type.ctl"/>
			<Item Name="ReachTargetState_Type.ctl" Type="VI" URL="../Miscellaneous/TypeDefs/ReachTargetState_Type.ctl"/>
		</Item>
		<Item Name="Assisted Turning.vi" Type="VI" URL="../Miscellaneous/Assisted Turning.vi"/>
		<Item Name="ChangeTimer.vi" Type="VI" URL="../Miscellaneous/ChangeTimer.vi"/>
		<Item Name="DBReadStringAsNumber.vi" Type="VI" URL="../Miscellaneous/DBReadStringAsNumber.vi"/>
		<Item Name="DrawLine.vi" Type="VI" URL="../Miscellaneous/DrawLine.vi"/>
		<Item Name="Lookup_Table.vi" Type="VI" URL="../Miscellaneous/Lookup_Table.vi"/>
		<Item Name="Motor_Limit.vi" Type="VI" URL="../Miscellaneous/Motor_Limit.vi"/>
		<Item Name="Reach_Target.vi" Type="VI" URL="../Miscellaneous/Reach_Target.vi"/>
		<Item Name="time_delta.vi" Type="VI" URL="../Miscellaneous/time_delta.vi"/>
	</Item>
	<Item Name="Path Planning" Type="Folder">
		<Item Name="TestSupport" Type="Folder">
			<Item Name="DrawCircle.vi" Type="VI" URL="../Path Planning/TestSupport/DrawCircle.vi"/>
			<Item Name="DrawPolygon2D.vi" Type="VI" URL="../Path Planning/TestSupport/DrawPolygon2D.vi"/>
		</Item>
		<Item Name="TypeDefs" Type="Folder">
			<Item Name="Point2D.ctl" Type="VI" URL="../Path Planning/TypeDefs/Point2D.ctl"/>
			<Item Name="Polygon2D.ctl" Type="VI" URL="../Path Planning/TypeDefs/Polygon2D.ctl"/>
		</Item>
		<Item Name="FindLinePolygonIntersectionFaces.vi" Type="VI" URL="../Path Planning/FindLinePolygonIntersectionFaces.vi"/>
		<Item Name="GetPolygonPointsBetweenSides.vi" Type="VI" URL="../Path Planning/GetPolygonPointsBetweenSides.vi"/>
		<Item Name="PathLength.vi" Type="VI" URL="../Path Planning/PathLength.vi"/>
		<Item Name="PointInPolygon.vi" Type="VI" URL="../Path Planning/PointInPolygon.vi"/>
		<Item Name="RedistributePathPoints.vi" Type="VI" URL="../Path Planning/RedistributePathPoints.vi"/>
		<Item Name="RedistributePathPointsVariable.vi" Type="VI" URL="../Path Planning/RedistributePathPointsVariable.vi"/>
		<Item Name="ReRouteAroundPolygon.vi" Type="VI" URL="../Path Planning/ReRouteAroundPolygon.vi"/>
	</Item>
	<Item Name="Sensors" Type="Folder">
		<Item Name="MultiCamera" Type="Folder">
			<Item Name="SwitchingCameraSendImagesToPCLoop.vi" Type="VI" URL="../Sensors/MultiCamera/SwitchingCameraSendImagesToPCLoop.vi"/>
			<Item Name="SwitchingHTTPCameraResponder.vi" Type="VI" URL="../Sensors/MultiCamera/SwitchingHTTPCameraResponder.vi"/>
		</Item>
		<Item Name="Ultrasonic" Type="Folder">
			<Item Name="TypeDefs" Type="Folder">
				<Item Name="UltrasonicParameters_Type.ctl" Type="VI" URL="../Sensors/Ultrasonic/TypeDefs/UltrasonicParameters_Type.ctl"/>
			</Item>
			<Item Name="Ultrasonic_Get_Range.vi" Type="VI" URL="../Sensors/Ultrasonic/Ultrasonic_Get_Range.vi"/>
			<Item Name="Ultrasonic_Open.vi" Type="VI" URL="../Sensors/Ultrasonic/Ultrasonic_Open.vi"/>
			<Item Name="Ultrasonic_Ref_Get.vi" Type="VI" URL="../Sensors/Ultrasonic/Ultrasonic_Ref_Get.vi"/>
			<Item Name="Ultrasonic_Ref_Set.vi" Type="VI" URL="../Sensors/Ultrasonic/Ultrasonic_Ref_Set.vi"/>
		</Item>
		<Item Name="DriveEncoderRevToDist.vi" Type="VI" URL="../Sensors/DriveEncoderRevToDist.vi"/>
		<Item Name="PotRead.vi" Type="VI" URL="../Sensors/PotRead.vi"/>
		<Item Name="UltraRead.vi" Type="VI" URL="../Sensors/UltraRead.vi"/>
		<Item Name="YoYoRead.vi" Type="VI" URL="../Sensors/YoYoRead.vi"/>
	</Item>
	<Item Name="Signal Processing" Type="Folder">
		<Item Name="Filters" Type="Folder">
			<Item Name="95-5 Filter.vi" Type="VI" URL="../Signal Processing/Filters/95-5 Filter.vi"/>
			<Item Name="Median Filter.vi" Type="VI" URL="../Signal Processing/Filters/Median Filter.vi"/>
		</Item>
		<Item Name="TypeDefs" Type="Folder">
			<Item Name="EdgeDetector_Type.ctl" Type="VI" URL="../Signal Processing/TypeDefs/EdgeDetector_Type.ctl"/>
		</Item>
		<Item Name="Debounce.vi" Type="VI" URL="../Signal Processing/Debounce.vi"/>
		<Item Name="EdgeDetector.vi" Type="VI" URL="../Signal Processing/EdgeDetector.vi"/>
		<Item Name="HistoricMaxMagnitude.vi" Type="VI" URL="../Signal Processing/HistoricMaxMagnitude.vi"/>
		<Item Name="Latch.vi" Type="VI" URL="../Signal Processing/Latch.vi"/>
		<Item Name="Rate_Limit.vi" Type="VI" URL="../Signal Processing/Rate_Limit.vi"/>
		<Item Name="Timed_DeBounce.vi" Type="VI" URL="../Signal Processing/Timed_DeBounce.vi"/>
	</Item>
	<Item Name="LICENSE" Type="Document" URL="../LICENSE"/>
</Library>
