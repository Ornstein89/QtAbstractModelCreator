#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QComboBox>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QString CombineCpp();
    bool LoadSampleFiles();
    QString cppCode;
    QString hCode;
    bool ready;

    struct PropRecord
    {
    public:

        PropRecord():
            property(),
            type(),
            role(),
            qml_name()
        {
            return;
        }

        PropRecord(const PropRecord &p_record):
            property(p_record.property),
            type(p_record.type),
            role(p_record.role),
            qml_name(p_record.qml_name)
        {
            return;
        }

        PropRecord(const QString &p_property,
                   const QString &p_type,
                   const QString &p_role,
                   const QString &p_qml_name):
            property(p_property),
            type(p_type),
            role(p_role),
            qml_name(p_qml_name)
        {
            return;
        }

        QString property;
        QString type;
        QString role;
        QString qml_name;
    };

    typedef QList<PropRecord> typePropList;
    typePropList lstProperties;
    QString strObjClassName, strObjModelName, strFileName;
    //  имя   тип  роль   названиеQML

    void names();
    void parameterList();
private slots:
    void on_tblProperties_cellChanged(int row, int column);

    void on_btnCreteModel_clicked();


private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
