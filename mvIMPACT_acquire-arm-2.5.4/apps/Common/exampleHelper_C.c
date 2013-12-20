//-----------------------------------------------------------------------------
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "exampleHelper_C.h"

#define BUF_SIZE (32)
#define BUF_SIZE_LARGE (256)

//-----------------------------------------------------------------------------
int getIntValFromSTDIn( void )
//-----------------------------------------------------------------------------
{
	int value;
	int conversionResult = 0;

#if defined(_MSC_VER) && (_MSC_VER >= 1400) // is at least VC 2005 compiler?
	conversionResult = scanf_s( "%d", &value );
#else
	conversionResult = scanf( "%d", &value );
#endif // #if defined(_MSC_VER) && (_MSC_VER >= 1400)
	if( conversionResult != 1 )
	{
		printf( "Conversion error: Expected: 1, conversion result: %d.\n", conversionResult );
	}
	return value;
}

//-----------------------------------------------------------------------------
int getPropI( HOBJ hProp, int index )
//-----------------------------------------------------------------------------
{
	int value = 0;
	TPROPHANDLING_ERROR result = PROPHANDLING_NO_ERROR;

	if( ( result = OBJ_GetI( hProp, &value, index ) ) != PROPHANDLING_NO_ERROR )
	{
		printf( "getPropI: Failed to read property value(%s).\n", DMR_ErrorCodeToString( result ) );
		exit( 42 );
	}
	return value;
}

//-----------------------------------------------------------------------------
void setPropI( HOBJ hProp, int value, int index )
//-----------------------------------------------------------------------------
{
	TPROPHANDLING_ERROR result = PROPHANDLING_NO_ERROR;

	if( ( result = OBJ_SetI( hProp, value, index ) ) != PROPHANDLING_NO_ERROR )
	{
		printf( "setPropI: Failed to write property value(%s).\n", DMR_ErrorCodeToString( result ) );
		exit( 42 );
	}
}

//-----------------------------------------------------------------------------
int64_type getPropI64( HOBJ hProp, int index )
//-----------------------------------------------------------------------------
{
	int64_type value = 0;
	TPROPHANDLING_ERROR result = PROPHANDLING_NO_ERROR;

	if( ( result = OBJ_GetI64( hProp, &value, index ) ) != PROPHANDLING_NO_ERROR )
	{
		printf( "getPropI: Failed to read property value(%s).\n", DMR_ErrorCodeToString( result ) );
		exit( 42 );
	}
	return value;
}

//-----------------------------------------------------------------------------
void setPropI64( HOBJ hProp, int64_type value, int index )
//-----------------------------------------------------------------------------
{
	TPROPHANDLING_ERROR result = PROPHANDLING_NO_ERROR;

	if( ( result = OBJ_SetI64( hProp, value, index ) ) != PROPHANDLING_NO_ERROR )
	{
		printf( "setPropI: Failed to write property value(%s).\n", DMR_ErrorCodeToString( result ) );
		exit( 42 );
	}
}

//-----------------------------------------------------------------------------
void* getPropP( HOBJ hProp, int index )
//-----------------------------------------------------------------------------
{
	void* value = 0;
	TPROPHANDLING_ERROR result = PROPHANDLING_NO_ERROR;

	if( ( result = OBJ_GetP( hProp, &value, index ) ) != PROPHANDLING_NO_ERROR )
	{
		printf( "getPropP: Failed to read property value(%s).\n", DMR_ErrorCodeToString( result ) );
		exit( 42 );
	}
	return value;
}

//-----------------------------------------------------------------------------
void setPropP( HOBJ hProp, void* value, int index )
//-----------------------------------------------------------------------------
{
	TPROPHANDLING_ERROR result = PROPHANDLING_NO_ERROR;

	if( ( result = OBJ_SetP( hProp, value, index ) ) != PROPHANDLING_NO_ERROR )
	{
		printf( "setPropP: Failed to write property value(%s).\n", DMR_ErrorCodeToString( result ) );
		exit( 42 );
	}
}

//-----------------------------------------------------------------------------
// This function will try to obtain the handle to a certain driver feature
HOBJ getDriverFeature( HDRV hDrv, const char* pFeatureName, const char* pFeatureType, const char* pAddListName, TDMR_ListType type, unsigned int searchMode )
//-----------------------------------------------------------------------------
{
	TDMR_ERROR dmrResult = DMR_NO_ERROR;
	HOBJ hObj = INVALID_ID;
	HLIST baseList = INVALID_ID;

	// try to loacte the base list for these property
	if( ( dmrResult = DMR_FindList( hDrv, pAddListName, type, 0, &baseList ) ) == DMR_NO_ERROR )
	{
		// try to loacte the property
		TPROPHANDLING_ERROR objResult;
		if( ( objResult = OBJ_GetHandleEx( baseList, pFeatureName, &hObj, searchMode, INT_MAX ) ) != PROPHANDLING_NO_ERROR )
		{
			printf( "OBJ_GetHandleEx for %s failed: %d Handle: %d. This %s might not be supported by this device\n", pFeatureName, objResult, hObj, pFeatureType );
		}
	}
	else
	{
		printf( "DMR_FindList failed: %d. Lists of type %d are not available for this device\n", dmrResult, type );
	}
	return hObj;
}

//-----------------------------------------------------------------------------
// This function will try to obtain the handle to a certain driver feature list
HOBJ getDriverList( HDRV hDrv, const char* pListName, const char* pAddListName, TDMR_ListType type )
//-----------------------------------------------------------------------------
{
	return getDriverFeature( hDrv, pListName, "list", pAddListName, type, smIgnoreProperties | smIgnoreMethods );
}

//-----------------------------------------------------------------------------
// This function will try to obtain the handle to a certain driver property
HOBJ getDriverProperty( HDRV hDrv, const char* pPropName, const char* pAddListName, TDMR_ListType type )
//-----------------------------------------------------------------------------
{
	return getDriverFeature( hDrv, pPropName, "property", pAddListName, type, smIgnoreLists | smIgnoreMethods );
}

//-----------------------------------------------------------------------------
// This function will try to obtain the handle to a certain driver property
HOBJ getDriverMethod( HDRV hDrv, const char* pPropName, const char* pAddListName, TDMR_ListType type )
//-----------------------------------------------------------------------------
{
	return getDriverFeature( hDrv, pPropName, "method", pAddListName, type, smIgnoreProperties | smIgnoreLists );
}

//-----------------------------------------------------------------------------
HOBJ getDeviceProp( HDEV hDev, const char* pPropName )
//-----------------------------------------------------------------------------
{
	TPROPHANDLING_ERROR objResult;
	HOBJ hProp;

	// try to loacte the property
	if( ( objResult = OBJ_GetHandleEx( hDev, pPropName, &hProp, 0, -1 ) ) != PROPHANDLING_NO_ERROR )
	{
		printf( "OBJ_GetHandleEx failed: %d Handle: %d\n", objResult, hProp );
	}
	return hProp;
}

//-----------------------------------------------------------------------------
HOBJ getInfoProp( HDRV hDrv, const char* pPropName )
//-----------------------------------------------------------------------------
{
	return getDriverProperty( hDrv, pPropName, 0, dmltInfo );
}

//-----------------------------------------------------------------------------
HOBJ getIOSubSystemProp( HDRV hDrv, const char* pPropName )
//-----------------------------------------------------------------------------
{
	return getDriverProperty( hDrv, pPropName, 0, dmltIOSubSystem );
}

//-----------------------------------------------------------------------------
HOBJ getRequestCtrlProp( HDRV hDrv, const char* pRequestCtrlName, const char* pPropName )
//-----------------------------------------------------------------------------
{
	return getDriverProperty( hDrv, pPropName, pRequestCtrlName, dmltRequestCtrl );
}

//-----------------------------------------------------------------------------
HOBJ getRequestProp( HDRV hDrv, int requestNr, const char* pPropName )
//-----------------------------------------------------------------------------
{
	char buf[BUF_SIZE];

#if defined(_MSC_VER) && (_MSC_VER >= 1400) // is at least VC 2005 compiler?
	sprintf_s( buf, BUF_SIZE, "Entry %d", requestNr );
#else
	sprintf( buf, "Entry %d", requestNr );
#endif // #if defined(_MSC_VER) && (_MSC_VER >= 1400) // is at least VC 2005 compiler?
	return getDriverProperty( hDrv, pPropName, buf, dmltRequest );
}

//-----------------------------------------------------------------------------
HOBJ getSettingProp( HDRV hDrv, const char* pSettingName, const char* pPropName )
//-----------------------------------------------------------------------------
{
	return getDriverProperty( hDrv, pPropName, pSettingName, dmltSetting );
}

//-----------------------------------------------------------------------------
HOBJ getSettingMethod( HDRV hDrv, const char* pSettingName, const char* pMethodName )
//-----------------------------------------------------------------------------
{
	return getDriverMethod( hDrv, pMethodName, pSettingName, dmltSetting );
}

//-----------------------------------------------------------------------------
HOBJ getStatisticProp( HDRV hDrv, const char* pPropName )
//-----------------------------------------------------------------------------
{
	return getDriverProperty( hDrv, pPropName, 0, dmltStatistics );
}

//-----------------------------------------------------------------------------
HOBJ getSystemSettingProp( HDRV hDrv, const char* pPropName )
//-----------------------------------------------------------------------------
{
	return getDriverProperty( hDrv, pPropName, 0, dmltSystemSettings );
}

//-----------------------------------------------------------------------------
TPROPHANDLING_ERROR getStringValue( HOBJ hObj, char** pBuf, int index )
//-----------------------------------------------------------------------------
{
	size_t bufSize = DEFAULT_STRING_SIZE_LIMIT;
	TPROPHANDLING_ERROR result = PROPHANDLING_NO_ERROR;
	static const int BUFFER_INCREMENT_FACTOR = 2;

	*pBuf = (char*)calloc( 1, bufSize );
	while( ( result = OBJ_GetS( hObj, *pBuf, bufSize, index ) ) == PROPHANDLING_INPUT_BUFFER_TOO_SMALL )
	{
		bufSize *= BUFFER_INCREMENT_FACTOR;
		*pBuf = (char*)realloc( *pBuf, bufSize );
	}
	if( result != PROPHANDLING_NO_ERROR )
	{
		printf( "Error while reading string property value: Error code: %d(%s).\n", result, DMR_ErrorCodeToString( result ) );
	}
	return result;
}

//-----------------------------------------------------------------------------
TPROPHANDLING_ERROR getValueAsString( HOBJ hObj, const char* pFormat, char** pBuf, int index )
//-----------------------------------------------------------------------------
{
	size_t bufSize = DEFAULT_STRING_SIZE_LIMIT;
	TPROPHANDLING_ERROR result = PROPHANDLING_NO_ERROR;

	*pBuf = (char*)calloc( 1, bufSize );
	while( ( result = OBJ_GetSFormattedEx( hObj, *pBuf, &bufSize, pFormat, index ) ) == PROPHANDLING_INPUT_BUFFER_TOO_SMALL )
	{
		*pBuf = (char*)realloc( *pBuf, bufSize );
	}

	if( result != PROPHANDLING_NO_ERROR )
	{
		printf( "Error while reading string property value: Error code: %d(%s).\n", result, DMR_ErrorCodeToString( result ) );
	}
	return result;
}

//-----------------------------------------------------------------------------
void modifyEnumPropertyI( HDRV hDrv, const char* pSettingName, const char* pPropName )
//-----------------------------------------------------------------------------
{
	HOBJ hProp = INVALID_ID;
	unsigned int dictValCount = 0;
	int* dictVals = NULL;
	TPROPHANDLING_ERROR result = PROPHANDLING_NO_ERROR;

	printf( "Trying to modify property %s:\n", pPropName );
	if( ( hProp = getSettingProp( hDrv, pSettingName, pPropName ) ) != INVALID_ID )
	{
		if( ( result = readTranslationDictValuesI( hProp, &dictVals, &dictValCount ) ) == PROPHANDLING_NO_ERROR )
		{
			int value = 0;
			printf( "Please select one of the values listed above: " );
			value = getIntValFromSTDIn();
			free( dictVals );
			// set the new trigger mode
			if( ( result = OBJ_SetI( hProp, value, 0 ) ) != PROPHANDLING_NO_ERROR )
			{
				printf( "Failed to set new value for %s. Error code: %d(%s).\n", pPropName, result, DMR_ErrorCodeToString( result ) );
			}
		}
	}
}

//-----------------------------------------------------------------------------
TPROPHANDLING_ERROR readTranslationDictValuesI( HOBJ hObj, int** pDictValues, unsigned int* pDictValCnt )
//-----------------------------------------------------------------------------
{
	TPROPHANDLING_ERROR funcResult = PROPHANDLING_NO_ERROR;
	char** ppBuf = 0;
	unsigned int i = 0;
	size_t bufSize = 0;
	const size_t BUFFER_INCREMENT_FACTOR = 6;

	if( ( funcResult = OBJ_GetDictSize( hObj, pDictValCnt ) ) != PROPHANDLING_NO_ERROR )
	{
		return funcResult;
	}

	*pDictValues = (int*)calloc( *pDictValCnt, sizeof(int) );
	ppBuf = (char**)calloc( *pDictValCnt, sizeof(char*) );
	bufSize = DEFAULT_STRING_SIZE_LIMIT;
	for( i=0; i<*pDictValCnt; i++ )
	{
		ppBuf[i] = (char*)calloc( 1, bufSize );
	}

	while( ( funcResult = OBJ_GetIDictEntries( hObj, ppBuf, bufSize, *pDictValues, (size_t)*pDictValCnt ) ) == PROPHANDLING_INPUT_BUFFER_TOO_SMALL )
	{
		bufSize *= BUFFER_INCREMENT_FACTOR;
		for( i=0; i<*pDictValCnt; i++ )
		{
			ppBuf[i] = (char*)realloc( ppBuf[i], bufSize );
		}
	}

	if( funcResult == PROPHANDLING_NO_ERROR )
	{
		printf( "Got the following dictionary:\n" );
		for( i=0; i<*pDictValCnt; i++ )
		{
			printf( "[%d]: %s(numerical rep: %d)\n", i, ppBuf[i], (*pDictValues)[i] );
		}
	}

	// free memory again
	for( i=0; i<*pDictValCnt; i++ )
	{
		free( ppBuf[i] );
	}
	free( ppBuf );
	return funcResult;
}

//-----------------------------------------------------------------------------
void conditionalSetPropI( HOBJ hProp, int value )
//-----------------------------------------------------------------------------
{
	unsigned int dictValCount = 0;
	size_t i = 0;
	int* dictVals = NULL;
	TPROPHANDLING_ERROR result = PROPHANDLING_NO_ERROR;
	char bufName[BUF_SIZE_LARGE];
	char* pBufValue = 0;

	if( ( result = readTranslationDictValuesI( hProp, &dictVals, &dictValCount ) ) == PROPHANDLING_NO_ERROR )
	{
		for( i=0; i<dictValCount; i++ )
		{
			if( dictVals[i] == value )
			{
				setPropI( hProp, value, 0 );
				memset( bufName, '\0', BUF_SIZE_LARGE );
				OBJ_GetName( hProp, bufName, BUF_SIZE_LARGE );
				getValueAsString( hProp, 0, &pBufValue, 0 );
				printf( "Property '%s' set to '%s'.\n", bufName, pBufValue );
				free( pBufValue );
				break;
			}
		}
		free( dictVals );
	}
	else
	{
		printf( "Failed to read translation dictionary from property. Error code: %d(%s).\n", result, DMR_ErrorCodeToString( result ) );
	}
}
