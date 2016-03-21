#include "autopriceutils.h"
#include <QStringList>
#include <QListWidget>

namespace Utils {

QStringList items(const QListWidget &widget)
{
    QStringList tmp;
    for (auto row = 0; row < widget.count(); row++) {
        tmp.push_back(widget.item(row)->text());
    }
    return tmp;
}

}
