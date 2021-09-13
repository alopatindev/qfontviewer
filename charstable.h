#ifndef CHARSTABLE_H
#define CHARSTABLE_H

#include <QWidget>
#include <QFont>
#include <QFontDatabase>
#include <QSize>
#include <QChar>
#include <QString>
#include <QMap>
#include "chardialog.h"

class CharDialog;

const int MAX_CHARS = 1112064;  // 2^20+2^16-2048 == 1112064 chars in UTF-8
const int COLUMNS = 12;
const int ROWS = MAX_CHARS / COLUMNS;

class CharsTable : public QWidget
{
    Q_OBJECT

    QFont font;
    QFontDatabase::WritingSystem subset;
    int squareSize;
    uint key;
    bool systemColors;
    CategoryString categories;

    inline void refresh()
    {
        squareSize = qMax(24, QFontMetrics(font).xHeight() * 3);
        adjustSize(); update();
    }
    void initCharCategories();

public:
    CharsTable(QWidget *parent = 0);
    ~CharsTable();
    QSize sizeHint() const;
    static QString textChar(uint codepoint);

signals:
    void characterSelected(uint character);

public slots:
    void setFontStyle(const QFont & font);
    void setFontFamily(const QString & family) { font.setFamily(family); }
    void setFontSize(qreal size) { font.setPointSizeF(size); refresh(); }
    void setFontSize(const QString & size) { setFontSize(size.toDouble()); }
    void setSubset(QFontDatabase::WritingSystem subset);
    static QString unicodeChar(uint key);
    static QString utf8Char(uint ch);
    inline static QString xmlDecimal(uint key, bool escape = false);
    uint currentKey() { return key; }
    QString currentChar() { return CharsTable::textChar(key); }
    void goToChar(uint character);
    void goToChar(const QString & character);
    void useSystemColors(bool enable) { systemColors = enable; update(); }

protected:
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
};

#endif
