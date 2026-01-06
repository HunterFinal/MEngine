#include "ManifestParser.h"

bool MManifestParser::TryConsumeChar(OUT const TCHAR*& OutPtr, IN TCHAR Ch)
{
  if (*OutPtr != Ch)
  {
    return false;
  }

  ++OutPtr;
  return true;
}

bool MManifestParser::ConsumeWhiteSpace(OUT const TCHAR*& OutPtr)
{
  // Consume all white space until we hit a non white space character
  while (true)
  {
    switch (*OutPtr)
    {
      case MTEXT(' ') :    // Space
      case MTEXT('\n'):    // Line Feed
      case MTEXT('\r'):    // Carriage Return
      case MTEXT('\t'):    // Tab
      {
        ++OutPtr;
      }
      break;

      default:
        return true;
    }
  }
}

bool MManifestParser::ParseString(OUT const TCHAR*& OutPtr, OUT std::wstring& OutStr)
{
  OutStr.clear();

  // We attempt to parse string like "XXX"
  // So the first char should be '"'
  if (*OutPtr != MTEXT('"'))
  {
    return false;
  }

  // Infinity loop until we reach the other '"' or any white space or '\0'
  while (true)
  {
    ++OutPtr;

    switch(*OutPtr)
    {
      // We reach the other '"' so we consume it
      case MTEXT('"'):
      {
        ++OutPtr;
        return true;
      }

      // Exception occured. This is not a valid string 
      case MTEXT('\0'):    // Null Terminator
      case MTEXT('\n'):    // Line Feed
      case MTEXT('\r'):    // Carriage Return
      case MTEXT('\t'):    // Tab
      {
        return false;
      }

      // Escape sequence is valid in string
      case MTEXT('\\'):
      {
        ++OutPtr;
        switch (*OutPtr)
        {
          case MTEXT('\\'): OutStr.push_back(MTEXT('\\')); break;
          case MTEXT('\"'): OutStr.push_back(MTEXT('\"')); break;
          case MTEXT('/'): OutStr.push_back(MTEXT('/'));   break;
          case MTEXT('b'): OutStr.push_back(MTEXT('\b'));  break;
          case MTEXT('f'): OutStr.push_back(MTEXT('\f'));  break;
          case MTEXT('n'): OutStr.push_back(MTEXT('\n'));  break;
          case MTEXT('r'): OutStr.push_back(MTEXT('\r'));  break;
          case MTEXT('t'): OutStr.push_back(MTEXT('\t'));  break;

          // Single escape character is invalid in a string
          default:
            return false;
        }
      }
      break;
        
      default:
      {
        OutStr.push_back(*OutPtr);
      }
      break;
    }
  }
}