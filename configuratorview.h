#ifndef CONFIGURATORVIEW_H
#define CONFIGURATORVIEW_H

#include <QtGui/QDialog>

namespace Ui {
    class ConfiguratorView;
}

class ConfiguratorView : public QDialog {
    Q_OBJECT
public:
    ConfiguratorView(QWidget *parent = 0);
    ~ConfiguratorView();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::ConfiguratorView *m_ui;
private slots:
    void configurar();
};

#endif // CONFIGURATORVIEW_H
