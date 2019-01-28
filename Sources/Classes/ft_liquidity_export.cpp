#include "ft_liquidity_export.h"
#include "xlsxdocument.h"

#include <QDate>
#include <QLocale>
#include <QApplication>

const QString m_lineTitles[ft_liquidity_export::sizeof_en_lineIndexes] = {
  QString("Liquiditätsplanung"),  // en_lineIndex_Title
  QString(""),  // en_lineIndex_Year
  QString("(in TEUR)"),  // en_lineIndex_Month
  QString("Kasse/Bank - Bestand Monatsanfang"),  // en_lineIndex_Bank
  QString(""),  // en_lineIndex_dummy
  QString("Einzahlungen (brutto), Summe"),  // en_lineIndex_Einzahlungen
  QString("Bezahlte Rechnungen"),  // en_lineIndex_bezahlteRechnungen
  QString("Vorsteuererstattung"),  // en_lineIndex_Vorsteuererstattung
  QString("Sonstige Einzahlungen"),  // en_lineIndex_sonstigeEinzahlungen
  QString(""),
  QString("Auszahlungen (brutto), Summe"),  // en_lineIndex_Auszahlungen
  QString("Investitionen"),  // en_lineIndex_Investitionen,
  QString("Wareneinkauf"),  // en_lineIndex_Wareneinkauf,
  QString("Versicherungen / Beiträge / sonst. Steuern"),  // en_lineIndex_Versicherungen
};

ft_liquidity_export::ft_liquidity_export()
{

}

void ft_liquidity_export::exportIt(ft_liquidity* liquidity)
{
  QXlsx::Document xlsx;

  xlsx.addSheet("Liquiditätsplanung");

  /** @notes Write titles */
  int32_t maxValue = (sizeof_en_lineIndexes - 1);
  for (int32_t i = 0; i < maxValue; i++) {
    QString tmpString = m_lineTitles[i];
    xlsx.write(i + 1, en_columnIndex_Titles, tmpString);
  }

  QLocale* locale = new QLocale(QLocale::German, QLocale::Germany);

  int32_t year = 0;
  int32_t firstYear = 0;
  if (liquidity->GetEntryList()->count() > 0) {
    firstYear = liquidity->GetEntryList()->first().m_date.year() - 1;
    for (int32_t i = 0; liquidity->GetEntryList()->count() > i; i++) {
      if (year != liquidity->GetEntryList()->at(i).m_date.year()) {
        year = liquidity->GetEntryList()->at(i).m_date.year();
        xlsx.write(en_lineIndex_Year, en_columnIndex_ValuesStart + i, QString("%1. Jahr").arg(year - firstYear));
      }

      ft_liquidity::Entry entry = liquidity->GetEntryList()->at(i);
      int32_t monthIndex = liquidity->GetEntryList()->at(i).m_date.month();
      QString monthName = locale->monthName(monthIndex);
      xlsx.write(en_lineIndex_Month, en_columnIndex_ValuesStart + i, monthName);
      xlsx.write(en_lineIndex_Bank, en_columnIndex_ValuesStart + i,
                 QString::number(static_cast<double>(liquidity->GetEntryList()->at(i).m_moneyCent) / 100, 'f', 2));

      xlsx.write(en_lineIndex_bezahlteRechnungen, en_columnIndex_ValuesStart + i,
                 QString::number(static_cast<double>(liquidity->GetEntryList()->at(i).m_bezahlteRechnungenCent) / 100, 'f', 2));

      xlsx.write(en_lineIndex_Auszahlungen, en_columnIndex_ValuesStart + i,
                 QString::number(static_cast<double>(entry.Get_SummeAusgaben()) / 100, 'f', 2));

      xlsx.write(en_lineIndex_Wareneinkauf, en_columnIndex_ValuesStart + i,
                 QString::number(static_cast<double>(liquidity->GetEntryList()->at(i).m_WareneinkaufCent) / 100, 'f', 2));
    }
  }

  delete locale;

  xlsx.saveAs("Test.xlsx");
}
