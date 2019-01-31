#include <QFile>
#include <QDebug>
#include "ft_event_engine.h"


ft_event_engine::ft_event_engine(QObject *parent) : QObject(parent)
{

}

void ft_event_engine::Slot_OpenFile(QString filepath)
{
  QFile* file = new QFile(filepath);

  if (nullptr == file) {

  } else if (false == file->open(QIODevice::ReadOnly | QIODevice::Text)) {

  } else {
    while (false == file->atEnd()) {
      QByteArray line = file->readLine();
      QList<QByteArray> columns = line.split(m_delimiter);

      if (sizeof_en_Columns == columns.count()) {
        for (int32_t i = 0; i < columns.count(); i++) {
          QString cellText = columns.at(i);
          cellText = cellText.remove("\n");
          m_stringList[i].append(cellText);
        }
      }
    }

    qDebug() << m_stringList[0] << m_stringList[1] << m_stringList[2];
  }

  bool allTitlesOkay = true;

  for (uint32_t i = 0; sizeof_en_Columns > i; i++) {
    if (m_ColumnTitles[i] != m_stringList[i].first()) {
      allTitlesOkay = false;
      qDebug() << "Wrong title" << i << m_stringList[i].first() << "expected:" << m_ColumnTitles[i];
    }
  }

  if (false == allTitlesOkay) {

  } else {
    for (int32_t i = 1; m_stringList[0].size() > i; i++) {
      st_values value;

      QString dateString = m_stringList[en_Columns_Date].at(i);
      QStringList dateList = dateString.split('.');
      QString year = dateList.at(2);
      QString month = dateList.at(1);
      QString day = dateList.at(0);
      value.m_date.setDate(year.toInt(), month.toInt(), day.toInt());

      QString eventString = m_stringList[en_Columns_Event].at(i);

      for (uint32_t m = 0; sizeof_en_Events > m; m++) {
        if (m_EventNames[m] == eventString) {
          value.m_event = static_cast<en_Events>(m);
        }
      }

      QString valueString = m_stringList[en_Columns_Value].at(i);
      value.m_value_cents = valueString.toLongLong();

      m_valueList.append(value);
    }
  }

  if (nullptr == file) {

  } else {
    file->deleteLater();
  }
}
