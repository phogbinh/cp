const char EMPTY_CHARACTER = '\0';
const char POSITIVE_SIGN = '+';
const char NEGATIVE_SIGN = '-';
const char SPACE_CHARACTER = ' ';
const char ZERO_CHARACTER = '0';
const char NINE_CHARACTER = '9';
const int INT_MAX_DIGITS_COUNT = 10;
const string INT_MAX_STR = "2147483647";
const string INT_MIN_ABSOLUTE_STR = "2147483648";

enum EStatus
{
    FAILURE = 0,
    SUCCESS
};

class Solution
{
public:
    int myAtoi( string strInput )
    {
        int nFirstNonWhiteSpaceCharacterIndex;
        if ( GetFirstNonWhiteSpaceCharacterIndex( strInput, nFirstNonWhiteSpaceCharacterIndex ) == EStatus::FAILURE )
        {
            return 0;
        }

        char cSign;
        if ( GetSign( nFirstNonWhiteSpaceCharacterIndex, strInput, cSign ) == EStatus::FAILURE )
        {
            return 0;
        }

        int nFirstDigitIndex;
        if ( GetFirstDigitIndex( nFirstNonWhiteSpaceCharacterIndex, cSign, strInput, nFirstDigitIndex ) == EStatus::FAILURE )
        {
            return 0;
        }

        string strZeroInclusiveNumber = GetStringZeroInclusiveNumber( nFirstDigitIndex, strInput );
        string strNumber = GetStringNumber( strZeroInclusiveNumber );

        return GetNumber( cSign, strNumber );
    }

    EStatus GetFirstNonWhiteSpaceCharacterIndex( string strInput, int& nFirstNonWhiteSpaceCharacterIndex )
    {
        for ( int nIndex = 0; nIndex < strInput.length(); nIndex++ )
        {
            if ( strInput[ nIndex ] != SPACE_CHARACTER )
            {
                nFirstNonWhiteSpaceCharacterIndex = nIndex;
                return EStatus::SUCCESS;
            }
        }

        return EStatus::FAILURE;
    }

    EStatus GetSign( int nFirstNonWhiteSpaceCharacterIndex, string strInput, char& cSign )
    {
        char cFirstNonWhiteCharacter = strInput[ nFirstNonWhiteSpaceCharacterIndex ];
        if ( IsDigit( cFirstNonWhiteCharacter ) || cFirstNonWhiteCharacter == POSITIVE_SIGN )
        {
            cSign = EMPTY_CHARACTER;
            return EStatus::SUCCESS;
        }

        if ( cFirstNonWhiteCharacter == NEGATIVE_SIGN )
        {
            cSign = NEGATIVE_SIGN;
            return EStatus::SUCCESS;
        }

        return EStatus::FAILURE;
    }

    bool IsDigit( char cChar )
    {
        return ZERO_CHARACTER <= cChar && cChar <= NINE_CHARACTER;
    }

    EStatus GetFirstDigitIndex( int nFirstNonWhiteSpaceCharacterIndex, char cSign, string strInput, int& nFirstDigitIndex )
    {
        if ( cSign == EMPTY_CHARACTER && IsDigit( strInput[ nFirstNonWhiteSpaceCharacterIndex ] ) )
        {
            //
            nFirstDigitIndex = nFirstNonWhiteSpaceCharacterIndex;
            return EStatus::SUCCESS;
        }
        else if ( cSign == EMPTY_CHARACTER && IsDigit( strInput[ nFirstNonWhiteSpaceCharacterIndex + 1 ] ) )
        {
            // +
            nFirstDigitIndex = nFirstNonWhiteSpaceCharacterIndex + 1;
            return EStatus::SUCCESS;
        }
        else if ( cSign == NEGATIVE_SIGN && IsDigit( strInput[ nFirstNonWhiteSpaceCharacterIndex + 1 ] ) )
        {
            // -
            nFirstDigitIndex = nFirstNonWhiteSpaceCharacterIndex + 1;
            return EStatus::SUCCESS;
        }
        else
        {
            return EStatus::FAILURE;
        }
    }

    string GetStringZeroInclusiveNumber( int nFirstDigitIndex, string strInput )
    {
        string strNumber = "";
        for ( int nIndex = nFirstDigitIndex; nIndex < strInput.length(); nIndex++ )
        {
            if ( !IsDigit( strInput[ nIndex ] ) )
            {
                break;
            }

            strNumber = strNumber + strInput[ nIndex ];
        }

        return strNumber;
    }

    string GetStringNumber( string strZeroInclusiveNumber )
    {
        int nFirstNonZeroDigitIndex = GetFirstNonZeroDigitIndex( strZeroInclusiveNumber );
        return strZeroInclusiveNumber.substr( nFirstNonZeroDigitIndex, strZeroInclusiveNumber.length() - nFirstNonZeroDigitIndex + 1 );
    }

    int GetFirstNonZeroDigitIndex( string strZeroInclusiveNumber )
    {
        for ( int nIndex = 0; nIndex < strZeroInclusiveNumber.length(); nIndex++ )
        {
            if ( strZeroInclusiveNumber[ nIndex ] != ZERO_CHARACTER )
            {
                return nIndex;
            }
        }

        return strZeroInclusiveNumber.length() - 1;
    }

    int GetNumber( char cSign, string strNumber )
    {
        if ( cSign == EMPTY_CHARACTER && LeftHandStringIsBiggerOrEqualThanRightHandString( strNumber, INT_MAX_STR ) )
        {
            return INT_MAX;
        }
        else if ( cSign == NEGATIVE_SIGN && LeftHandStringIsBiggerOrEqualThanRightHandString( strNumber, INT_MIN_ABSOLUTE_STR ) )
        {
            return INT_MIN;
        }
        else
        {
            int nAbsoluteNumber = atoi( strNumber.c_str() );
            return cSign == EMPTY_CHARACTER ? nAbsoluteNumber : -nAbsoluteNumber;
        }
    }

    bool LeftHandStringIsBiggerOrEqualThanRightHandString( string strLeft, string strRight )
    {
        if ( strLeft.length() > strRight.length() )
        {
            return true;
        }
        else if ( strLeft.length() < strRight.length() )
        {
            return false;
        }

        // If equal length
        for ( int nIndex = 0; nIndex < strLeft.length(); nIndex++ )
        {
            if ( strLeft[ nIndex ] > strRight[ nIndex ] )
            {
                return true;
            }
            else if ( strLeft[ nIndex ] < strRight[ nIndex ] )
            {
                return false;
            }
        }

        // If equal
        return true;
    }
};