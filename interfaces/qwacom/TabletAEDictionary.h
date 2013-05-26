/*----------------------------------------------------------------------------

FILE NAME
	TabletAEDictionary.h

PURPOSE
	Tablet Apple Event Constants

COPYRIGHT
	Copyright WACOM Technology, Inc.  2002 - 2010.
	All rights reserved.

----------------------------------------------------------------------------*/
#pragma once


#define kEndOfList					nil			// Nil terminator for variable argument list.

#define kWacomDriverSig				'WaCM'

//////////////////////////////////////////////////////////////////////////////
// Classes
//
//	Driver Target ('WaCM' application)                            
//		|                                                        
//		|                                                        
//		+--- cWTDDriver
//		|			|                                        
//		|			+--- cWTDTablet                                                        
//		|					|                                        
//		|					|--- cWTDExpressKey                    
//		|					|--- cWTDTouchRing                   
//		|					|--- cWTDTouchStrip                   
//		|					|                                        
//		|					|--- cWTDCustomizedApp (optional level)
//		|							|
//		|							|--- cWTDMenuItem                    
//		|							|--- cWTDPopItem                    
//		|							|--- cWTDTransducer                 
//		|									|
//		|									|--- cWTDButton                     
//		|									|--- cWTDRoller                     
//		|									|--- cWTDWheel                     
//		|                                                        
//		+--- cWTDContext                          
//					|                                        
//					|--- cWTDExpressKey                    
//					|--- cWTDTouchRing                   
//					|--- cWTDTouchStrip
                                                              

#define cWTDDriver					'Drvr'
#define cWTDTablet					'Tblt'
#define cWTDCustomizedApp			'Tcap'
#define cWTDTransducer				'Tran'
#define cWTDButton					'Butn'
#define cWTDWheel						'Whel'
#define cWTDRoller					'Roll'
#define cWTDMenuItem					'Mitm'
#define cWTDPopItem					'Pitm'
#define cWTDTouchRing				'WRnG'
#define cWTDExpressKey				'WExK'
#define cWTDTouchStrip				'WTcS'
#define cWTDControlFunction		'WCtF'



//////////////////////////////////////////////////////////////////////////////
// Properties

// Driver Properties
//      pVersion											// typeVersion r/o
#define pRate							'Drat'			// typeUInt16 r/o
#define pTabletDriverPrefs			'Tprf'			// used with a save event

// Tablet Properties
//      pVersion											// typeVersion r/o
//      pName												// typeUTF8Text r/o
#define pIsConnected					'Cnct'			// typeBoolean r/o (available 6.1.3/5.2.2 and later)
#define pTabletModel					'Taml'			// typeSInt16 r/o (available 6.1.3/5.2.2 and later)
#define pXDimension					'Xdim'			// typeSInt32 r/o
#define pYDimension					'Ydim'			// typeSInt32 r/o
#define pResolution					'Resl'			// typeSInt32 r/o
#define pTabletSize					'Tsiz'			// typeLongRectangle r/o (formerly pSize, which conflicted with Apple symbol)
#define pOrientation					'Oren'			// typeEnumerated (eOrientation) r/w
#define pTiltLevels					'Tlvl'			// typeSInt16 r/o

// Properties for Tablet Controls (TouchRing, ExpressKeys and TouchStrip)
#define pFunctionAvailable			'FunA'			// typeBoolean r/o
#define pControlMinValue			'CMin'			// typeUInt32 r/o
#define pControlMaxValue			'CMax'			// typeUInt32 r/o
#define pControlLocation			'CLoc'			// typeUInt32 r/o
#define pIconWidth					'IcnW'			// typeUInt32 r/o
#define pIconHeight					'IcnH'			// typeUInt32 r/o
#define pIconPixelFormat			'IcnF'			// typeUInt32 r/o
#define pOverrideFlag				'OvrF'			// typeBoolean r/w
#define pOverrideName				'ONme'			// typeUTF8Text r/w
#define pOverrideIcon				'OIcn'			// typeWTDData w/o

// Application Properties
#define pAppID							'Cacc'			// typeUInt32 r/o (4 char code)
#define pAppName						pName				// typeUTF8Text r/o

// Transducer Properties
//      pName												// typeUTF8Text r/o
#define pTiltSens						'Tsen'			// typeSInt16 r/w
#define pClickAssist					'Cass'			// typeBoolean r/w
#define pAssistDistance				'Dcad'			// typeUInt32 r/w
#define pAssistTime					'Dctm'			// typeUInt32 r/w
#define pType							'Type'			// typeUInt16 r/o
#define pSerialNumber				'tSSN'			// typeUInt32 r/o
#define pUniqueID						'UqId'			// typeLongPoint r/o
#define pDeviceID						'DvId'			// does not exist yet
#define pPositioningMode			'Pmde'			// typeEnumerated (ePositioningMode) r/w
#define pMapScreenArea				'Smap'			// typeQDRectangle r/w
#define pMapTabletArea				'Tmap'			// typeLongRectangle r/w
#define pMapDisplayNum				'MpTp'			// typeUInt32 w/o (write only)


// Button Properties
//      pName												// typeUTF8Text r/o
#define pButtonFunction				'Bfcn'			// typeEnumerated r/w
#define pPressLevels					'Plvl'			// typeSInt32 r/o
#define pClickPressure				'Cprs'			// typeSInt16 r/w
#define pPressureSen					'Psen'			// typeEnumerated (ePressureRange) r/w
#define pForceRange					'Frng'			// typeSInt16 r/w
#define pForceMin						'Fmin'			// typeSInt16 r/w
#define pForceMax						'Fmax'			// typeSInt16 r/w
#define pButtonKeys					'Bkey'			// typeUTF8Text r/w
#define pButtonRun					'Brun'			// typeUTF8Text r/w
#define pButtonModifiers			'Bmod'			// typeUInt32 r/w
#define pButtonMacro					'Bmac'			// does not exist yet

// Wheel Properties
#define pWheelFunction				'Wfcn'			// typeEnumerated (eWheelFunction) r/w
#define pWheelReverseDirection	'Wrvd'			// typeBoolean r/w
#define pWheelLinesPerNotch		'WLpN'			// typeSInt32 r/w
#define pWheelKeysUp					'Wkyu'			// typeUTF8Text r/w
#define pWheelKeysDown				'Wkyd'			// typeUTF8Text r/w

// Roller Properties
#define pRollerFunction				'Rfcn'			// typeEnumerated (eRollerFunction) r/w
#define pRollerSen					'Rsen'			// typeEnumerated (eRollerRange) r/w
#define pRollerReverseDirection	'Wrvd'			// typeBoolean r/w
#define pRollerKeysUp				'Rkyu'			// typeUTF8Text r/w
#define pRollerKeysDown				'Rkyd'			// typeUTF8Text r/w

// Menu Strip Properties
//      pName												// typeUTF8Text r/o
#define pMenuFunction				'Mfcn'			// typeEnumerated (eMenuFunction) r/w
#define pMenuKeys						'Mkey'			// typeUTF8Text r/w
#define pMenuMacro					pButtonMacro	// does not exist yet
#define pMenuRun						pButtonRun		// typeUTF8Text r/w

// Popup menu Properties
#define pPopupFunction				'Pfcn'			// typeEnumerated (ePopupFunction) r/w
#define pPopupKeys					'Pkey'			// typeUTF8Text r/w
#define pPopupMacro					pButtonMacro	// does not exist yet
#define pPopupRun						pButtonRun		// typeUTF8Text r/w



//////////////////////////////////////////////////////////////////////////////
// Enumerations

// Tablet Orentation Enums
#define eOrientation					'Ornt'
#define eOrientLandscape			'Land'
#define eOrientPortrait				'Port'
#define eOrientLandscapeFlipped	'Lflp'
#define eOrientPortraitFlipped	'Pflp'

// Cursor Positiioning Mode Enums
#define ePositioningMode			'Pmod'
#define ePositioningAbsolute		'Absl'
#define ePositioningRelative		'Rela'

// Tip Pressure Sensitivity Enums
#define ePressureRange				'Pcrv'
#define ePressureSoftest			'Pc00'
#define ePressureSofter				'Pc02'
#define ePressureSoft				'Pc03'
#define ePressureNormal				'Pc04'
#define ePressureFirm				'Pc05'
#define ePressureFirmer				'Pc06'
#define ePressureFirmest			'Pc08'

// Button Function Enums
#define eButtonFunction				'Bfcs'
#define eButtonFuncIgnore			'Ignr'
#define eButtonLeftClick			'Clic'
#define eButtonMiddleClick 		'Mclk'
#define eButtonRightClick			'Rclk'
#define eButtonLeftDoubleClick	'Dclk'
#define eButtonMiddleDoubleClick	'??B3'
#define eButtonRightDoubleClick	'??B4'
#define eButtonLeftClickLock		'Clok'
#define eButtonKeystrokes			'Keys'
#define eButtonModifiers			'Mods'
#define eButtonPressureHold 		'Phld'
#define eButtonModeToggle			'Mtgl'
#define eButtonMacro					'Mkro'
#define eButtonScreenMacro			'Smkr'
#define eButtonAutoErase			'Aers'
#define eButtonBumbleFree			'Eras'
#define eButtonEraseKeystroke 	'Ekey'
#define eButtonEraseModifier 		'Emod'
#define eButtonEraseMacro			'Emac'
#define eButtonButton4Click 		'4clk'
#define eButtonButton5Click 		'5clk'
#define eButtonMiddleClickLock 	'??B7'
#define eButtonRightClickLock 	'??B8'
#define eButtonRunApplication		'Runa'
#define eButtonToggleInkAnywhere 'InkT'
#define eButtonDisplayToggle		'bDiT'
#define eButtonPanScroll			'bPan'

#define eButtonBack					'Back'
#define eButtonForward				'Fwrd'
#define eButtonShowDesktop			'bSDT'
#define eButtonHelp					'Help'
#define eButtonRadialMenu			'RPM '
#define eButtonFinePoint			'bFPM'

// Wheel Function Enums
#define eWheelFunction				'Wfcs'
#define eWheelLineScroll			'Lscr'
#define eWheelPagecroll				'Pscr'
#define eWheelKeyScroll				'Kscr'
#define eWheelIgnored				eButtonFuncIgnore

// Roller Function Enums
#define eRollerFunction				'Rfcs'
#define eRollerZAxis					'Zee '
#define eRollerPressure				'Psur'
#define eRollerScroll				'Scrl'
#define eRoller15Button				'W15b'
#define eRollerKeyScroll			eWheelKeyScroll
#define eRollerIgnored				eButtonFuncIgnore

// Roller Sensitivity Range Enums
#define eRollerRange					'Rcrv'
#define eRangeMax						'Max '
#define eRangeMed						'Med '
#define eRangeMin						'Min '

// Tablet Menu Function Enums
#define eMenuFunction				'Mact'
#define eMenuFuncIgnored			eButtonFuncIgnore
#define eMenuKeystrokes				eButtonKeystrokes
#define eMenuMacro					eButtonMacro
#define eMenuRunApplication		eButtonRunApplication
#define eMenuAbsolute				ePositioningAbsolute
#define eMenuRelative				ePositioningRelative
#define eMenuQuickPoint				'Qpnt'
#define eMenuToggleInkAnywhere	eButtonToggleInkAnywhere
#define eMenuSoftPressure			ePressureSoft
#define eMenuNormalPressure		ePressureNormal
#define eMenuFirmPressure			ePressureFirm

// Popup Menu Function Enums
#define ePopupFunction				'Pfcs'
#define ePopupKeystrokes			eButtonKeystrokes
#define ePopupMacro					eButtonMacro
#define ePopupRunApplication		eButtonRunApplication
#define ePopupAbsolute				ePositioningAbsolute
#define ePopupRelative				ePositioningRelative

#define typeOSType					'OSTp'
#define typeWTDData					'WDtA'

//////////////////////////////////////////////////////////////////////////////
// Application Specific objects and events

#define cTabletEvent						'TblE'
#define cContext							'CTxt'

#define kAEWacomSuite					'Wacm'
#define eSendTabletEvent				'WSnd'
#define eEventProximity					'WePx'
#define eEventPointer					'WePt'

#pragma mark 
#pragma mark *** Context Attributes ***
// Context Properties
#define pContextPositiongMode			pPositioningMode	// does not exist yet
#define pContextMapScreenArea			pMapScreenArea		// typeQDRectangle
#define pContextMapTabletInputArea	pMapTabletArea 	// typeLongRectangle
#define pContextMapTabletOutputArea	'Tomp'				// typeLongRectangle
#define pContextMovesSystemCursor	'Mvsc'				// typeBoolean
#define pContextEnabled					'Cenb'				// typeBoolean
#define pContextTransducerType		'Ctdt' 				// does not exist yet
#define pContextTransducerSN			'Ctd#' 				// does not exist yet

// Context types. 
//		Blank:	
typedef enum AEContextType
{
	// Default: Tablet output areas are reset to full size, current transducers 
	//				are acquired, the context is marked non-customizable (control 
	//				panel mapping changes don't affect it), and the context is 
	//				enabled. 
	//
	//				This is the appropriate type for applications which want to 
	//				take over tablet mapping. 
	pContextTypeDefault				= 'Pos ',
	
	// Blank:	The context is enabled, but the rest of the work done in creating 
	//				a default context is skipped.
	//
	//				This is appropriate for contexts which only customize buttons, 
	//				and should still track other user changes in the control panel. 
	pContextTypeBlank					= 'Blnk'

} AEContextType;



//////////////////////////////////////////////////////////////////////////////
// Data Structures

// use with typeLongRectangle
typedef struct LongRect
{
   int32_t	top;
   int32_t	left;
   int32_t	bottom;
   int32_t	right;

} LongRect;


// Cross-process notifications
// control type
typedef enum eAETabletControlType
{
	eAETouchRing = 0,
	eAETouchStrip,
	eAEExpressKey
} eAETabletControlType;

// control position
typedef enum eAEControlPosition
{
	eAEControlPositionLeft = 0,
	eAEControlPositionRight,
	eAEControlPositionTop,
	eAEControlPositionBottom
} eAEControlPosition;


#define kWacomNotificationObject				"com.wacom.tabletdriver.hardware"
#define kWacomTabletControlNotification	"com.wacom.tabletdriver.hardware.controldata"
// keys used in data dictionary
#define kTabletNumberKey						"Tablet Number"	// 1-based system tablet id
#define kControlTypeKey							"Control Type"		// value is defined in ETabletControlType
#define kControlNumberKey						"Control Number"	// 1-based
#define kFunctionNumberKey						"Function Number"	// 1-based
#define kControlValueKey						"Control Value"	// value depends on the control type

