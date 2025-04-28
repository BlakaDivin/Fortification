//////////////////////////////////////////////////////////
// Common.h
//--------------------------------------------------------
// Common algorithms for general uses.
//
// Abin (abinn32@yahoo.com)
//////////////////////////////////////////////////////////

#include <windows.h>

long CalculateDistance(const POINT& pt1, const POINT& pt2);
long CalculateDistance(long x1, long y1, long x2, long y2);
void NormalizeRect(RECT& rRect);
void NormalizeRect(LPRECT lpRect);
long CalculateAngle(long x1, long y1, long x2, long y2);
POINT CalculatePointOnTrack(const POINT& ptOrigin, int nRadius, int nAngle);
long CalculateAngle(const POINT& pt1, const POINT& pt2);