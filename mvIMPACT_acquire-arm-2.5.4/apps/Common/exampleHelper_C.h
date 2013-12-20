//-----------------------------------------------------------------------------
#ifndef exampleHelper_CH
#define exampleHelper_CH exampleHelper_CH
//-----------------------------------------------------------------------------
#include <mvDeviceManager/Include/mvDeviceManager.h>

#define END_APPLICATION										\
	printf( "Press any key to end the application.\n" );	\
	getchar();												\
	return 0;												\

int        getIntValFromSTDIn( void );
int        getPropI( HOBJ hProp, int index );
void       setPropI( HOBJ hProp, int value, int index );
int64_type getPropI64( HOBJ hProp, int index );
void       setPropI64( HOBJ hProp, int64_type value, int index );
void*      getPropP( HOBJ hProp, int index );
void       setPropP( HOBJ hProp, void* value, int index );

HOBJ getDriverList( HDRV hDrv, const char* pListName, const char* pAddListName, TDMR_ListType type );
HOBJ getDriverProperty( HDRV hDrv, const char* pPropName, const char* pAddListName, TDMR_ListType type );
HOBJ getDriverMethod( HDRV hDrv, const char* pMethodName, const char* pAddListName, TDMR_ListType type );
HOBJ getDeviceProp( HDEV hDev, const char* pPropName );
HOBJ getInfoProp( HDRV hDrv, const char* pPropName );
HOBJ getIOSubSystemProp( HDRV hDrv, const char* pPropName );
HOBJ getRequestCtrlProp( HDRV hDrv, const char* pRequestCtrlName, const char* pPropName );
HOBJ getRequestProp( HDRV hDrv, int requestNr, const char* pPropName );
HOBJ getSettingProp( HDRV hDrv, const char* pSettingName, const char* pPropName );
HOBJ getSettingMethod( HDRV hDrv, const char* pSettingName, const char* pMethodName );
HOBJ getStatisticProp( HDRV hDrv, const char* pPropName );
HOBJ getSystemSettingProp( HDRV hDrv, const char* pPropName );

/// \brief Reads the value of a feature as a string
/// \note
/// pBuf must be freed by the caller
TPROPHANDLING_ERROR getStringValue( HOBJ hObj, char** pBuf, int index );
/// \brief Reads the value of a feature as a string
/// \note
/// pBuf must be freed by the caller
TPROPHANDLING_ERROR getValueAsString( HOBJ hObj, const char* pFormat, char** pBuf, int index );
void modifyEnumPropertyI( HDRV hDrv, const char* pSettingName, const char* pPropName );
/// \brief Shows how to read the translation dictionary of an integer property and returns all the
/// integer values in the dictionary.
///
/// \note
/// \a pDictValues must be freed by the caller.
TPROPHANDLING_ERROR readTranslationDictValuesI( HOBJ hObj, int** pDictValues, unsigned int* pDictValCnt );
/// \brief Sets an enumerated integer property to a certain value if this value is supported by
/// the property.
void conditionalSetPropI( HOBJ hObj, int value );

#endif // exampleHelper_CH
