#ifndef TMCOMPLETER_H
#define TMCOMPLETER_H

#include <QCompleter>
class TreeModelCompleter : public QCompleter
{
    Q_OBJECT
    Q_PROPERTY(QString separator READ separator WRITE setSeparator)
public:
    explicit TreeModelCompleter(QObject *parent = nullptr);
    explicit TreeModelCompleter(QAbstractItemModel *model, QObject *parent = nullptr);
    QString separator() const;
public slots:
    void setSeparator(const QString &separator);
protected:
    QStringList splitPath(const QString &path) const;
    QString pathFromIndex(const QModelIndex &index) const;
private:
    QString sep;
};


#endif // TMCOMPLETER_H
