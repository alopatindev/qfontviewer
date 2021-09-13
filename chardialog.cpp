#include "chardialog.h"
#include "charstable.h"

class CharsTable;

CharDialog::CharDialog(uint ch, const QString & fontFamily,
                       const CategoryString & categories,
                       QWidget *parent)
    : QDialog(parent)
{
    this->ch = ch;
    QString text = CharsTable::textChar(ch);
    setupUi(this);
    setWindowTitle(tr("Character %1").arg(text));
    character->setText(text);

    QFont fn = QFont(character->font());
    fn.setFamily(fontFamily);
    character->setFont(fn);

    unicode->setText(CharsTable::unicodeChar(ch));
    utf8->setText(CharsTable::utf8Char(ch));
    xmlDecimal->setText(CharsTable::xmlDecimal(ch));
    category->setText(categories[QChar::category(ch)]);
}

CharDialog::~CharDialog()
{
}
