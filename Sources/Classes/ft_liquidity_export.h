#ifndef FT_LIQUIDITY_EXPORT_H
#define FT_LIQUIDITY_EXPORT_H

#include <QString>
#include "ft_liquidity.h"


class ft_liquidity_export
{
public:
  ft_liquidity_export();
  static void exportIt(ft_liquidity* liquidity);

  enum en_lineIndexes {
    en_lineIndex_Title = 1,
    en_lineIndex_Year,
    en_lineIndex_Month,
    en_lineIndex_Bank,
    en_lineIndex_dummy,
    en_lineIndex_Einzahlungen,
    en_lineIndex_bezahlteRechnungen,
    en_lineIndex_Vorsteuererstattung,
    en_lineIndex_sonstigeEinzahlungen,
    en_lineIndex_dummy2,
    en_lineIndex_Auszahlungen,
    en_lineIndex_Investitionen,
    en_lineIndex_Wareneinkauf,
    en_lineIndex_Versicherungen,
    sizeof_en_lineIndexes
  };

  enum en_columnIndexes {
    en_columnIndex_Titles = 1,
    en_columnIndex_ValuesStart,
    sizeof_en_columnIndexes,
  };
};

#endif // FT_LIQUIDITY_EXPORT_H
