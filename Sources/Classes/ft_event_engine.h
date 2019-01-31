#ifndef FT_EVENT_ENGINE_H
#define FT_EVENT_ENGINE_H

#include <QObject>
#include <QString>
#include <QDate>

#include "ft_events.h"

class ft_event_engine : public QObject
{
  Q_OBJECT
public:
  explicit ft_event_engine(QObject *parent = nullptr);

signals:

public slots:
  void Slot_OpenFile(QString filepath);

private:
  char m_delimiter = ';';

  enum en_Columns {
    en_Columns_Date,
    en_Columns_Event,
    en_Columns_Value,
    sizeof_en_Columns
  };

  QString m_ColumnTitles[sizeof_en_Columns] = {
    "Datum",
    "Event",
    "Wert",
  };

  QStringList m_stringList[sizeof_en_Columns];

  struct st_values {
    QDate m_date;
    en_Events m_event = en_Events_unknown;
    uint64_t m_value_cents = 0;
  };

  QList<st_values> m_valueList;

  QString m_EventNames[sizeof_en_Events] = {
    "en_Events_unknown",
    "Versicherung",  // en_Events_Versicherung,
    "Produktverkauf",  // en_Events_Produktverkauf,
    "Produktkauf"  // en_Events_Produktkauf
  };
};

#endif // FT_EVENT_ENGINE_H
